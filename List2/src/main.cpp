#include <iostream>

using namespace std;

class List
{
    class Element
    {
        int Data;
        Element* pNext;
        Element* pPrev;
    public:
        Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
            Data(Data), pNext(pNext), pPrev(pPrev)
        {
            cout << "EConstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
        }
        friend class List;
    }*Head, * Tail;
    size_t size;
public:

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

    /*---------------------Constructors-------------------------*/
    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }

    List(const std::initializer_list<int>& il) :List()
    {
        cout << typeid(il.begin()).name() << endl;;
        for (int const* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }
    }
    ~List()
    {
       // while (Head)pop_front();
        while (Tail)pop_back();
        cout << "LDestructor:\t" << this << endl;
    }

    /*------------------Adding elements------------------------*/
    void push_front(const int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
        Head = Head->pPrev = new Element(Data, Head);
        ++size;
    }
    void push_back(const int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            push_front(Data);
            return;
        }
        Tail = Tail->pNext = new Element(Data, nullptr, Tail);
        ++size;
    }

    void insert(const int index, const int Data)
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

        Element* New = new Element(Data);
        New->pNext = Temp;
        New->pPrev = Temp->pPrev;
        Temp->pPrev->pNext = New;
        Temp->pPrev = New;
        ++size;
    }

    /*-----------------------Remowing elements-----------------------------------*/
    void pop_front()
    {
        if (Head == nullptr && Tail == nullptr)return;
        if (Head == Tail)
        {
            delete Head;
            Head = Tail = nullptr;
            --size;
            return;
        }
        Head = Head->pNext;
        delete Head->pPrev;
        Head->pPrev = nullptr;
        --size;
    }

    void pop_back()
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
Iterator begin()
{
    return Head;
}
Iterator end()
{
    return nullptr;
}
ReverseIterator rbegin()
{
    return Tail;
}
ReverseIterator rend()
{
    return nullptr;
}

    void print()const
    {
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp->pPrev << "\t" << Temp << "\t"
            << Temp->Data << "\t" << Temp->pNext << endl;
        cout << "Количество элементов списка:\t" << size << endl;
    }
    void revers_print()const
    {
        for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
            cout << Temp->pPrev << "\t" << Temp << "\t"
            << Temp->Data << "\t" << Temp->pNext << endl;
        cout << "Количество элементов списка:\t" << size << endl;
    }
};

//#define BASE_CHECK
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

    List list = { 3,5,8,13,21 };
    list.print();
    for (int i : list)
    {
        cout << i << "\t";
    }
    cout << endl;

    for (List::ReverseIterator it = list.rbegin(); it; ++it)
    {
        cout << *it << "\t";
    }
    cout << endl;
}


