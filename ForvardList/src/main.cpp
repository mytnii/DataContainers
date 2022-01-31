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
public:
	ForwardList()
	{
		Head = nullptr;
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
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_bask()
	{
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
	}
	void insert(int index, int Data)
	{
		int count = 0;
		Element* Temp = Head;

		while (Temp)
		{
			Temp = Temp->pNext;
			count++;
		}

		if (index > count)
		{
			cout << "Выход за пределы списка" << endl;
			return;
		}
		if (index == 0 || Head == nullptr)
		{
			return push_front(Data);
		}

		Temp = Head;

		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}


		Temp->pNext = new Element(Data, Temp->pNext);
	}
	void erase(int index)
	{
		int count = 0;
		Element* Temp = Head;
		while (Temp)
		{
			Temp = Temp->pNext;
			count++;
		}
		if (index > count)
		{
			cout << "Элемента по заданному индексу не существует" << endl;
			return;
		}
		if (Head == nullptr)
		{
			cout << "В списке нету элементов" << endl;
			return;
		}

		Temp = Head;

		

		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}

		Element* erase = Temp->pNext;

		Temp = Head;

		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;

		Temp->pNext = erase;

		delete erase;
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
	cout << "Введите размер списка: "; cin >> n;
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
	delimiter;
	list.pop_front();
	delimiter;
	list.print();
	delimiter;
	list.pop_bask();
	delimiter;
	list.print();
	delimiter;
	
	int index;

	cout << "Введите индекс добавляемого элемента: ";
	cin >> index;

	list.insert(index, rand() % 100);
	delimiter;
	list.print();
	delimiter;

	cout << "Введите индекс удаляемого элемента:";
	cin >> index;

	list.erase(index);
	delimiter;
	list.print();

}