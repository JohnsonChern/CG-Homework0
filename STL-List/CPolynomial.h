#pragma once

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define OK      1
#define ERROR   0
#ifdef OVERFLOW
#undef OVERFLOW
#define OVERFLOW -1
#endif // OVERFLOW
#define NOT_FOUND 0
#define FOUND 1

typedef struct Node {
    
    double cof;        // coefficient
    double degree;     // degree

} Node;


class CPolynomial {

private:
    std::list<Node> _polynomial;

private:
    int readFromFile(std::string file);
    int addOneTerm(Node term);

public:
    // constructor
    CPolynomial();
    CPolynomial(const std::string& file);
    CPolynomial(double *cof, int *deg, int n);
    CPolynomial(const std::vector<double>& cof, const std::vector<int>& deg);

    // destructor
    virtual ~CPolynomial();

    // overload
    CPolynomial operator+(const CPolynomial &right);
    CPolynomial operator-(const CPolynomial &right);
    CPolynomial operator*(const CPolynomial &right);
    CPolynomial& operator=(const CPolynomial &right);

    void print() const;

};

