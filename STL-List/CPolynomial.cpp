#include "CPolynomial.h"

int CPolynomial::readFromFile(std::string file) {

    std::ifstream infile(file);
    if (!infile.is_open()) {
        std::cout << "cannot read from file " + file + "!" << std::endl;
        return ERROR;
    }

    if (infile.get() != 'P') {
        std::cout << "wrong file format!" << std::endl;
        return ERROR;
    }
    
    int nterm = 0;
    infile >> nterm;

    for (int i = 0; i < nterm; ++i) {
        Node new_node;
        infile >> new_node.degree >> new_node.cof;
        if (infile.bad()) {
            std::cout << "wrong file format!" << std::endl;
            infile.close();
            return ERROR;
        }

        if (new_node.cof == 0)
            continue;
        this->addOneTerm(new_node);
    }

    infile.close();
    return OK;

}


int CPolynomial::addOneTerm(Node term) {

    std::list<Node>::iterator j;
    int tag = NOT_FOUND;

    // insert the new_node into the polynomial
    for (j = this->_polynomial.begin(); j != this->_polynomial.end(); j++)
        if (j->degree == term.degree) {
            tag = FOUND;
            break;
        }

    if (tag == FOUND) {
        if ((j->cof += term.cof) == 0)
            this->_polynomial.erase(j);
    }
    else this->_polynomial.insert(j, term);

    return OK;
}


CPolynomial::CPolynomial() {

}


CPolynomial::CPolynomial(const std::string& file) {

    this->readFromFile(file);

}


CPolynomial::CPolynomial(double *cof, int *deg, int n) {

}


CPolynomial::CPolynomial(const std::vector<double>& cof, const std::vector<int>& deg) {

    if (cof.size != deg.size) {
        std::cout << "wrong input!" << std::endl;
    }
    else {
        std::vector<double>::const_iterator i = cof.begin;
        std::vector<int>::const_iterator j = deg.begin;
        for (; i != cof.end(); ++i, ++j) {
            Node term;
            if ((term.cof = *i) == 0)
                continue;
            term.degree = *j;
            this->addOneTerm(term);
        }
    }

}


CPolynomial::~CPolynomial() {

}

CPolynomial CPolynomial::operator+ (const CPolynomial &right) {

    std::list<Node>::const_iterator i;
    CPolynomial new_polynomial(*this);

    for (i = right._polynomial.begin(); i != right._polynomial.end(); ++i)
        new_polynomial.addOneTerm(*i);

    return new_polynomial;

}


CPolynomial CPolynomial::operator- (const CPolynomial &right) {

    std::list<Node>::const_iterator i;
    CPolynomial new_polynomial(*this);

    for (i = right._polynomial.begin(); i != right._polynomial.end(); ++i) {
        Node term;
        term.cof = (-1) * i->cof;
        term.degree = i->degree;
        new_polynomial.addOneTerm(*i);
    }

    return new_polynomial;

}


CPolynomial CPolynomial::operator* (const CPolynomial &right) {



}