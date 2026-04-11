#include <iostream>
#include <boost/multi_array.hpp>
#include <chrono>
#include <thread>
#include <vector>

using grid_t = boost::multi_array<bool, 2>;

void print_grid(const grid_t& grid) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << (grid[i][j] ? "# " : ". ");
        }
        std::cout << "\n";
    }
    std::cout << std::string(20, '-') << "\n";
}

int count_neighbors(const grid_t& grid, int r, int c) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nr = r + i, nc = c + j;
            if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && grid[nr][nc]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    grid_t grid(boost::extents[10][10]);
    std::fill(grid.data(), grid.data() + grid.num_elements(), false);

    grid[1][2] = true; grid[2][3] = true;
    grid[3][1] = true; grid[3][2] = true; grid[3][3] = true;

    for (int step = 0; step < 15; ++step) {
        print_grid(grid);
        grid_t next_grid(boost::extents[10][10]);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                int neighbors = count_neighbors(grid, i, j);
                if (grid[i][j]) {
                    next_grid[i][j] = (neighbors == 2 || neighbors == 3);
                } else {
                    next_grid[i][j] = (neighbors == 3);
                }
            }
        }
        grid = next_grid;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}