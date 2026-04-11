#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class LinkedList {
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(T val) : data(std::move(val)), next(nullptr) {}
    };
    std::unique_ptr<Node> head;

public:
    void push_front(T val) {
        auto new_node = std::make_unique<Node>(std::move(val));
        new_node->next = std::move(head);
        head = std::move(new_node);
    }

    void print() const {
        for (Node* curr = head.get(); curr; curr = curr->next.get()) {
            std::cout << curr->data << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
class SimpleTree {
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(T val) : data(std::move(val)) {}
    };
    std::unique_ptr<Node> root;

public:
    void set_root(T val) { root = std::make_unique<Node>(std::move(val)); }
    
    void add_left(T val) {
        if (root) root->left = std::make_unique<Node>(std::move(val));
    }
};

int main() {
    LinkedList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    std::cout << "List: ";
    list.print();

    auto shared_val = std::make_shared<int>(42);
    std::cout << "Shared value: " << *shared_val << " (Use shared_ptr only for shared ownership)" << std::endl;

    return 0;
}

// g++ -std=c++23 03.cpp -o task3