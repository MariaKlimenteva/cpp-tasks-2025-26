#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>
#include <limits>
#include <boost/graph/adjacency_matrix.hpp>

int main() {
    const int N = 10;
    
    // Граф коммивояжера: 10 вершин, полносвязный, неориентированный
    typedef boost::adjacency_matrix<boost::undirectedS, boost::no_property, 
                                   boost::property<boost::edge_weight_t, int>> Graph;
    Graph g(N);

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            boost::add_edge(i, j, dist(gen), g);
        }
    }

    std::cout << "Weights:\n    ";
    for (int i = 0; i < N; ++i) std::cout << std::setw(3) << i << " ";
    std::cout << "\n   " << std::string(N * 4, '-') << "\n";
    
    for (int i = 0; i < N; ++i) {
        std::cout << std::setw(2) << i << "| ";
        for (int j = 0; j < N; ++j) {
            if (i == j) std::cout << std::setw(3) << 0 << " ";
            else {
                auto e = boost::edge(i, j, g);
                std::cout << std::setw(3) << boost::get(boost::edge_weight, g, e.first) << " ";
            }
        }
        std::cout << "\n";
    }

    std::vector<int> path(N - 1);
    std::iota(path.begin(), path.end(), 1);

    int min_cost = std::numeric_limits<int>::max();
    std::vector<int> best_path;

    do {
        int cost = 0;
        
        cost += boost::get(boost::edge_weight, g, boost::edge(0, path[0], g).first);

        for (size_t i = 0; i < path.size() - 1; ++i) {
            cost += boost::get(boost::edge_weight, g, boost::edge(path[i], path[i+1], g).first);
        }
        cost += boost::get(boost::edge_weight, g, boost::edge(path.back(), 0, g).first);

        if (cost < min_cost) {
            min_cost = cost;
            best_path = path;
        }
    } while (std::next_permutation(path.begin(), path.end()));

    std::cout << "\nBest Path: 0 -> ";
    for (int v : best_path) std::cout << v << " -> ";
    std::cout << "0\nCost: " << min_cost << "\n";

    return 0;
}
