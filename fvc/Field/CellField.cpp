#include "CellField.hpp"


CellField :: CellField (unsigned length_, unsigned width_, std :: string fieldName_) : Matrix <double> (length_, width_), fieldName(fieldName_){}

std :: string CellField :: name () const{
    return fieldName;
}

std :: string CellField :: type () const {
    return "CellField";
}

CellField & CellField :: operator = (const Matrix<double> &rhs){
    if ((*this).length() != rhs.length() || (*this).width() != rhs.width()){
        std::invalid_argument("Sizes of lists are different. in CellField & CellField :: operator = (const Matrix<double> &rhs)");
    }  
    for (unsigned ind = 0; ind < rhs.length(); ind++){
        (*this)[ind] = rhs[ind];
    }
    return *this;
}

std::ostream & operator<<(std::ostream& os, const CellField& field){
    os << field.type() << " " << field.name() << std :: endl;
    os << static_cast <const Matrix<double>&> (field);  
    return os;
}
