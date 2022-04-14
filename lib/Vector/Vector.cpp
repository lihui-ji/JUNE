#include "Vector.hpp"
#include <cmath>
#include <stdexcept>

template <class T>
Vector <T> :: Vector(): List<T>(3){} //default: 3D vector

template <class T>
Vector <T> :: Vector(T* arr_): List<T>(3, arr_){}

template <class T>
Vector <T> :: Vector(size_t vectorSize): List<T>(vectorSize){}

template <class T>
Vector <T> :: Vector(List<T> valueList): List<T>(valueList){}

template <class T>
Vector <T> :: Vector(Vector <T> &vector_): List<T>(3){
    for (int ind = 0; ind < 3; ind++){
        (*this)[ind] = vector_[ind];
    }    
}

template <class T>
Vector <T> :: Vector(T x, T y, T z): List<T>(3){
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

template <class T>
Vector <T> :: Vector(List<T> &startPoint, List<T> &endPoint): List<T>(3){
    (*this)[0] = endPoint[0] - startPoint[0];
    (*this)[1] = endPoint[1] - startPoint[1];
    (*this)[2] = endPoint[2] - startPoint[2];
}

template <class T>
std::string Vector <T> :: type() const{
    return "Vector";
}

template <class T>
double Vector <T> :: norm() const{
    double ans = 0;
    for (size_t ind = 0; ind < (*this).size(); ind++){
        ans += pow((double)(*this)[ind], 2);
    }    
    ans = sqrt(ans);
    return ans;
}

template <class T>
Vector <T> Vector <T> :: eleMultiply(Vector<T> rhs) const{
    if ((*this).size() != rhs.size()){
        throw std::invalid_argument("Size mismatch in Vector <T> Vector <T> :: eleMultiply(Vector<T> rhs) const.");
    }  
    Vector <T> ans (rhs.size());
    for (size_t ind = 0; ind < rhs.size(); ind++){
        ans [ind] = (*this)[ind] * rhs[ind];
    }
    return ans;
}

template <class T>
Vector <T> Vector <T> :: eleDivide(Vector<T> rhs) const{
    if ((*this).size() != rhs.size()){
        throw std::invalid_argument("Size mismatch in Vector <T> Vector <T> :: eleDivide(Vector<T> rhs) const.");
    }  
    Vector <T> ans (rhs.size());
    for (size_t ind = 0; ind < rhs.size(); ind++){
        ans [ind] = (*this)[ind] / rhs[ind];
    }
    return ans;
}

template <class T>
Vector <int> Vector <T> :: toInt() const{
    Vector <int> ans ((*this).size());
    for (size_t ind = 0; ind < (*this).size(); ind++){
        ans [ind] = (int) (*this)[ind];
    }    
    return ans;
}

template <class T>
Vector <double> Vector <T> :: toDouble() const{
    Vector <double> ans ((*this).size());
    for (size_t ind = 0; ind < (*this).size(); ind++){
        ans [ind] = (double) (*this)[ind];
    }    
    return ans;
}

template <class T>
Vector <unsigned> Vector <T> :: toUnsigned() const{
    Vector <unsigned> ans ((*this).size());
    for (size_t ind = 0; ind < (*this).size(); ind++){
        ans [ind] = (unsigned) (*this)[ind];
    }    
    return ans;
}

template <class T>
List <T> Vector <T> :: toList() const{
    List <T> ans ((*this).size());
    for (size_t ind = 0; ind < (*this).size(); ind++){
        ans [ind] = (*this) [ind];
    }
    return ans;    
}

template <class T>
std::ostream& operator << (std::ostream& os, const Vector <T> & vector)
{
     os << static_cast <const List<T>&> (vector);  
     return os;
}

/* overload operators*/
// element wise +
template <class T>
Vector <T> operator+(const Vector <T> & lhs, const Vector <T> & rhs){
    if (lhs.size() != rhs.size()){
        throw std::invalid_argument("Size mismatch in Vector <T> operator+(const Vector <T> & lhs, const Vector <T> & rhs).");
    }  
    Vector <T> ans(lhs.size());
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans[ind] = lhs[ind] + rhs[ind];
    }     
    return ans;
}

// add a value +
template <class T>
Vector <T> operator+(const Vector <T> & lhs, T rhs){
    Vector <T> ans (lhs.size());
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans [ind] = lhs[ind] + rhs;
    }     
    return ans;
}

// add a value +
template <class T>
Vector <T> operator+(T lhs, const Vector <T> & rhs){
    return rhs + lhs;
}

// element wise -
template <class T>
Vector <T> operator-(const Vector <T> & lhs, const Vector <T> & rhs){
    if (lhs.size() != rhs.size()){
        throw std::invalid_argument("Size mismatch in Vector <T> operator-(const Vector <T> & lhs, const Vector <T> & rhs).");
    }  
    Vector <T> ans(lhs.size());
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans[ind] = lhs[ind] - rhs[ind];
    }     
    return ans;
}

// substract a value -
template <class T>
Vector <T> operator-(const Vector <T> & lhs, T rhs){
    Vector <T> ans (lhs.size());
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans [ind] = lhs[ind] - rhs;
    }     
    return ans;
}

// value substract Vector
template <class T>
Vector <T> operator-(T lhs, const Vector <T> & rhs){
    Vector <T> ans (rhs.size());
    for (size_t  ind = 0; ind < rhs.size(); ind++){
        ans [ind] = lhs - rhs[ind];
    }     
    return ans;
}


// inner (dot) product *
template <class T>
T operator*(const Vector <T> & lhs, const Vector <T> & rhs){
    if (lhs.size() != rhs.size()){
        throw std::invalid_argument("Size mismatch in T operator*(const Vector <T> & lhs, const Vector <T> & rhs).");
    }  
    T ans = 0;
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans += lhs[ind] * rhs[ind];
    }     
    return ans;
}

// multiply a value *
template <class T>
Vector <T> operator*(const Vector <T> & lhs, T rhs){
    Vector <T> ans (lhs.size());
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans [ind] = lhs[ind] * rhs;
    }     
    return ans;
}

// multiply a value *
template <class T>
Vector <T> operator*(T lhs, const Vector <T> & rhs){
    return rhs * lhs;
}

// divided by a value /
template <class T>
Vector <T> operator/(const Vector <T> & lhs, T rhs){
    Vector <T> ans (lhs.size());
    for (size_t  ind = 0; ind < lhs.size(); ind++){
        ans [ind] = lhs[ind] / rhs;
    }     
    return ans;
}

// outer (cross) product &, restricted to length 3 vectors
template <class T>
Vector <T> operator&(const Vector <T> & lhs, const Vector <T> & rhs){
    if (lhs.size() != 3 || rhs.size() != 3){
        throw std::invalid_argument("Size wrong (should be 3 for both) in Vector <T> operator&(const Vector <T> & lhs, const Vector <T> & rhs)");
    }  
    Vector <T> ans(3);
    ans[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    ans[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    ans[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];  
    return ans;
}

template class Vector < double >;
template Vector < double > operator + (const Vector < double > &, const Vector < double > &);
template Vector <double> operator + (const Vector < double > &, double);
template Vector <double> operator + (double, const Vector < double > &);
template Vector < double > operator - (const Vector < double > &, const Vector < double > &);
template Vector <double> operator - (const Vector < double > &, double);
template Vector <double> operator - (double, const Vector < double > &);
template double operator * (const Vector < double > &, const Vector < double > &);
template Vector <double> operator * (const Vector < double > &, double);
template Vector <double> operator * (double, const Vector < double > &);
template Vector <double> operator / (const Vector < double > &, double);
template Vector < double > operator & (const Vector < double > &, const Vector < double > &);
template std::ostream & operator << (std::ostream &, const Vector < double > &);

template class Vector < bool >;
template std::ostream & operator << (std::ostream &, const Vector < bool > &);

template class Vector < unsigned >;
template Vector < unsigned > operator + (const Vector < unsigned > &, const Vector < unsigned > &);
template Vector < unsigned > operator + (const Vector < unsigned > &, unsigned);
template Vector < unsigned > operator + (unsigned, const Vector < unsigned > &);
template Vector < unsigned > operator - (const Vector < unsigned > &, const Vector < unsigned > &);
template Vector < unsigned > operator - (const Vector < unsigned > &, unsigned);
template Vector < unsigned > operator - (unsigned, const Vector < unsigned > &);
template unsigned operator * (const Vector < unsigned > &, const Vector < unsigned > &);
template Vector < unsigned > operator * (const Vector < unsigned > &, unsigned);
template Vector < unsigned > operator * (unsigned, const Vector < unsigned > &);
template Vector < unsigned > operator / (const Vector < unsigned > &, unsigned);
template Vector < unsigned > operator & (const Vector < unsigned > &, const Vector < unsigned > &);
template std::ostream & operator << (std::ostream&, const Vector < unsigned > &);