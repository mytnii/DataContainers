#include"List.h"
#include"List.cpp"


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


