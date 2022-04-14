#ifndef List_H
#define List_H
#include <iostream>

template<class T>
class List; // forward declare to make function declaration possible

template<class T> // declaration
std::ostream& operator<<(std::ostream&, const List<T>&);

/* This a List base class from C++ array */
template <class T>
class List{
    protected:
        T *arr;
        size_t listSize;
    public:
        List();
        List(size_t size_);
        // unable to check size of given array
        List(size_t size_, T* arr_);
        List(List<T> & list_);
        List(const List<T> & list_);
        ~List();
        void resize(unsigned newSize);
        int lookUp(T targetValue);
        virtual std::string type() const;
        size_t size() const;
        T& operator [] (size_t index) const;
        virtual List<T>& operator = (const List<T> &rhs);
        bool operator== (const List<T> &rhs);
        bool operator!= (const List<T> &rhs);
        friend std::ostream& operator<< <>(std::ostream& os, const List<T> & list);
        friend std::ostream& operator<< <>(std::ostream& os, const List<T> & list);
};

#endif /* List_H */