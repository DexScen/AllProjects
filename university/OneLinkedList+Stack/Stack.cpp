#include <iostream>
#include <cstdlib>
#include <time.h>
/* 
	Я использовал информацию о реализации стека из интернета, поскольку раньше не умел реализовывать его сам
*/
using namespace std;

template <class T>
class Stack
{
public:
	// Конструктор
	Stack()
	{
		head = nullptr;
		size = 0;
	}

	// Деструктор
	~Stack()
	{
		Free();
	}

	// Возвращает true, если стек пуст
	bool IsEmpty()
	{
		return size == 0;
	}

	// Добавить элемент в стек
	void Push(T item)
	{
		try
		{
			// 1. Если первый элемент
			if (size == 0)
			{
				head = new Node<T>;
				head->next = nullptr;
				head->data = item;
			}
			else
			{
				// 2. Если не первый элемент
				// 2.1. Создать новую ячейку и заполнить ее данными
				Node<T>* p2 = new Node<T>;
				p2->data = item;
				p2->next = nullptr;

				// 2.2. Направить указатели
				p2->next = head;
				head = p2;
			}

			// Увеличить количество элементов в стеке
			size++;
		}
		catch (bad_alloc e)
		{
			cout << e.what();
		}
	}

	// Вытянуть элемент из стека
	T Pop()
	{
		// 1. Проверка
		if (size == 0)
			return 0;

		// 2. Запомнить элемент, который будет возвращаться
		T item = head->data;

		// 3. Установить дополнительный указатель на вершину
		Node<T>* p = head;

		// 4. Переместить вершину
		head = head->next;

		// 5. Освободить память, выделенную под вершину стека
		delete p;

		// 6. Уменьшить количество элементов в стека
		size--;

		// 7. Вернуть элемент
		return item;
	}

private: //Внутренняя структура
	
	template <class T>
	struct Node
	{
		T data;
		Node<T>* next;
	};

	Node<T>* head; // указатель на вершину стека
	unsigned int size; // размер стека

	void Free()
	{
		// 1. Установить указатель на вершину стека
		Node<T>* p = head;

		// 2. Обход стека и освобождение памяти
		while (p != nullptr)
		{
			head = head->next;
			delete p;
			p = head;
			size--; // не обязательно
		}
	}
};


int main()
{
	Stack<int> s;
	int N, random, top, res = 0;
	srand(time(NULL));

	cout << "Please enter N: ";
	cin >> N;
	cout << endl;

	for (int i = 0; i < N; i++)
	{
		random = 10 + (rand() % 91);
		s.Push(random); // Свой пуш
	}

	while (s.IsEmpty() != 1) // Свой емпти
	{
		top = s.Pop();
		//Проверка работы 
		cout << top << endl;
		//Проверка остатка 2 от деления на 7
		if (top % 7 == 2) //svoy top
			res++;
	}


	cout << "Result is " << res;

	return 0;
}