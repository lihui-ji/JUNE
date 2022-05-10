#ifndef Vector_H
#define Vector_H
#include <iostream>
#include "List.hpp"
/* Vector class */
template<class T>
class Vector; // forward declare to make function declaration possible
    
template<class T> // declaration
std::ostream& operator<< (std::ostream&, const Vector<T>&);

template<class T> // declaration
Vector <T> operator+ (const Vector <T> & lhs, const Vector <T> & rhs);

template<class T> // declaration
Vector <T> operator+ (const Vector <T> & lhs, T rhs);

template<class T> // declaration
Vector <T> operator+ (T rhs, const Vector <T> & lhs);

template<class T> // declaration
Vector <T> operator- (const Vector <T> & lhs, const Vector <T> & rhs);

template<class T> // declaration
Vector <T> operator- (const Vector <T> & lhs, T rhs);

template<class T> // declaration
Vector <T> operator- (T rhs, const Vector <T> & lhs);

template<class T> // declaration
T operator* (const Vector <T> & lhs, const Vector <double> & rhs);

template<class T> // declaration
Vector <T> operator* (const Vector <T> & lhs, double rhs);

template<class T> // declaration
Vector <T> operator* (double rhs, const Vector <T> & lhs);

template<class T> // declaration
Vector <T> operator/ (const Vector <T> & lhs, double rhs);

template<class T> // declaration
Vector <T> operator& (const Vector <T> & lhs, const Vector <T> & rhs);

template <class T>
class Vector : public List<T>{
    public:
        //constructor
        Vector();
        Vector(size_t vectorSize);
        Vector(List<T> valueList);
        Vector(T* arr_);
        Vector(Vector <T> & vector_);
        Vector(T x, T y, T z);
        Vector(List<T> startPoint, List<T> endPoint);

        std::string type() const;
        double norm() const;
        Vector <T> eleMultiply(Vector<T> rhs) const;
        Vector <T> eleDivide(Vector<T> rhs) const;
        Vector <int> toInt () const;
        Vector <double> toDouble () const;
        Vector <unsigned> toUnsigned () const;
        List <T> toList() const;
        operator double();
        bool operator< (const double &rhs);
        bool operator> (const double &rhs);
        friend Vector <T> operator+ <>(const Vector <T> & lhs, const Vector <T> & rhs);
        friend Vector <T> operator+ <>(const Vector <T> & lhs, T rhs);
        friend Vector <T> operator+ <>(T rhs, const Vector <T> & lhs);
        friend Vector <T> operator- <>(const Vector <T> & lhs, const Vector <T> & rhs);
        friend Vector <T> operator- <>(const Vector <T> & lhs, T rhs);
        friend Vector <T> operator- <>(T rhs, const Vector <T> & lhs);
        friend T operator* <>(const Vector <T> & lhs, const Vector <double> & rhs);
        friend Vector <T> operator* <>(const Vector <T> & lhs, double rhs);
        friend Vector <T> operator* <>(double rhs, const Vector <T> & lhs);
        friend Vector <T> operator/ <>(const Vector <T> & lhs, double rhs);
        friend Vector <T> operator& <>(const Vector <T> & lhs, const Vector <T> & rhs);
        friend std::ostream& operator<< <>(std::ostream& os, const Vector <T> & vector);
};
#endif /* Vector_H */
