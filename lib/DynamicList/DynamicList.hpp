#ifndef DynamicList_H
#define DynamicList_H
#include <iostream>
#include "List.hpp"

template<class T>
class DynamicList; // forward declare to make function declaration possible

template<class T> // declaration
std::ostream& operator<<(std::ostream&, const DynamicList<T>&);

/* This a DynamicList class */
template <class T>
class DynamicList : public List <T> {
    public:
        DynamicList();
        DynamicList(size_t size_);
        DynamicList(size_t size_, T* arr_);
        DynamicList(List<T> list_);
        DynamicList(DynamicList<T> & dynamicList_);
        std::string type() const;
        void append(T newValue);
        // the overloading operators
        DynamicList<T>& operator = (const List<T> &rhs);
        friend std::ostream& operator<< <>(std::ostream& os, const List<T> & list);
};

#endif /* DynamicList_H */