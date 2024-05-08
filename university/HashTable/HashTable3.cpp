#include <iostream>
#include <vector>
#include <list>
#include <fstream>

class HashTable
{
public:
    HashTable(int cap) : _table(std::vector<std::list<int>>(cap)), _capacity(cap), _count(0) {};
    ~HashTable() = default;

    void add(int num);
    int find(int num);
    
    void reHash();
    int hashFunc(int num);

    void out();

private:
    int _capacity, _count;
    std::vector<std::list<int>> _table;
};

// Function for console outing Hash Table
void HashTable::out()
{
    int i = 0;
    for (auto& it : _table)
    {
        std::cout << i << " ---> ";
        for (int x : it)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
        i++;
    }
}

// hash function
int HashTable::hashFunc(int num)
{
    return num % _capacity;
}

// finding key by element
int HashTable::find(int num)
{
    for (int x : _table[hashFunc(num)])
    {
        if (x == num) 
        {
            return hashFunc(num);
        }
    }
    return -1;
}

// rehashing function
void HashTable::reHash()
{
    std::vector<std::list<int>> temp(2 * _capacity);
    _capacity = 2 * _capacity;
    for (auto& it : _table)
    {
        for (int x : it)
        {
            temp[hashFunc(x)].push_back(x);
        }
    }
    swap(_table, temp);
}

// adding element to table
void HashTable::add(int num)
{
    if ((float)_count / (float)_capacity > 0.7) reHash();

    if (find(num) == -1)
    {
        _table[hashFunc(num)].push_back(num);
        _count++;
    }

}

int main()
{
    std::fstream in("input3.txt");
    HashTable table(10);

    int x;
    if (in.is_open())
        while(in >> x)
            table.add(x);
    in.close();

    table.out();

    std::cout << "Searching for 4444: " << std::endl;
    std::cout << "Key is: " << table.find(4444);
}
