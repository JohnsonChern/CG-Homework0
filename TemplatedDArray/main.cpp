#include <iostream>
#include <stdlib.h>
#include "DArray.h"

int main() {

    DArray<double> a;
    a.insertAt(0, 2.1);
    a.print();

    a.pushBack(3.0);
    a.pushBack(3.1);
    a.pushBack(3.2);
    a.print();

    a.deleteAt(0);
    a.print();
    a.insertAt(0, 4.1);
    a.print();

    DArray<double> acopy = a;
    acopy.print();

    DArray<double> acopy2(a);
    acopy2.print();

    DArray<double> acopy3;
    acopy3 = a;
    acopy3.print();


    DArray<int> b;
    b.pushBack(21);
    b.print();
    b.deleteAt(0);
    b.print();
    b.pushBack(22);
    b.setSize(5);
    b.print();

    DArray<char> c;
    c.pushBack('a');
    c.pushBack('b');
    c.pushBack('c');
    c.insertAt(0, 'd');
    c.print();

    system("pause");
    return 0;

}