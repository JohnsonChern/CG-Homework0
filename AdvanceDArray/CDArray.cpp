#include "CDArray.h"
#include <stdlib.h>

void CDArray::init() {
    this->_pdata = new double[2];
    this->_size = 0;
    this->_max = 2;
}

void CDArray::free() {
    if (_pdata == NULL)
        return;
    delete[] _pdata;
}

bool CDArray::invalidateIndex(int nIndex) {

    return nIndex >= 0 && nIndex < _size;

}

int CDArray::expandArray(int nMaxSize) {

    double *new_pdata = new double[nMaxSize];
    if (new_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
        return -1;
    }

    this->_max = nMaxSize;
    for (int i = 0; i < this->_size; ++i)
        new_pdata[i] = this->_pdata[i];

    delete[] this->_pdata;
    this->_pdata = new_pdata;

    return 0;

}

CDArray::CDArray() {

    init();

}

CDArray::CDArray(int nSize, double dValue) {

    this->_size = nSize;
    this->_max = nSize * 2;
    this->_pdata = new double[this->_max];
    if (this->_pdata == NULL) {
        std::cout << "not enough memory!" << std::endl;
    }
    for (int i = 0; i < this->_max; ++i) {
        _pdata[i] = 0.0;
    }

}

CDArray::CDArray(const CDArray& arr) {

    this->_size = arr._size;
    this->_max = arr._max;
    this->_pdata = new double[this->_max];
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

    // if nSize < _size, we need only modify _size to nSize
    if (nSize < this->_size) {
        this->_size = nSize;
        return 0;
    }

    // if nSize >= _size

    // if nSize > _max, we expand this array
    if (nSize > this->_max) {
        int new_max = this->_max * 2;
        while (new_max <= nSize)
            new_max *= 2;
        if (this->expandArray(new_max) == -1) {
            std::cout << "not enough memory!" << std::endl;
            return -1;
        }
    }
    
    // assign default value 0 to element between the original _size and nSize
    for (int i = this->_size; i < nSize; ++i)
        this->_pdata[i] = 0;

    // modify _size to nSize
    this->_size = nSize;

    return 0;

}

double CDArray::getAt(int nIndex) {

    if (!this->invalidateIndex(nIndex)) {
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

    if (!this->invalidateIndex(nIndex)) {
        std::cout << "invalid index" << std::endl;
        return -1;
    }

    this->_pdata[nIndex] = dValue;
    return 0;

}

int CDArray::pushBack(double dValue) {

    if (this->_size == this->_max) {
        if (this->expandArray(this->_max * 2) == -1) {
            std::cout << "not enough memory!" << std::endl;
            return -1;
        }
    }

    this->_pdata[this->_size++] = dValue;

    return 0;

}

int CDArray::deleteAt(int nIndex) {

    if (!this->invalidateIndex(nIndex)) {
        std::cout << "invalid index" << std::endl;
        return -1;
    }

    for (int i = nIndex + 1; i < this->_size; ++i)
        this->_pdata[i - 1] = this->_pdata[i];
    --this->_size;

    return 0;

}

int CDArray::insertAt(int nIndex, double dValue) {

    if (nIndex < 0 || nIndex > this->_size) {
        std::cout << "invalid index" << std::endl;
        return -1;
    }

    if (this->_size == this->_max) {
        if (this->expandArray(this->_max * 2) == -1) {
            std::cout << "not enough memory!" << std::endl;
            return -1;
        }
    }

    for (int i = this->_size; i > nIndex; --i)
        this->_pdata[i] = this->_pdata[i - 1];

    this->_pdata[nIndex] = dValue;
    ++this->_size;
   
    return 0;

}

CDArray& CDArray::operator=(const CDArray& arr) {

    this->_size = arr._size;
    this->_max = arr._max;

    if (this->_pdata != NULL)
        delete[] this->_pdata;

    this->_pdata = new double[this->_max];
    if (this->_pdata == NULL)
        std::cout << "not enough memory!" << std::endl;
    for (int i = 0; i < this->_size; ++i)
        this->_pdata[i] = arr._pdata[i];

    return *this;

}