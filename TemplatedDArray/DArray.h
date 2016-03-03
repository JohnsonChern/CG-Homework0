#pragma once

#include <stdlib.h>
#include <iostream>

#define OK           1
#define ERROR        0

#ifdef OVERFLOW
#undef OVERFLOW
#define OVERFLOW -1
#endif


template <class dataType>
class DArray
{

private:
    dataType*   _pdata;
    int         _size;
    int         _max;

private:
    void init();
    void free();
    int expandArray(int nMaxSize);
    inline bool invalidataIndex(int nIndex);

public:
    DArray();
    DArray(int nSize, dataType tValue = 0);
    DArray(const DArray& arr);
    ~DArray();

    void print();
    int getSize();
    int getMax();
    int setSize(int nSize);

    dataType getAt(int nIndex);
    dataType operator[] (int nIndex) const;
    int setAt(int nIndex, dataType tValue);

    int pushBack(dataType tValue);
    int deleteAt(int nIndex);
    int insertAt(int nIndex, dataType tValue);

    DArray& operator=(const DArray& arr);

};


template <class dataType>
void DArray<dataType>::init() {

    this->_pdata = new dataType[2];
    if (this->_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        this->_size = 0;
        this->_max = 0;
        return;
    }

    this->_size = 0;
    this->_max = 2;

}


template <class dataType>
void DArray<dataType>::free() {

    if (this->_pdata != NULL)
        delete[] this->_pdata;

}


template <class dataType>
bool DArray<dataType>::invalidataIndex(int nIndex) {

    return nIndex >= 0 && nIndex < this->_size;

}


template <class dataType>
int DArray<dataType>::expandArray(int nMax) {

    if (nMax < this->_max) {
        std::cout << "invalid new max size!" << std::endl;
        return ERROR;
    }

    dataType *new_pdata = new dataType[nMax];
    if (new_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        return OVERFLOW;
    }

    for (int i = 0; i < this->_size; ++i)
        new_pdata[i] = this->_pdata[i];

    this->_max = nMax;
    delete[] this->_pdata;
    this->_pdata = new_pdata;

    return OK;

}


template <class dataType>
DArray<dataType>::DArray() {

    this->init();

}


template <class dataType>
DArray<dataType>::DArray(int nSize, dataType tValue) {

    this->_pdata = new dataType[this->_max];
    if (this->_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        this->_size = 0;
        this->_max = 0;
    }
    else {
        this->_size = nSize;
        this->_max = nSize * 2;
        for (int i = 0; i < this->_size; ++i)
            this->_pdata[i] = tValue;
    }

}


template <class dataType>
DArray<dataType>::DArray(const DArray& arr) {

    this->_pdata = new dataType[arr._max];
    if (this->_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        this->_size = 0;
        this->_max = 0;
    }
    else {
        this->_max = arr._max;
        this->_size = arr._size;
        for (int i = 0; i < this->_size; ++i)
            this->_pdata[i] = arr._pdata[i];
    }

}


template <class dataType>
DArray<dataType>::~DArray() {

    this->free();

}


template <class dataType>
void DArray<dataType>::print() {

    if (this->_max == 0) {
        std::cout << "null array!" << std::endl << std::endl;
        return;
    }

    if (this->_size == 0) {
        std::cout << "empty array!" << std::endl << std::endl;
        return;
    }

    for (int i = 0; i < this->_size; ++i)
        std::cout << this->_pdata[i] << std::endl;

    std::cout << std::endl;

}


template <class dataType>
int DArray<dataType>::getSize() {

    return this->_size;

}


template <class dataType>
int DArray<dataType>::getMax() {

    return this->_max;

}


template <class dataType>
int DArray<dataType>::setSize(int nSize) {

    if (nSize < 0) {
        std::cout << "invalid size!" << std::endl;
        return ERROR;
    }
    if (nSize <= this->_size) {
        this->_size = nSize;
        return OK;
    }
    if (nSize >= this->_max) {
        int new_max = this->_max * 2;
        while (new_max <= nSize)
            new_max *= 2;
        int tag = this->expandArray(new_max);
        if (tag != OK)
            return tag;
    }
    for (int i = this->_size; i < nSize; ++i)
        this->_pdata[i] = NULL;
    this->_size = nSize;

    return OK;

}


template <class dataType>
dataType DArray<dataType>::getAt(int nIndex) {

    if (this->invalidataIndex(nIndex))
        return this->_pdata[nIndex];
    else {
        std::cout << "invalid index!" << std::endl;
        return NULL;
    }

}


template <class dataType>
dataType DArray<dataType>::operator[] (int nIndex) const {

    return getAt(nIndex);

}


template <class dataType>
int DArray<dataType>::setAt(int nIndex, dataType tValue) {

    if (this->invalidateIndex(nIndex)) {
        this->_pdata[nIndex] = tValue;
    }
    else {
        std::cout << "invalid index!" << std::endl;
        return NULL;
    }

}


template <class dataType>
int DArray<dataType>::pushBack(dataType tValue) {

    if (this->_max == this->_size) {
        int tag = this->expandArray(this->_max * 2);
        if (tag != OK)
            return tag;
    }

    this->_pdata[this->_size++] = tValue;

}


template <class dataType>
int DArray<dataType>::deleteAt(int nIndex) {

    if (!this->invalidataIndex(nIndex)) {
        std::cout << "invalid index!" << std::endl;
        return ERROR;
    }

    for (int i = nIndex + 1; i < this->_size; ++i)
        this->_pdata[i - 1] = this->_pdata[i];

    --this->_size;
    return OK;

}


template <class dataType>
int DArray<dataType>::insertAt(int nIndex, dataType tValue) {

    if (nIndex != this->_size && this->invalidataIndex(nIndex) == false) {
        std::cout << "invalid index!" << std::endl;
        return ERROR;
    }

    if (this->_size == this->_max) {
        int tag = this->expandArray(this->_max * 2);
        if (tag != OK)
            return tag;
    }
    
    for (int i = this->_size; i > nIndex; --i)
        this->_pdata[i] = this->_pdata[i - 1];
    
    this->_pdata[nIndex] = tValue;
    ++this->_size;

    return OK;

}


template <class dataType>
DArray<dataType>& DArray<dataType>::operator= (const DArray& arr) {

    this->_max = arr._max;
    this->_size = arr._size;
    if (this->_max == 0) {
        this->_pdata = NULL;
        return *this;
    }

    this->_pdata = new dataType[this->_max];
    if (this->_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        this->_max = 0;
        this->_size = 0;
        return *this;
    }

    for (int i = 0; i < this->_size; ++i)
        this->_pdata[i] = arr._pdata[i];

    return *this;

}