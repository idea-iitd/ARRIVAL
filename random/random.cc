#include "random.h"
#include <cstdlib>

Random::Random(int max, int seed) {
    srand(seed); 
    while (numbers.size() < max) {
        numbers.push_back(rand());
    }
    it = numbers.begin();
}
int Random::next() {
    ++it;
    if (it == numbers.end()) it = numbers.begin();
    return *it;
}