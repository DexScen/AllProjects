#include <iostream>
#include <fstream>

using namespace std;

// Структура даты + перегрузка на сравнение дат
struct Time {
	int day = 0;
	int month = 0;
	int year = 0;


	bool operator== (const Time& b) {
		return this->day == b.day && this->month == b.month && this->year == b.year;
	}
};
// Структура одной записи о студенте
struct Entry {
	int course = 0, mark = 0;
	long number = 0;
	string code, surname, subject;
	struct Time date;
};
// Структура для возвращения массива из функции, и последующей работы с ним
struct Array {
	int arr[100];
	int Size = 0;
};

// Класс списка + нода в нем же
template<typename T>
class List 
{
public:
	
	List();
	~List();

	void clear();
	void pop_front();
	void push_back(T data);
	int getSize() { return Size; }
	void out();
	void sort(int type);
	struct Array search(long num);
	struct Array search(int num);
	struct Array search(Time t);

	T& operator[](const int index);

private:
	
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T data=T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}

	};
	int Size;
	Node<T>* head;
};
// Конструктор
template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}
// Деструктоp
template<typename T>
List<T>::~List()
{
	clear();
}
// Очистка списка
template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}
// Удаление элемента из начала
template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;
	delete temp;

	Size--;
}
// Добавление элемента в конец
template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}

	Size++;
}
// Вывод содержимого списка
template<typename T>
void List<T>::out()
{
	Node<T>* current = this->head;

	while (current != nullptr)
	{
		cout << "Course: " << current->data.course << endl;
		cout << "Group: " << current->data.code << endl;
		cout << "Surname: " << current->data.surname << endl;
		cout << "Date of start: " << current->data.date.day << '.' << current->data.date.month << '.' << current->data.date.year << endl;
		cout << "Card number: " << current->data.number << endl;
		cout << "Subject: " << current->data.subject << endl;
		cout << "Subject mark: " << current->data.mark << endl;
		cout << "--------------------------------------------------------------" << endl;
		current = current->pNext;
	}
}
// 3 вида сортировки (1) пузырьком
template<typename T>
void List<T>::sort(int type)
{
	Node<T>* current;
	if (type == 1) // sort by course
	{
		bool f = true;
		while (f)
		{
			f = false;
			current = this->head;
			while (current->pNext != nullptr)
			{
				if (current->data.course > current->pNext->data.course)
				{
					f = true;
					struct Entry temp = current->data;
					current->data = current->pNext->data;
					current->pNext->data = temp;
				}
				current = current->pNext;
			}
		}
	}
	if (type == 2) // sort by card number
	{
		bool f = true;
		while (f)
		{
			f = false;
			current = this->head;
			while (current->pNext != nullptr)
			{
				if (current->data.number > current->pNext->data.number)
				{
					f = true;
					struct Entry temp = current->data;
					current->data = current->pNext->data;
					current->pNext->data = temp;
				}
				current = current->pNext;
			}
		}
	}
	if (type == 3) // sort by date
	{
		bool f = true;
		while (f)
		{
			f = false;
			current = this->head;
			while (current->pNext != nullptr)
			{
				if (check(current->data.date, current->pNext->data.date))
				{
					f = true;
					struct Entry temp = current->data;
					current->data = current->pNext->data;
					current->pNext->data = temp;
				}
				current = current->pNext;
			}
		}
	}
}
// Поиск по карточке
template<typename T>
struct Array List<T>::search(long num)
{
	Node<T>* current = this->head;
	int i = 0, k = 0;
	struct Array res;
	while (current != nullptr)
	{
		if (current->data.number == num) {
			res.arr[k] = i;
			k++;
			res.Size++;
		}
		i++;
		current = current->pNext;
	}
	
	return res;
}
// Поиск по курсу
template<typename T>
struct Array List<T>::search(int num)
{
	Node<T>* current = this->head;
	int i = 0, k = 0;
	struct Array res;
	while (current != nullptr)
	{
		if (current->data.course == num) {
			res.arr[k] = i;
			k++;
			res.Size++;
		}
		i++;
		current = current->pNext;
	}

	return res;
}
// Поиск по дате
template<typename T>
struct Array List<T>::search(Time t)
{
	Node<T>* current = this->head;
	int i = 0, k = 0;
	struct Array res;
	while (current != nullptr)
	{
		if (current->data.date == t) {
			res.arr[k] = i;
			k++;
			res.Size++;
		}
		i++;
		current = current->pNext;
	}

	return res;
}
// Перегрузка для работы со списком как с массивом(не использовалась)
template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}
// Сравнение по времени
bool check(struct Time t1, struct Time t2)
{
	if (t1.year > t2.year)
	{
		return true;
	}
	else if ((t1.year == t2.year) && (t1.month > t2.month))
	{
		return true;
	}
	else if ((t1.month == t2.month) && (t1.day > t2.day))
	{
		return true;
	}
	return false;
}

int main()
{
	List<Entry> lst;
	Entry a;

	// input into OneLinkedList from file
	ifstream in("data.txt");
	if (in.is_open()) {
		while (!in.eof()) {
			in >> a.course >> a.code >> a.surname >> a.date.day >> a.date.month >> a.date.year >> a.number >> a.subject >> a.mark;
			lst.push_back(a);
		}
	}
	// output OneLinkedList
	cout << "One linked list contains: " << endl;
	lst.out();

	// TEST INPUT FOR SEARCH
	long testNumber = 62343321;
	int testCourse = 2;
	Time testTime = 
	{
		14, // day
		8, // month
		2021, // year
	};

	//START TESTING SEARCH
	cout << "==============================================================\nTESTING SEARCH : " << endl;
	struct Array arr = lst.search(testCourse);
	cout << "Indexes for search by Course: ";
	for (int i = 0; i < arr.Size; i++)
	{
		cout << arr.arr[i] << ' ';
	}
	cout << endl;
	arr = lst.search(testNumber);
	cout << "Indexes for search by Card Number: ";
	for (int i = 0; i < arr.Size; i++)
	{
		cout << arr.arr[i] << ' ';
	}
	cout << endl;
	arr = lst.search(testTime);
	cout << "Indexes for search by Date of start: ";
	for (int i = 0; i < arr.Size; i++)
	{
		cout << arr.arr[i] << ' ';
	}
	cout << endl;
	// END TESTING SEARCH

	// START TESTING SORT
	cout << "==============================================================\nTESTING SORT : " << endl;
	cout << "Sorting by Course: " << endl;
	lst.sort(1);
	lst.out();
	cout << "==============================================================\n";
	cout << "Sorting by Card Number: " << endl;
	lst.sort(2);
	lst.out();
	cout << "==============================================================\n";
	cout << "Sorting by Date: " << endl;
	lst.sort(3);
	lst.out();
	// END TESTING SORT
	
	// Проверка работы clear(не выводится ничего тк список становится пуст)
	lst.clear();
	lst.out();

	in.close();
}