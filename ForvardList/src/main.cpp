#include <iostream>

using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter cout << "\n---------------------------------------------\n"

class Element
{
	int Data;
	Element* pNext;
	 static int count;
public:
	Element* get_pNext()const
	{
		return pNext;
	}
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}

	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;


class ForwardList
{
	Element* Head;
	unsigned int size;
public:
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
			push_front(0);
		}
	}

	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//------------------------Operators------------------------------

	int& operator[](const int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	const int& operator[](const int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	

	//-------------------------Addigng elements----------------------

	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			return push_front(Data);
		}
		/*Element* New = new Element(Data);*/
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		/*Temp->pNext = New;*/
		Temp->pNext = new Element(Data);
		size++;

	}
	void insert(int index, int Data)
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
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp++;
		}

		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;

	}

	//-----------------------Removing elements:----------------------
	void pop_front()
	{
		if (Head == nullptr)
		{
			return;
		}
		Element* Erased = Head;
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
		Element* Temp = Head;
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
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
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
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		/*for (Iterator Temp = Head; Temp != nullptr; Temp++)
		{
			cout << *Temp << endl;
		}*/
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}
};


class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{

	}

	~Iterator()
	{

	}


	Iterator& operator++()
	{
		Iterator old = *this;
		Temp = Temp->pNext;

		return old;
	}

	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int& operator*()const
	{
		return Temp->Data;
	}
};
//#define BASE_CHESK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK1
#define HOME_WORK_2

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
#endif // HOME_WORK_2
}