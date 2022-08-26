#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

#define TOP_LEN 11

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

    size_t len;

    ifstream input;
    ifstream input2;
    input.open(path.c_str());
    input2.open(commonWordPath.c_str());

    std::string fp = commonWordPath;

    if (!input)
    {
        cout << "Error opening file alice_in_wonderland.txt\n";
        return 0;
    }

    if (!input2)
    {
        cout << "Error opening file common.txt\n";
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

    // Filter out common words
    // int isCommonWord(char *word)
    // {
    //     int i = 0;
    //     for (i = 0; i < TOP_LEN; i++)
    //     {
    //         if (strcmp(input2[i], word) == 0)
    //             return 1;
    //     }
    //     return 0;
    // }

    char ch[100], ch1[100];
    int max = 0;

    while (!input.eof())
    {
        input >> ch;
        if (max < strlen(ch))
        {
            max = strlen(ch);
            strcpy(ch1, ch);
        }
    }
    input.close();
    cout << "Largest word in alice file:", ch1;

    return 0;
}