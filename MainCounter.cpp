#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

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

int main()
{
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
        else break;
    }

    map<string, MainCounter, less<string>>::iterator it;

    for (it = counter.begin();
         it != counter.end();
         it++)
    {
        cout << (*it).first
             << "\t"
             << (*it).second
             << endl;
    }

    return 0;
}