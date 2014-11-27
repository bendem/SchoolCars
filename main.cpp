#include <iostream>

#include "collections/BaseList.hpp"
#include "collections/List.hpp"
#include "collections/SortedList.hpp"

using namespace std;

int main() {
    BaseList<int>* list = new List<int>();
    BaseList<int>* sortedList = new SortedList<int>();

    list->add(1);
    list->add(0);
    sortedList->add(1);
    sortedList->add(0);

    list->display();
    cout << endl << list->contains(-1) << list->contains(0) << list->contains(1) << list->contains(2) << endl;

    sortedList->display();
    cout << endl << sortedList->contains(-1) << sortedList->contains(0) << sortedList->contains(1) << sortedList->contains(2) << endl;

    return 0;
}
