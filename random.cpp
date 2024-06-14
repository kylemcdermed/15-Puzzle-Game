#include "random.h"


signed int getRandomValue() { // gets random number seed


    std::random_device rd{};

    std::mt19937 mt{static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> random{1,100};

    return random(mt);

}
