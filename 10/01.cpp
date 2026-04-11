#include <iostream>
#include <vector>
#include <deque>
#include <print>

void investigate_vector() {
    std::vector<int> v;
    size_t last_capacity = 0;
    
    std::println("--- std::vector Capacity Growth ---");
    
    for (int i = 0; i < 150; ++i) {
        v.push_back(i);
        size_t current_capacity = v.capacity();
        
        if (current_capacity != last_capacity) {
            double factor = (last_capacity == 0) ? 0 : static_cast<double>(current_capacity) / last_capacity;
            std::println("Size: {:3}, Capacity: {:4}, Growth factor: {:.2f}", 
                         v.size(), current_capacity, factor);
            last_capacity = current_capacity;
        }
    }
}

void investigate_deque() {
    std::deque<int> d;
    
    std::println("\n--- std::deque Address Tracking ---");
    
    const int* prev_addr = nullptr;
    size_t elements_in_chunk = 0;
    bool jump_detected = false;

    for (int i = 0; i < 600; ++i) {
        d.push_back(i);
        const int* current_addr = &d.back();
        
        if (prev_addr && current_addr != prev_addr + 1) {
            std::println("Address jump at index {:3}: prev = {}, current = {}. Chunk size: {} elements ({} bytes)", 
                         i, (void*)prev_addr, (void*)current_addr, elements_in_chunk, elements_in_chunk * sizeof(int));
            elements_in_chunk = 0;
            jump_detected = true;
        }
        
        elements_in_chunk++;
        prev_addr = current_addr;
    }

    if (!jump_detected) {
        std::println("No jumps detected in 600 elements. Increase the loop range or check type size.");
    }
}

int main() {
    investigate_vector();
    investigate_deque();
    return 0;
}