#include <cassert>
#include <cstddef>
#include <memory>
#include <new>
#include <print>
#include <random>
#include <utility>
#include <vector>
#include <limits>
#include <boost/noncopyable.hpp>
#include <benchmark/benchmark.h>

class Allocator : private boost::noncopyable {
public:
    enum class Policy { FirstFit, BestFit };

    Allocator(std::size_t size, Policy policy = Policy::FirstFit) 
        : m_size(size), m_policy(policy) {
        assert(m_size >= sizeof(Node) + 1);
        m_begin = operator new(m_size, std::align_val_t(s_alignment));
        m_head = get_node(m_begin);
        m_head->size = m_size - sizeof(Header);
        m_head->next = nullptr;
    }

    ~Allocator() {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }

    auto allocate(std::size_t size) -> void * {
        void * end = get_byte(m_begin) + sizeof(Header) + size, * next = end;
        auto free_space = 2 * alignof(Header);
        if (next = std::align(alignof(Header), sizeof(Header), next, free_space); next) {
            auto padding = get_byte(next) - get_byte(end);
            auto [current, previous] = (m_policy == Policy::FirstFit) 
                                        ? find_first(size + padding) 
                                        : find_best(size + padding);
            if (current) {
                if (current->size >= size + padding + sizeof(Node) + 1) {
                    auto step = sizeof(Header) + size + padding;
                    auto node = get_node(get_byte(current) + step);
                    node->size = current->size - step;
                    node->next = current->next;
                    current->next = node;
                } else {
                    padding += current->size - size - padding;
                }
                if (!previous) m_head = current->next;
                else previous->next = current->next;
                auto header = get_header(current);
                header->size = size + padding;
                return get_byte(current) + sizeof(Header);
            }
        }
        return nullptr;
    }

    void deallocate(void * x) {
        if (!x) return;
        auto node = get_node(get_byte(x) - sizeof(Header));
        Node * previous = nullptr, * current = m_head;
        while (current) {
            if (node < current) {
                node->next = current;
                if (!previous) m_head = node;
                else previous->next = node;
                break;
            }
            previous = current;
            current  = current->next;
        }
        merge(previous, node);
    }

private:
    struct Node { 
        std::size_t size = 0; 
        Node * next = nullptr; 
    };
    struct alignas(std::max_align_t) Header { 
        std::size_t size = 0; 
    };

    auto get_byte(void * x) const -> std::byte * { return static_cast<std::byte*>(x); }
    auto get_node(void * x) const -> Node * { return static_cast<Node*>(x); }
    auto get_header(void * x) const -> Header * { return static_cast<Header*>(x); }

    auto find_first(std::size_t size) const -> std::pair<Node *, Node *> {
        Node * current = m_head, * previous = nullptr;
        while (current && size > current->size) {
            previous = current;
            current  = current->next;
        }
        return {current, previous};
    }

    auto find_best(std::size_t size) const -> std::pair<Node *, Node *> {
        Node * current = m_head, * previous = nullptr;
        Node * best = nullptr, * best_prev = nullptr;
        std::size_t min_diff = std::numeric_limits<std::size_t>::max();
        while (current) {
            if (current->size >= size) {
                std::size_t diff = current->size - size;
                if (diff < min_diff) {
                    min_diff = diff;
                    best = current;
                    best_prev = previous;
                    if (min_diff == 0) break;
                }
            }
            previous = current;
            current = current->next;
        }
        return {best, best_prev};
    }

    void merge(Node * previous, Node * node) const {
        if (node->next && get_byte(node) + sizeof(Header) + node->size == get_byte(node->next)) {
            node->size += sizeof(Header) + node->next->size;
            node->next = node->next->next;
        }
        if (previous && get_byte(previous) + sizeof(Header) + previous->size == get_byte(node)) {
            previous->size += sizeof(Header) + node->size;
            previous->next = node->next;
        }
    }

    std::size_t m_size = 0;
    void * m_begin = nullptr;
    Node * m_head  = nullptr;
    Policy m_policy;
    static inline auto s_alignment = alignof(std::max_align_t);
};

void run_bench(benchmark::State & state, Allocator::Policy policy) {
    auto kb = 1uz << 10, mb = 1uz << 20, gb = 1uz << 30;
    std::uniform_int_distribution<std::size_t> distribution(1, 16);
    std::default_random_engine engine(42);
    std::vector<void*> vector(kb, nullptr);
    for (auto _ : state) {
        Allocator allocator(2 * gb, policy); 
        for (auto i = 0uz; i < kb; ++i)
            vector[i] = allocator.allocate(distribution(engine) * mb);
        for (auto i = 0uz; i < kb; i += 32)
            allocator.deallocate(vector[i]);
        for (auto i = 0uz; i < kb; i += 32)
            vector[i] = allocator.allocate(distribution(engine) * mb);
        for (auto i = 0uz; i < kb; ++i)
            allocator.deallocate(vector[i]);
        benchmark::DoNotOptimize(vector);
    }
}

void test_first_fit(benchmark::State & state) { run_bench(state, Allocator::Policy::FirstFit); }
void test_best_fit(benchmark::State & state) { run_bench(state, Allocator::Policy::BestFit); }

BENCHMARK(test_first_fit);
BENCHMARK(test_best_fit);

BENCHMARK_MAIN();