#include <iostream>
#include <string>
#include <vector>
#include <random>

int main() 
{
    const std::string target = "methinksitislikeaweasel";
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> char_dist('a', 'z');
    std::uniform_real_distribution<double> mut_dist(0.0, 1.0);

    std::string current(23, 'a');
    for (char& c : current) 
    {
        c = static_cast<char>(char_dist(engine));
    }

    int iteration = 0;
    while (true) 
    {
        std::cout << current << "\n";
        if (current == target) break;

        std::string best_str = current;
        int best_score = 24;

        for (int i = 0; i < 100; ++i) 
        {
            std::string copy = current;
            int diff = 0;
            for (int j = 0; j < 23; ++j) 
            {
                if (mut_dist(engine) <= 0.05) 
                {
                    copy[j] = static_cast<char>(char_dist(engine));
                }
                if (copy[j] != target[j]) diff++;
            }
            if (diff == 0) 
            {
                best_str = copy;
                break;
            }
            if (diff < best_score) 
            {
                best_score = diff;
                best_str = copy;
            }
        }
        current = best_str;
        iteration++;
    }
}
// g++ -std=c++23 04.cpp -o 04