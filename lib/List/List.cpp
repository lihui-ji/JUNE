#include <stdexcept>
#include "List.hpp"
#include "Vector.hpp"
//constructor

template <class T> 
List <T> :: List(){
    listSize = 0;
    arr = new T [0];
}

template <class T> 
List <T> :: List(size_t size_){
    listSize = size_;
    arr = new T [size_];
}
template <class T> 
List <T> :: List(size_t size_, T* arr_){
    listSize = size_;
    arr = new T[size_];
    for (size_t listInd = 0; listInd < size_; listInd++){
        arr[listInd] = arr_[listInd];
    }
}
//copy instructor
template <class T> 
List <T> :: List(List<T>& list_){
    listSize = list_.size();
    arr = new T[listSize];
    for (size_t listInd = 0; listInd < listSize; listInd++){
        arr[listInd] = list_[listInd];
    }    
}

template <class T> 
List <T> :: List(const List<T> & list_){
    listSize = list_.size();
    arr = new T[listSize];
    for (size_t listInd = 0; listInd < listSize; listInd++){
        arr[listInd] = list_[listInd];
    }
}

//destructor

template <class T> 
List <T> :: ~List(){
    delete [] arr;
}

template <class T> 
void List <T> :: resize (unsigned newSize){
    T* newarr = new T [newSize];
    delete [] (*this).arr;
    (*this).arr = newarr;
    (*this).listSize = newSize;
}

// find first apperance index of value in list
template <class T> 
int List <T> :: lookUp(T targetValue){
    for (size_t ind = 0; ind < listSize; ind++){
        if (arr[ind] == targetValue){
            return (int)ind;
        }
    }
    return -1;
}

//print type
template <class T> 
std::string List<T> :: type() const{
    return "List";
}

//index operation
template <class T> 
T& List <T> :: operator[](size_t index) const{
    //std::cout << "List index operator is invoked." << std::endl;
    return arr[index];
} 

template <class T> 
bool List <T> :: operator!=(const List<T> &rhs){
  return ! ((*this) == rhs);
}

template <class T> 
bool List <T> :: operator==(const List<T> &rhs){
  if ((*this).size() != rhs.size()){
      return false;
  }
  for (size_t ind = 0; ind < rhs.size(); ind++){
      if ((*this)[ind] != rhs[ind]){
          return false;
      }
  }
  return true;
}

//assignment operator
template <class T> 
List<T>& List <T> :: operator= (const List<T> &rhs){
    if (this == &rhs){
        return *this;
    }
    if ((*this).size() != rhs.size()){
        throw std::invalid_argument("Size mismatch in assignment of List<T>& List <T>.");
    }  
    for (size_t ind = 0; ind < listSize; ind++){
        arr[ind] = rhs[ind];
    }
    //std::cout << "List assignment operator is invoked." << std::endl;
    return *this;
}

//get list size
template <class T> 
size_t List <T> :: size() const{
    return listSize;
}
//print operation
template<class T>
std::ostream& operator<<(std::ostream& os, const List<T> & list){
    size_t length = list.size();
    os << length << " " << "(";
    for (size_t index = 0; index < length; index++){
        os << list[index];
        if (index != length-1){
            os << " ";
        }
    }
    os << ")";
    return os;
}

// template class List < int >;
// template std::ostream & operator << (std::ostream&, const List < int > &);
template class List < int >;
template std::ostream & operator << (std::ostream&, const List < int > &);
template class List < double >;
template std::ostream & operator << (std::ostream&, const List < double > &);
template class List < unsigned >;
template std::ostream & operator << (std::ostream&, const List < unsigned > &);
template class List < bool >;
template std::ostream & operator << (std::ostream&, const List < bool > &);
template class List < std::string >;
template std::ostream & operator << (std::ostream&, const List < std::string > &);
template class List < Vector <double> >;
template std::ostream & operator << (std::ostream&, const List < Vector <double> > &);

template class List < List < unsigned > >;
template std::ostream & operator << (std::ostream&, const List < List < unsigned > > &);
template class List < List < double > >;
template std::ostream & operator << (std::ostream&, const List < List < double > > &);
template class List < List < bool > >;
template std::ostream & operator << (std::ostream&, const List < List < bool > > &);
template class List < List < std::string > >;
template std::ostream & operator << (std::ostream&, const List < List < std::string > > &);
template class List < List < int > >;
template std::ostream & operator << (std::ostream&, const List < List < int > > &);