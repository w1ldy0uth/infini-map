#include "Random.h"
#include <random>
#include <ctime>
#include <thread>
#include <chrono>

int generateRandomSeed()
{
    std::random_device rd;
    if (rd.entropy() != 0) {
        return static_cast<int>(rd());
    }

    // Combined time and thread ID
    auto ns = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto tid = std::hash<std::thread::id>{}(std::this_thread::get_id());

    std::seed_seq seed{
        static_cast<unsigned int>(ns),
        static_cast<unsigned int>(ns >> 32),
        static_cast<unsigned int>(tid),
        static_cast<unsigned int>(tid >> 32)
    };

    unsigned int result;
    seed.generate(&result, &result + 1);
    return static_cast<int>(result);
}
