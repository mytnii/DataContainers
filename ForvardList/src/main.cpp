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

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor" << this << endl;
	}

	Iterator& operator ++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator ++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}


	bool operator ==(const Iterator& other)const//for 
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()//for 
	{
		return Temp->Data;
	}
	const int& operator*()const//for 
	{
		return Temp->Data;
	}
};

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

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	/*------------------------Operators------------------------------*/

	int& operator[](int n)
	{
		Element* temp = Head;

		for (int i = 0; i < n; i++)++temp;
		return temp->Data;
	}
	const int& operator[](int n)const
	{
		Element* temp = Head;

		for (int i = 0; i < n; i++)++temp;
		return temp->Data;
	}

	//-------------------------Addigng elements----------------------

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			return push_front(Data);
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
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
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}

		New->pNext = Temp->pNext;
		Temp->pNext = New;
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
		if (index == size)
		{
			pop_back();
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

	//------------------------Methods---------------------------------

	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}

	void unique()
	{
		Element* Temp = Head;
		while (Temp)
		{
			Element* Erased = Head;
			Element* Temp2 = nullptr;
			while (Erased)
			{
				if (Temp == Erased || Temp->Data != Erased->Data)
				{
					Temp2 = Erased;
					Erased = Erased->pNext;
				}
				else
				{
					Temp2->pNext = Erased->pNext;
					delete Erased;
					Erased = Temp2->pNext;
					--size;
				}
			}
			Temp = Temp->pNext;
		}
	}

	void reverse()
	{
		Element* Temp = nullptr;

		while (Head)
		{
			Element* New = new Element(Head->Data);
			New->pNext = Temp;
			Temp = New;
			/*cout << Temp->Data << endl;*/
			/*Element* Erased = Head;
			Head = Head->pNext;
			delete Erased;*/
			pop_front();
		}
		/*while (Temp)
		{
			cout << Temp->Data << "\t";
			Temp = Temp->pNext;
		}*/
		Head = Temp;
	}


	friend void list_completion(ForwardList& list, const int size);
};

//#define BASE_CHESK
//#define DESTRUCTOR_CHECK
//#define HOME_WORC

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

#ifdef HOME_WORC
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
#endif // HOME_WORC

	
	int size;

	cout << "Введите размер списка: " << endl;
	cin >> size;

	ForwardList list;
	list_completion(list, size);
	list.print();

	list.push_back(9);
	list.print();


	list.unique();
	list.print();

	list.reverse();
	list.print();

}

void list_completion(ForwardList& list, const int size)
{
	for (int i = 0; i < size; i++)
	{
		list.push_front(rand() % 10);
	}
}