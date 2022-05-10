#include "CellGradField.hpp"

CellGradField :: CellGradField (unsigned length_, unsigned width_, std :: string fieldName_) : Matrix <Vector<double> > (length_, width_), fieldName(fieldName_){}

std :: string CellGradField :: name () const{
    return fieldName;
}

std :: string CellGradField :: type () const {
    return "CellGradField";
}

Matrix <double> CellGradField :: flatten() const{
    if (width() !=1){
        std::invalid_argument("Higher order tensor cannot be expanded in Matrix <double> CellGradField :: flatten() const.");
    }
    Matrix <double> ans (length(), (*this)[0][0].size());
    for (unsigned indLength = 0; indLength < length(); indLength++){
        for (unsigned indWidth = 0; indWidth < (*this)[0][0].size(); indWidth++){
            ans[indLength][indWidth] = (*this)[indLength][0][indWidth];
        }
    }
    return ans;
}

CellGradField & CellGradField :: operator = (const Matrix<Vector<double>> &rhs){
    if ((*this).length() != rhs.length() || (*this).width() != rhs.width()){
        std::invalid_argument("Sizes of lists are different. in CellGradField & CellGradField :: operator = (const Matrix<double> &rhs)");
    }  
    for (unsigned ind = 0; ind < rhs.length(); ind++){
        (*this)[ind] = rhs[ind];
    }
    return *this;
}

std::ostream & operator<<(std::ostream& os, const CellGradField& field){
    os << field.type() << " " << field.name() << std :: endl;
    os << static_cast <const Matrix<Vector<double> >&> (field);  
    return os;
}
