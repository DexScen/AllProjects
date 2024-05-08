#include <iostream>
#include <string>

// Реализация сугубо для 1й задачи, на строку состоящую только из маленьких букв.

using namespace std;

class HashTable
{
private:
    int* table;
    int capacity;
public:

    HashTable(int cap)
    {
        capacity = cap;
        table = new int[capacity]();
    }

    ~HashTable()
    {
        delete[] table;
    }

    int hashFunction(char c)
    {
        return c % capacity;
    }

    void add(char c)
    {
        table[hashFunction(c)]++;
    }

    int find(char c)
    {
        return table[hashFunction(c)];
    }

    void out()
    {
        char c = 'a';
        for (char i = 0; i < capacity; i++)
        {
            cout << (char)(c + i) << " --> " << table[hashFunction((char)(c + i))] << endl;
        }
    }
};

int main()
{
    HashTable hash(26);
    string s;
    cin >> s;
    for (char c : s)
    {
        hash.add(c);
    }
    // Вывод таблицы:
    hash.out();
    // Поиск в таблице:
    cout << "Enter char to search for: " << endl;
    char c;
    cin >> c;
    cout << "Value for " << c << " is: " << hash.find(c);
}
