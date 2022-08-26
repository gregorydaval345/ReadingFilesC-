#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

template <class T>
struct less_second : std::binary_function<T, T, bool>
{
    inline bool operator()(const T &lhs, const T &rhs)
    {
        return lhs.second.value < rhs.second.value;
    }
};

class MainCounter
{
public:
    int value;
    MainCounter() : value(0) {}

    void operator++(int) { value++; }
};

ostream &operator<<(ostream &st, MainCounter &mc)
{
    return st << mc.value;
}

// Removing the unwanted characters and from a string
bool filter(char c)
{
    return isalpha(c) == 0;
}

const string path = "alice_in_wonderland.txt";
const string commonWordPath = "common.txt";

int main()
{
    typedef std::pair<string, MainCounter> word_mapping;

    map<string, MainCounter> counter;

    ifstream input;
    input.open(path.c_str());

    if (!input)
    {
        cout << "Error opening file alice_in_wonderland.txt\n";
        return 0;
    }

    string token;
    while (true)
    {
        input >> token;

        // Remove the unwanted characters from string
        token.resize(remove_if(token.begin(), token.end(), filter) - token.begin());

        if (input)
        {
            counter[token]++;
        }
        else
            break;
    }

    map<string, MainCounter, less<string>>::iterator it = counter.begin();

    for (; it != counter.end(); it++)
    {
        cout << std::setw(20)
             << (*it).first
             << "\t"
             << (*it).second
             << endl;
    }

    // Sorting using vector
    std::vector<word_mapping> result(counter.begin(), counter.end());
    std::sort(result.begin(), result.end(), less_second<word_mapping>());

    for (std::vector<word_mapping>::const_iterator iter = result.begin();
         iter != result.end();
         iter++)

    {
        cout
            << std::setw(20)
            << (*iter).first
            << std::left
            << "\t"
            << (*iter).second.value
            << endl;
    }

    return 0;
}