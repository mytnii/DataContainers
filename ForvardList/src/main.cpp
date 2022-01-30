#include <iostream>

using namespace std;

#define tab "\t"
#define delimiter cout << "\n---------------------------------------------\n\n"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}

	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
	int count;
public:
	ForwardList()
	{
		Head = nullptr;
		count = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//-------------------------Addigng elements----------------------

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			return push_front(Data);
		}
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
	}

	//------------------------Methods---------------------------------

	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	delimiter;
	list.print();
	delimiter;
	list.push_back(rand() % 100);
	delimiter;
	list.print();
}