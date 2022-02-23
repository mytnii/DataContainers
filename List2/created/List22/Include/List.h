
#include <iostream>
using namespace std;

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();

		friend class List<T>;
	}*Head, * Tail;
	size_t size;
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		/*---------------------Constructors------------------------*/

		BaseIterator(Element* Temp);

		/*----------------------Destructor---------------------------*/

		~BaseIterator();

		/*----------------------Operators------------------------------*/
		virtual BaseIterator& operator++() = 0;
		virtual BaseIterator& operator--() = 0;

		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;

		const T& operator*()const;
		operator bool()const;
	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		/*--------------Constructors-------------------------*/

		ConstIterator(Element* Temp);

		/*----------------Destructor----------------------------*/

		~ConstIterator();

		/*------------------Operators------------------------------*/

		ConstIterator& operator++();

		ConstIterator operator++(int);

		ConstIterator& operator--();

		ConstIterator operator--(int);


	};

	class Iterator :public ConstIterator
	{
	public:

		/*-------------------------------Constructors---------------------------*/

		Iterator(Element* Temp);

		/*---------------------------------Destructor------------------------------*/

		~Iterator();

		/*------------------------------------Operators------------------------------*/

		T& operator*();
	};

	class ConstReverseIterator :public BaseIterator
	{
	public:

		/*--------------------------------Constructors--------------------------------*/

		ConstReverseIterator(Element* Temp);

		/*----------------------------------Destructor---------------------------------*/

		~ConstReverseIterator();

		/*------------------------------------Operators---------------------------------*/

		ConstReverseIterator& operator++();

		ConstReverseIterator operator++(int);

		ConstReverseIterator& operator--();

		ConstReverseIterator operator--(int);

	};

	class ReverseIterator :public ConstReverseIterator
	{
	public:

		/*-----------------------Constructors----------------------------------*/

		ReverseIterator(Element* Temp);
		/*--------------------------Destructor-------------------------------*/

		~ReverseIterator();

		/*-----------------------------Operators-------------------------------*/

		T& operator*();
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
