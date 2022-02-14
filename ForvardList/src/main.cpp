#include <iostream>
#include<string>

using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter cout << "\n---------------------------------------------\n"

template<typename T>class ForwardList;
template<typename T>class Iterator;

template<typename T>
class Element
{
	T Data;
	Element<T>* pNext;
	 static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}

	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstryctor:\t" << this << endl;
	}

	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;

		return *this;
	}

	Iterator<T> operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;

		return old;
	}

	bool operator ==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	T& operator*()
	{
		return Temp->Data;
	}
	const T& operator*()const
	{
		return Temp->Data;
	}
	operator bool()const
	{
		return Temp;
	}
};

template<typename T>
class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:
	Element<T>* get_Head()const
	{
		return Head;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size)
	{
		this->Head = nullptr;
		this->size = 0;
		for (int i = 0; i < size; i++)
		{
			push_front(T());
		}
	}

	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		
		for (const T* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	ForwardList(const ForwardList<T>& other):ForwardList()
	{
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
	}

	Iterator<T> begin()
	{

		return Head;

	}

	Iterator<T> end()
	{

		return nullptr;

	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		while (Head)pop_front();
		for (Iterator<T> it = other.Head; it; ++it)
		{
			push_back(*it);
		}
	}

	//------------------------Operators------------------------------

	T& operator[](const int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	const T& operator[](const int index)const
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	

	//-------------------------Addigng elements----------------------

	void push_front(T Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			return push_front(Data);
		}
		/*Element* New = new Element(Data);*/
		Element<T>* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		/*Temp->pNext = New;*/
		Temp->pNext = new Element<T>(Data);
		size++;

	}
	void insert(int index, T Data)
	{
		if (Head == nullptr)
		{
			return push_front(Data);
		}
		if (index == 0)
		{
			return push_front(Data);
		}
		if (index > size)
		{
			return;
		}
		/*Element* New = new Element(Data);*/
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp++;
		}

		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;

	}

	//-----------------------Removing elements:----------------------
	void pop_front()
	{
		if (Head == nullptr)
		{
			return;
		}
		Element<T>* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)
		{
			return;
		}
		if (Head->pNext == nullptr)
		{
			return pop_front();
		}
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;

		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index > size)
		{
			return;
		}
		if (index == 0)
		{
			return pop_front();
		}
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element<T>* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}

	//Element& operator++()
	//{

	//	Element* old;
	//	Temp = Temp->pNext;

	//	return old;
	//}

	//------------------------Methods---------------------------------

	void print()const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		/*for (Iterator<T> Temp = Head; Temp != nullptr; Temp++)
		{
			cout << *Temp << endl;
		}*/
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}
};


//#define BASE_CHESK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK1
//#define HOME_WORK_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHESK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	/*list.push_back(123);
	list.print();
	list.pop_front();
	list.pop_back();*/
	int index;
	int value;
	cout << "Введите индек добавляемого элемента: ";
	cin >> index;
	cout << "Введите значение добовляемого элемента: ";
	cin >> value;

	list.insert(index, value);
	list.print();

	cout << "Введите индекс удаляемого элемента: ";
	cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHESK

	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/

#ifdef DESTRUCTOR_CHECK
	int n;
	cout << "Введите размер списка: " << endl;
	cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}

	cout << "Список заполнен" << endl;
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK1
	int n;
	cout << "Введите размер списка: " << endl;
	cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // H

#ifdef HOME_WORK_2
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	//for (Iterator it = list.get_Head(); it != nullptr; it++)
	//{
	//	cout << *it << tab;
	//}
#endif // HOME_WORK_2

	ForwardList<int> list = {3,5,8,13,21};
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	for (double i : d_list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<string> s_list = { "Have", "a", "nice", "day" };
	for (string i : s_list)
	{
		cout << i << tab;
	}
	cout << endl;

	//ForwardList<string> s_list2 = s_list;
	ForwardList<string> s_list2;
	s_list2 = s_list;
	for (string i : s_list2)
	{
		cout << i << tab;
	}
	cout << endl;
}