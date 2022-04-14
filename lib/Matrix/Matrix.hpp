#ifndef Matrix_H
#define Matrix_H
#include <iostream>
#include "List.hpp"
#include "Vector.hpp"

template<class T>
class Matrix; // forward declare to make function declaration possible
    
template<class T> // declaration
std::ostream & operator<<(std::ostream&, const Matrix<T>&);

template<class T> // declaration
Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs);

template<class T> // declaration
Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs);

// element wise multiplication
template<class T> // declaration
double operator* (const Matrix<T>& lhs, const Matrix<T>& rhs);

// standard matrix multiplication
template<class T> // declaration
Matrix<T> operator& (const Matrix<T>& lhs, const Matrix<T>& rhs);

/* This a Matrix base class from C++ array */
template <class T>
class Matrix : public List <List <T> >{
    private:
        size_t matrixLength;
        size_t matrixWidth;        
    public:
        // There's no constructor of Matrix()
        bool ifClose (T a, T b) const;
        void swap (size_t row1, size_t row2);
        Matrix(size_t length_, size_t width_);
        Matrix(size_t length_, size_t width_, T** arr_);
        Matrix(List <List <T> > listList_);
        Matrix(Matrix<T> & Matrix_);
        void setIdentity();
        Matrix <double> toDouble() const;
        std::string type() const;
        size_t length() const;
        size_t width() const;
        bool ifIdentity() const;
        bool ifSquare() const;
        double det() const;
        Vector<T> row(size_t rowInd_) const;
        Vector<T> col(size_t colInd_) const;
        Matrix<double> inverse () const;        
        Matrix<T>& operator = (const Matrix<T> &rhs);
        friend Matrix<T> operator+ <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
        friend Matrix<T> operator- <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
        // element wise multiplication
        friend double operator* <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
        // standard matrix multiplication
        friend Matrix<T> operator& <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
        friend std::ostream& operator<< <> (std::ostream& os, const Matrix<T> & Matrix);
};

#endif /* Matrix_H */