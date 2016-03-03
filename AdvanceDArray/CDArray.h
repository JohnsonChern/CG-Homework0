#pragma once

#include <iostream>
#include <stdlib.h>

class CDArray {

private:
    double* _pdata;
    int	    _size;
    int     _max;

private:
    void init();
    void free();
    int  expandArray(int nMaxSize);
    inline bool invalidateIndex(int nIndex); // check the validativity of nIndex

public:
    CDArray();
    CDArray(int nSize, double dValue = 0);  // construtor
    CDArray(const CDArray& arr);            // copy constructor
    ~CDArray();                             // destructor

    void print();
    int getSize();          // get the size of array
    int setSize(int nSize); // reset the size of array
                            // if nSize <= former size, truncate the first nSize elements of the former array as the new element
                            // if nSize > former size, default value of new elements is 0
    double getAt(int nIndex);
    double operator[] (int nIndex) const;
    int setAt(int nIndex, double dValue);

    int pushBack(double dValue); // add a new element to the end of the array
    int deleteAt(int nIndex);    // delete the element at the nIndex position
    int insertAt(int nIndex, double dValue);
    // insert dValue into the nIndex position

    CDArray& operator=(const CDArray& arr);

};