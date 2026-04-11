#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>

struct Header { size_t size; };
struct Node { Node* next; };

class Allocator {
public:
    virtual ~Allocator() = default;
    virtual void* allocate(size_t size) = 0;
    virtual void deallocate(void* ptr) = 0;

protected:
    template <typename T>
    T* get(void* ptr) {
        return reinterpret_cast<T*>(ptr);
    }
};

class MallocAllocator : public Allocator {
public:
    void* allocate(size_t size) override {
        std::cout << "[Malloc] Allocating " << size << " bytes\n";
        return std::malloc(size);
    }
    void deallocate(void* ptr) override {
        std::cout << "[Malloc] Deallocating\n";
        std::free(ptr);
    }
};

class LinearAllocator : public Allocator {
    std::byte buffer[1024];
    size_t offset = 0;
public:
    void* allocate(size_t size) override {
        std::cout << "[Linear] Allocating from static buffer\n";
        if (offset + size > 1024) return nullptr;
        void* ptr = &buffer[offset];
        offset += size;
        return ptr;
    }
    void deallocate(void*) override {
        std::cout << "[Linear] Deallocate is a no-op\n";
    }
};

class PoolAllocator : public Allocator {
public:
    void* allocate(size_t size) override {
        std::cout << "[Pool] Allocating fixed block\n";
        return ::operator new(size);
    }
    void deallocate(void* ptr) override {
        std::cout << "[Pool] Deallocating block\n";
        ::operator delete(ptr);
    }
};

class DebugAllocator : public Allocator {
public:
    void* allocate(size_t size) override {
        std::cout << "[Debug] Tracking allocation of " << size << "\n";
        return ::operator new(size);
    }
    void deallocate(void* ptr) override {
        std::cout << "[Debug] Tracking deallocation\n";
        ::operator delete(ptr);
    }
};

void run_test(Allocator& alloc) {
    void* p = alloc.allocate(128);
    alloc.deallocate(p);
}

int main() {
    MallocAllocator ma;
    LinearAllocator la;
    PoolAllocator pa;
    DebugAllocator da;

    std::vector<Allocator*> allocators = {&ma, &la, &pa, &da};

    for (auto* a : allocators) {
        run_test(*a);
        std::cout << "-------------------\n";
    }

    return 0;
}