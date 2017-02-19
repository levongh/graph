#include <iostream>
#include <chrono>

class timer
{
public:
    timer()
        : m_start{std::chrono::high_resolution_clock::now()}
    {
    }
    ~timer()
    {
        std::cout << "Time: " <<
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_start).count()
            << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};
