#include <iostream>
#include <fstream>
#include <sstream>
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

        if (input)
        {
            counter[token]++;
        }
        else
            break;
    }

    map<string, MainCounter, less<string>>::iterator it;

    for (it = counter.begin();
         it != counter.end();
         it++)
    {
        cout << (*it).first
             << ", "
             << (*it).second
             << endl;
    }

    return 0;
}