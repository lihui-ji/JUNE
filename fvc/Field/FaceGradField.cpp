#include "FaceGradField.hpp"

FaceGradField :: FaceGradField (unsigned length_, unsigned width_, std :: string fieldName_) : Matrix <Vector<double> > (length_, width_), fieldName(fieldName_){}

std :: string FaceGradField :: name () const{
    return fieldName;
}

std :: string FaceGradField :: type () const {
    return "FaceGradField";
}

FaceGradField & FaceGradField :: operator = (const Matrix<Vector<double>> &rhs){
    if ((*this).length() != rhs.length() || (*this).width() != rhs.width()){
        std::invalid_argument("Sizes of lists are different. in FaceGradField & FaceGradField :: operator = (const Matrix<double> &rhs)");
    }  
    for (unsigned ind = 0; ind < rhs.length(); ind++){
        (*this)[ind] = rhs[ind];
    }
    return *this;
}

std::ostream & operator<<(std::ostream& os, const FaceGradField& field){
    os << field.type() << " " << field.name() << std :: endl;
    os << static_cast <const Matrix<Vector<double> >&> (field);  
    return os;
}
