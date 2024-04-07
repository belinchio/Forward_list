#include "List.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	
	List<int> lst;
	lst.push_front(13);
	lst.push_front(15);
	lst.push_front(17);
	lst.print();
	lst.pop_front();
	lst.print();
	lst.insert(lst.getNode(0), 100);
	lst.print();

	return 0;
}