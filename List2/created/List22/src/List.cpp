
#include "list.h"

template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}


template<typename T>List<T>::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BaConstructor:\t" << this << endl;
#endif // DEBUG

}

/*----------------------Destructor---------------------------*/

template<typename T>List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BaDestructor:\t" << this << endl;

#endif // DEBUG
}

/*----------------------Operators------------------------------*/
//virtual BaseIterator& operator++() = 0;
//virtual BaseIterator& operator--() = 0;
template<typename T>bool List<T>::BaseIterator::operator==(const List<T>::BaseIterator& other)const
{
	return this->Temp == other.Temp;
}

template<typename T>bool List<T>::BaseIterator::operator!=(const List<T>::BaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}
template<typename T> List<T>::BaseIterator::operator bool()const
{
	return Temp;
}


template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CoConstructors:\t" << this << endl;
#endif // DEBUG

}

/*----------------Destructor----------------------------*/

template<typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "CoDestructor:\t" << this << endl;
#endif // DEBUG

}

/*------------------Operators------------------------------*/

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator:: operator++(int)
{
	ConstIterator old = *this;
	Temp = Temp->pNext;
	return old;
}

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	Temp = Temp->pPrev;
	return *this;
}

template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator:: operator--(int)
{
	ConstIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}


template<typename T>
List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CoReIConstructor:\t" << this << endl;
#endif // DEBUG

}

/*----------------------------------Destructor---------------------------------*/

template<typename T>
List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "CoReIDestructor:\t" << this << endl;
#endif // DEBUG

}

/*------------------------------------Operators---------------------------------*/

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator++()
{
	Temp = Temp->pPrev;
	return *this;
}

template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator++(int)
{
	ConstReverseIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator--()
{
	Temp = Temp->pNext;
	return *this;
}

template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator--(int)
{
	ConstReverseIterator old = *this;
	Temp = Temp->pNext;
	return old;
}

template<typename T>List<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp)
{
#ifdef DEBUG
	cout << "IConstructor:\t" << this << endl;
#endif // DEBUG

}

/*---------------------------------Destructor------------------------------*/

template<typename T>List<T>::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "IDEstructor:\t" << this << endl;
#endif // DEBUG

}

/*------------------------------------Operators------------------------------*/

template<typename T>
T& List<T>::Iterator::operator*()
{
	return Temp->Data;
}


template<typename T>
List<T>::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
{
#ifdef DEBUG
	cout << "ReIConstructor:\t" << this << endl;
#endif // DEBUG

}


template<typename T>
List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "ReIDestructor:\t" << this << endl;
#endif // DEBUG

}


template<typename T>
T& List<T>::ReverseIterator:: operator*()
{
	return Temp->Data;
}


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
