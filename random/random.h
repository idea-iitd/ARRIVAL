#include <vector>

using namespace std;

class Random {
    private:
        vector<int> numbers;
        vector<int>::iterator it;
    public:
        Random(int max, int seed);
        int next();
};