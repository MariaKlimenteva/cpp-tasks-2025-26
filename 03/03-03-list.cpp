#include <iostream>
#include <stdexcept>
#include <cassert>

class List
{
private:
    struct Node
    {
        int data;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    ~List()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    bool empty() const
    {
        return head == nullptr;
    }

    void show() const
    {
        Node* current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    void push_front(int value)
    {
        Node* new_node = new Node{value, head};
        head = new_node;
        if (tail == nullptr)
        {
            tail = new_node;
        }
    }

    void push_back(int value)
    {
        Node* new_node = new Node{value, nullptr};
        if (empty())
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void pop_front()
    {
        if (empty())
        {
            throw std::out_of_range("Cannot pop_front from an empty list.");
        }
        Node* node_to_delete = head;
        head = head->next;
        delete node_to_delete;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::out_of_range("Cannot pop_back from an empty list.");
        }
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node* current = head;
            while (current->next != tail)
            {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
    }

    int get(size_t index) const
    {
        Node* current = head;
        size_t current_index = 0;
        while (current != nullptr)
        {
            if (current_index == index)
            {
                return current->data;
            }
            current = current->next;
            current_index++;
        }
        throw std::out_of_range("Index is out of range.");
    }
};

void run_tests()
{
    std::cout << "--- Running Tests ---" << std::endl;

    std::cout << "\nModule Test: Initialization" << std::endl;
    List list1;
    assert(list1.empty());
    list1.show();

    std::cout << "\nModule Test: push_front" << std::endl;
    list1.push_front(10);
    assert(!list1.empty());
    assert(list1.get(0) == 10);
    list1.push_front(5);
    assert(list1.get(0) == 5);
    assert(list1.get(1) == 10);
    list1.show();

    std::cout << "\nModule Test: pop_front" << std::endl;
    list1.pop_front();
    assert(list1.get(0) == 10);
    list1.pop_front();
    assert(list1.empty());
    list1.show();

    std::cout << "\nModule Test: push_back" << std::endl;
    List list2;
    list2.push_back(20);
    assert(!list2.empty());
    assert(list2.get(0) == 20);
    list2.push_back(30);
    assert(list2.get(0) == 20);
    assert(list2.get(1) == 30);
    list2.show();
    
    std::cout << "\nModule Test: pop_back" << std::endl;
    list2.pop_back();
    assert(list2.get(0) == 20);
    list2.pop_back();
    assert(list2.empty());
    list2.show();
    
    std::cout << "\nModule Test: Edge Case Exceptions" << std::endl;
    try { list2.pop_front(); assert(false); } catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }
    try { list2.get(0); assert(false); } catch (const std::out_of_range& e) { std::cout << "Caught expected: " << e.what() << std::endl; }

    std::cout << "\nIntegration Test: Mixed Operations" << std::endl;
    List list3;
    list3.push_back(100); // 100 ->
    list3.push_front(50); // 50 -> 100 ->
    list3.push_back(200); // 50 -> 100 -> 200 ->
    list3.push_front(10); // 10 -> 50 -> 100 -> 200 ->
    list3.show();
    assert(list3.get(0) == 10);
    assert(list3.get(1) == 50);
    assert(list3.get(2) == 100);
    assert(list3.get(3) == 200);

    list3.pop_front(); // 50 -> 100 -> 200 ->
    assert(list3.get(0) == 50);
    list3.show();

    list3.pop_back(); // 50 -> 100 ->
    assert(list3.get(1) == 100);
    list3.show();
    
    try { list3.get(2); assert(false); } catch (const std::out_of_range&) { std::cout << "Caught expected out_of_range." << std::endl; }
    
    std::cout << "\nIntegration Test: Clearing the list" << std::endl;
    list3.pop_back(); // 50 ->
    list3.pop_front(); // empty
    assert(list3.empty());
    list3.show();
    
    std::cout << "\n--- All Tests Passed ---" << std::endl;
}


int main()
{
    run_tests();
    return 0;
}

//g++ -std=c++17 -o ./out 03-03-list.cpp
//./out