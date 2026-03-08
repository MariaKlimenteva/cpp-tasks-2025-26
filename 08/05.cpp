#include <chrono>
#include <vector>
#include <numeric>
#include <print>
#include <thread>

template <typename D = std::chrono::duration<double>>
class Timer 
{
public:
    void start() 
    {
        if (!m_running) 
        {
            m_begin = clock_t::now();
            m_running = true;
        }
    }

    void stop() 
    {
        if (m_running) 
        {
            m_intervals.push_back(std::chrono::duration_cast<D>(clock_t::now() - m_begin));
            m_running = false;
        }
    }

    double average() const 
    {
        if (m_intervals.empty()) return 0.0;
        D total = std::accumulate(m_intervals.begin(), m_intervals.end(), D{0});
        return total.count() / m_intervals.size();
    }

private:
    using clock_t = std::chrono::steady_clock;
    
    bool m_running = false;
    clock_t::time_point m_begin;
    std::vector<D> m_intervals;
};

int main()
{
    Timer timer;

    for (int i = 0; i < 3; ++i)
    {
        timer.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        timer.stop();
    }

    std::print("Average time: {:.6f} seconds\n", timer.average());
}
// g++ -std=c++23 05.cpp -o 05