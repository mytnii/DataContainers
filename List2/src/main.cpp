#include <iostream>

using namespace std;

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List<T>;
	}*Head, * Tail;
	size_t size;
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		/*---------------------Constructors------------------------*/

		BaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BaConstructor:\t" << this << endl;
#endif // DEBUG

		}

		/*----------------------Destructor---------------------------*/

		~BaseIterator()
		{
#ifdef DEBUG
			cout << "BaDestructor:\t" << this << endl;

#endif // DEBUG
		}

		/*----------------------Operators------------------------------*/
		virtual BaseIterator& operator++() = 0;
		virtual BaseIterator& operator--() = 0;
		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
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
public:
	class ConstIterator :public BaseIterator
	{
	public:
		/*--------------Constructors-------------------------*/

		ConstIterator(Element* Temp) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CoConstructors:\t" << this << endl;
#endif // DEBUG

		}

		/*----------------Destructor----------------------------*/

		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CoDestructor:\t" << this << endl;
#endif // DEBUG

		}

		/*------------------Operators------------------------------*/

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}


	};

	class Iterator :public ConstIterator
	{
	public:

		/*-------------------------------Constructors---------------------------*/

		Iterator(Element* Temp) :ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG

		}

		/*---------------------------------Destructor------------------------------*/

		~Iterator()
		{
#ifdef DEBUG
			cout << "IDEstructor:\t" << this << endl;
#endif // DEBUG

		}

		/*------------------------------------Operators------------------------------*/

		T& operator*()
		{
			return Temp->Data;
		}
	};

	class ConstReverseIterator :public BaseIterator
	{
	public:

		/*--------------------------------Constructors--------------------------------*/

		ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CoReIConstructor:\t" << this << endl;
#endif // DEBUG

		}

		/*----------------------------------Destructor---------------------------------*/

		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "CoReIDestructor:\t" << this << endl;
#endif // DEBUG

		}

		/*------------------------------------Operators---------------------------------*/

		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}

		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

	};

	class ReverseIterator :public ConstReverseIterator
	{
	public:

		/*-----------------------Constructors----------------------------------*/

		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ReIConstructor:\t" << this << endl;
#endif // DEBUG

		}

		/*--------------------------Destructor-------------------------------*/

		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "ReIDestructor:\t" << this << endl;
#endif // DEBUG

		}

		/*-----------------------------Operators-------------------------------*/

		T& operator*()
		{
			return Temp->Data;
		}
	};
#ifdef DEBUG
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
			cout << "IConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "IDestructor:\t" << this << endl;
		}

		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		bool operator!=(const ReverseIterator& other)
		{
			return this->Temp != other.Temp;
		}

		bool operator==(const ReverseIterator& other)
		{
			return this->Temp == other.Temp;
		}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

		operator bool()const
		{
			return Temp;
		}
	};

#endif // DEBUG

	/*---------------------Constructors-------------------------*/
	List();

	List(const std::initializer_list<T>& il);
	~List();

	/*------------------Adding elements------------------------*/
	void push_front(const T Data);
	void push_back(const T Data);

	void insert(const int index, const T Data);

	/*-----------------------Remowing elements-----------------------------------*/
	void pop_front();

	void pop_back();

	//void erase(const int index)
	//{
	//    if (index >= size)
	//    {
	//        cout << "Going beyond the list" << endl;
	//        return;
	//    }
	//    if (index == 0)
	//    {
	//        pop_front();
	//        return;
	//    }
	//    if (index == size - 1)
	//    {
	//        pop_back();
	//        return;
	//    }
	//    Element* Temp;

	//    if (index < size / 2)
	//    {
	//        
	//    }

	//}

	/*------------------------------Methods-------------------------------*/
	Iterator begin();
	Iterator end();

	ConstIterator cbegin()const;
	ConstIterator cend()const;


	ReverseIterator rbegin();
	ReverseIterator rend();

	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	void print()const;
	void revers_print()const;
};

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}

template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	cout << typeid(il.begin()).name() << endl;;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>List<T>::~List()
{
	// while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

/*------------------Adding elements------------------------*/

template<typename T>
void List<T>::push_front(const T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	if (Head)Head = Head->pPrev = new Element(Data, Head);
	++size;
}

template<typename T>
void List<T>::push_back(const T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		push_front(Data);
		return;
	}
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	++size;
}

template<typename T>
void List<T>::insert(const int index, const T Data)
{
	if (index > size)
	{
		cout << "Going beyond the list" << endl;
		return;
	}
	if (index == 0)
	{
		push_front(Data);
		return;
	}
	if (index == size)
	{
		push_back(Data);
		return;
	}

	Element* Temp;

	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; ++i)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; ++i)
		{
			Temp = Temp->pPrev;
		}
	}

	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	++size;
}

/*-----------------------Remowing elements-----------------------------------*/

template<typename T>
void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		--size;
		return;
	}

	if (Head)
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		--size;
	}
}

template<typename T>
void List<T>::pop_back()
{
	if (Head == Tail)
	{
		pop_front();
		return;
	}

	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	--size;
}

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>
typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}

template<typename T>
typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}

template<typename T>
void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << "\t" << Temp << "\t"
		<< Temp->Data << "\t" << Temp->pNext << endl;
	cout << "Количество элементов списка:\t" << size << endl;
}

template<typename T>
void List<T>::revers_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << "\t" << Temp << "\t"
		<< Temp->Data << "\t" << Temp->pNext << endl;
	cout << "Количество элементов списка:\t" << size << endl;
}
//#define BASE_CHECK
#define RANGE_BASED_FOR_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int size = 6;
	List list;
	for (int i = 0; i < size; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.revers_print();
	list.pop_front();
	list.print();
	list.push_back(123);
	list.print();
	list.pop_back();
	list.print();
	int index;
	cout << "Введите индекс добавляемого елемента:\t";
	cin >> index;
	list.insert(index, 123);
	list.print();
	list.revers_print();
#endif // B

#ifdef RANGE_BASED_FOR_LIST
	List<int> list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;

	for (List<int>::ReverseIterator it = list.rbegin(); it; ++it)
	{
		cout << *it << "\t";
	}
	cout << endl;
#endif // RAN

	List<double> d_list = { 2.5, 3.14, 5.2, 8.3 };

	for (double i : d_list)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
	{
		cout << *it << "\t";
	}
	cout << endl;

	List<std::string> s_list = { "Have", "a", "nice", "day" };

	for (std::string i : s_list)
	{
		cout << i << "\t";
	}
	cout << endl;

	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
	{
		cout << *it << "\t";
	}
	cout << endl;
}


