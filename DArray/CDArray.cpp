#include "CDArray.h"
#include <stdlib.h>

void CDArray::init() {
    this->_pdata = new double[0];
    this->_size = 0;
}

void CDArray::free() {
    if (_pdata == NULL)
        return;
    delete[] _pdata;
}

bool CDArray::invalidateIndex(int nIndex) {

    return nIndex >= 0 && nIndex < _size;

}

CDArray::CDArray() {

    init();

}

CDArray::CDArray(int nSize, double dValue) {

    this->_size = nSize;
    this->_pdata = new double[nSize];
    if (this->_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
    }
    for (int i = 0; i < nSize; ++i) {
        _pdata[i] = 0.0;
    }

}

CDArray::CDArray(const CDArray& arr) {

    this->_size = arr._size;
    this->_pdata = new double[this->_size];
    if (this->_pdata == NULL)
        std::cout << "not enough memory!" << std::endl;
    for (int i = 0; i < this->_size; ++i)
        this->_pdata[i] = arr._pdata[i];

}

CDArray::~CDArray() {

    free();

}

void CDArray::print() {

    if (this->_size == 0) {
        std::cout << "empty array" << std::endl << std::endl;
        return;
    }
    for (int i = 0; i < this->_size; ++i) {
        std::cout << this->_pdata[i] << std::endl;
    }
    std::cout << std::endl;

}

int CDArray::getSize() {

    return this->_size;

}

int CDArray::setSize(int nSize) {

    if (nSize <= 0) {
        std::cout << "invalid size!" << std::endl;
        return -1;
    }
    
    double *new_pdata = new double[nSize];
    if (new_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        return -1;
    }

    for (int i = 0; i < nSize; ++i)
        new_pdata[i] = 0.0;
    
    int min_size = this->_size < nSize ? this->_size : nSize;
    for (int i = 0; i < min_size; ++i)
        new_pdata[i] = this->_pdata[i];

    delete[] this->_pdata;
    this->_pdata = new_pdata;
    this->_size = nSize;

    return 0;

}

double CDArray::getAt(int nIndex) {

    if (nIndex < 0 || nIndex >= this->_size) {
        std::cout << "invalid index!" << std::endl;
        return -1;
    }

    return this->_pdata[nIndex];

}

double CDArray::operator[](int nIndex) const {

    if (nIndex < 0 || nIndex >= this->_size) {
        std::cout << "invalid index!" << std::endl;
        return -1;
    }

    return this->_pdata[nIndex];

}

int CDArray::setAt(int nIndex, double dValue) {

    if (nIndex < 0 || nIndex >= this->_size) {
        std::cout << "invalid index" << std::endl;
        return -1;
    }

    this->_pdata[nIndex] = dValue;
    return 0;

}

int CDArray::pushBack(double dValue) {

    double *new_pdata = new double[this->_size + 1];
    if (new_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        return -1;
    }
    
    for (int i = 0; i < this->_size; ++i)
        new_pdata[i] = this->_pdata[i];

    new_pdata[this->_size++] = dValue;
    delete []this->_pdata;
    this->_pdata = new_pdata;

    return 0;

}

int CDArray::deleteAt(int nIndex) {

    if (nIndex < 0 || nIndex >= this->_size) {
        std::cout << "invalid index" << std::endl;
        return -1;
    }

    double *new_pdata = new double[this->_size - 1];
    if (new_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        return -1;
    }

    for (int i = 0; i < nIndex; i++)
        new_pdata[i] = this->_pdata[i];
    for (int i = nIndex + 1; i < this->_size; i++)
        new_pdata[i - 1] = this->_pdata[i];
    delete[] this->_pdata;
    this->_pdata = new_pdata;
    --this->_size;
    return 0;

}

int CDArray::insertAt(int nIndex, double dValue) {

    if (nIndex < 0 || nIndex > this->_size) {
        std::cout << "invalid index" << std::endl;
        return -1;
    }

    double *new_pdata = new double[this->_size + 1];
    if (new_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        return -1;
    }

    for (int i = 0; i < nIndex; ++i)
        new_pdata[i] = this->_pdata[i];
    for (int i = nIndex; i < this->_size; ++i)
        new_pdata[i + 1] = this->_pdata[i];
    new_pdata[nIndex] = dValue;

    delete[] this->_pdata;
    this->_pdata = new_pdata;
    this->_size = this->_size + 1;
    return 0;

}

CDArray& CDArray::operator=(const CDArray& arr) {

    this->_size = arr._size;
    if (this->_pdata != NULL)
    delete[] this->_pdata;

    this->_pdata = new double[this->_size];
    if (this->_pdata == NULL)
    std::cout << "not enough memory!" << std::endl;
    for (int i = 0; i < this->_size; ++i)
    this->_pdata[i] = arr._pdata[i];

    return *this;

}