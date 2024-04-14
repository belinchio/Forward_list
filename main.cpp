#include "SingleList.h"
#include <iostream>

template <typename Item>
void PrintList(const Forward_list<Item> &list) {
    std::cout << "[ ";
    for (const auto &item : list) {
        std::cout << item << ' ';
    }

    std::cout << ']' << std::endl;
}

int main() {
    Forward_list<int> l {1, 2, 3};
    PrintList(l);
    
    {
    auto it = l.find(2);
    l.insert_after(it, 4);
    PrintList(l);
    }

    {
    auto it = l.find(1);
    l.erase_after(it);
    PrintList(l);
    }


    l.push_front(5);
    l.push_back(6);
    PrintList(l);

    l.pop_front();
    PrintList(l);

    l.clear();
    PrintList(l);

    const Forward_list<int> cl {2, 4, 6};
    PrintList(cl);
}