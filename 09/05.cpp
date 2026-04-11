#include <iostream>
#include <memory>
#include <iterator>

template <typename T>
class List {
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
        Node(const T& val) : data(val) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

public:
    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(std::shared_ptr<Node> ptr, std::shared_ptr<Node> t) 
            : current(ptr), tail_ref(t) {}

        reference operator*() const { return current->data; }
        pointer operator->() { return &current->data; }

        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (!current) {
                current = tail_ref;
            } else {
                current = current->prev.lock();
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        std::shared_ptr<Node> current;
        std::shared_ptr<Node> tail_ref;
    };

    void push_back(const T& val) {
        auto new_node = std::make_shared<Node>(val);
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
    }

    Iterator begin() { return Iterator(head, tail); }
    Iterator end() { return Iterator(nullptr, tail); }
};

int main() {
    List<int> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    std::cout << "Forward: ";
    auto it = myList.begin();
    for (; it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    
    std::cout << "\nBackward: ";
    auto it_back = myList.end();
    do {
        --it_back;
        std::cout << *it_back << " ";
    } while (it_back != myList.begin());
    
    std::cout << std::endl;

    return 0;
}