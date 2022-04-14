#include "DynamicList.hpp"

//constructor

template <class T> 
DynamicList <T> :: DynamicList () : List <T> (){}

template <class T> 
DynamicList <T> :: DynamicList (size_t size_) : List <T> (size_){}

template <class T> 
DynamicList <T> :: DynamicList (size_t size_, T* arr_) : List <T> (size_, arr_){}

template <class T> 
DynamicList <T> :: DynamicList(List<T> list_) : List <T> (list_){}

template <class T> 
DynamicList <T> :: DynamicList(DynamicList<T> & dynamicList_) : List <T> (dynamicList_.listSize, dynamicList_.arr){}

//print type
template <class T> 
std::string DynamicList<T> :: type() const{
    return "DynamicList";
}

// append a new value
template <class T> 
void DynamicList<T> :: append(T newValue){
    T* newarr = new T [(*this).listSize + 1];
    for (size_t ind = 0; ind < (*this).size(); ind++){
        newarr[ind] = (*this)[ind];
    }
    newarr[(*this).listSize] = newValue;
    delete [] (*this).arr;
    (*this).arr = newarr;
    (*this).listSize ++;
}

//assignment operator
template <class T> 
DynamicList<T>& DynamicList <T> :: operator= (const List<T> &rhs){
    if ((*this).size() != rhs.size()){
        T* newarr = new T [rhs.size()];
        delete [] (*this).arr;
        (*this).arr = newarr;
        (*this).listSize = rhs.size();
    }  
    for (size_t ind = 0; ind < (*this).size(); ind++){
        (*this)[ind] = (*this)[ind];
    }
    return *this;
}

//print operation
template<class T>
std::ostream& operator<<(std::ostream& os, const DynamicList<T> & dynamicList){
    os << static_cast <const List<T>&> (dynamicList); 
    return os;
}

template class DynamicList < unsigned >;
template std::ostream & operator << (std::ostream&, const DynamicList < unsigned > &);

template class DynamicList < double >;
template std::ostream & operator << (std::ostream&, const DynamicList < double > &);

template class DynamicList < bool >;
template std::ostream & operator << (std::ostream&, const DynamicList < bool > &);

template class DynamicList < std::string >;
template std::ostream & operator << (std::ostream&, const DynamicList < std::string > &);