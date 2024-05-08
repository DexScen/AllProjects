#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class HashTable
{
public:
    
    HashTable(int cap);
    ~HashTable() = default;

    int hashFunction(string s);
    int find(string s);
    void add(string s);
    void remove(string s);
    void addNoReHash(string s);
    int findc(string s);
    void out();
    void reHash();

private:
    int capacity;
    std::vector <list<string>> table;
    int count;
};

// constructor
HashTable::HashTable(int cap) : table(std::vector<list<string>>(cap))
{
    capacity = cap;
    count = 0;
}

// hashFunction to return key of entered string
int HashTable::hashFunction(string s)
{
    int res = 0;
    for (char c : s)
    {
        res += (int)c;
    }
    return res % capacity;
}

// add element to table with auto rehashing 
void HashTable::add(string s)
{
    if ((((float)count / (float)capacity)) > 0.7) reHash();

    if (find(s) == -1)
    {
        table[hashFunction(s)].push_back(s);
        count++;
    }
    
}

// remove element from hashtable
void HashTable::remove(string s)
{
    table[hashFunction(s)].remove(s);
}

// add function withour rehashing
void HashTable::addNoReHash(string s)
{
    if (find(s) == -1)
    {
        table[hashFunction(s)].push_back(s);
        count++;
    }
}

// returning number of comparisons for finding element
int HashTable::findc(string s)
{
    int comp = 0;
    for (string str : table[hashFunction(s)])
    {
        comp++;
        if (str == s)
        {
            return comp;
        }
    }

    return -1;
}

// returning key of entered element
int HashTable::find(string s)
{
    for (string str : table[hashFunction(s)]) 
    {
        if (str == s)
        {      
            return(hashFunction(s));
        }
    }
    
    return -1;
}

// console outing hashtable
void HashTable::out()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << i << " --> ";
        for (string str : table[i])
        {
            cout << str << ' ';
        }
        cout << endl;
    }
}

// rehashing hashtable
void HashTable::reHash()
{
    int newCapacity = 2 * capacity;
    std::vector<list<string>> temp(newCapacity);
    capacity = newCapacity;

    for (auto& it : table)
    {
        for (string str : it)
        {
            temp[hashFunction(str)].push_back(str);
        }
    }

    std::swap(table, temp);
}

// split to fill vector
void split(const string& s, char delim, vector<string>& elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

// split returning final vector
vector<string> split(const string& s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int main()
{
    cout << "Enter hashtable capacity: ";
    int n;
    cin >> n;
    cout << "Example of table with re-hashing: " << endl;
    HashTable table(n); 
    string line, str = "";
    vector<string> words;
    ifstream in("input.txt"); // Entering words from file
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            str += line;
        }
    }
    in.close();
    words = split(str, ' ');
    for (string s : words)
    {
        table.add(s);
    }
    table.out();
    cout << "Enter word to search: ";
    cin >> line;
    cout << "Index for " << line << " is " << table.find(line) << " and comparison amount is: " << table.findc(line) << endl;
   
    // HashTable for 5: 
    cout << "Enter hashtable capacity: ";
    cin >> n;
    cout << "Example of table with entered capacity: " << endl; // cap = 5
    HashTable table1(n);
    for (string s : words)
    {
        table1.addNoReHash(s);
    }
    table1.out();
    cout << "Enter word to search: ";
    cin >> line;
    cout << "Index for " << line << " is " << table1.find(line) << " and comparison amount is: " << table1.findc(line) << endl;
    
    // HashTable for 1000:
    cout << "Enter hashtable capacity: ";
    cin >> n;
    cout << "Example of table with entered capacity: " << endl; // cap = 1000
    HashTable table2(n);
    for (string s : words)
    {
        table2.addNoReHash(s);
    }
    table2.out();
    cout << "Enter word to search: ";
    cin >> line;
    cout << "Index for " << line << " is " << table2.find(line) << " and comparison amount is: " << table2.findc(line) << endl;

    // Delete words starting with entered letter: (Lower-Upper case sensitive)
    cout << "Enter letter to delete words starting with: ";
    char ch;
    cin >> ch;
    cout << endl;
    for (string s : words)
    {
        if (s[0] == ch)
        {
            table.remove(s);
        }
    }
    table.out();
}

