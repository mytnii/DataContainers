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

    /*---------------------Constructors-------------------------*/
    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    ~List()
    {
        while (Head)pop_front();
        cout << "LDestructor:\t" << this << endl;
    }

    /*------------------Adding elements------------------------*/
    void push_front(int Data)
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
    void push_back(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            push_front(Data);
            return;
        }
        Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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

    /*------------------------------Methods-------------------------------*/

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

void main()
{
    setlocale(LC_ALL, "");
    int size = 3;
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
}

