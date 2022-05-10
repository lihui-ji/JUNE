#ifndef CellGradField_H
#define CellGradField_H

#include <iostream>
#include "Matrix.hpp"
/* CellGradField class */
class CellGradField : public Matrix<Vector<double> >{
    private:
        std :: string fieldName;
    public:
        //constructor
        CellGradField(unsigned length_, unsigned width_, std :: string fieldName_);
        std :: string name() const;
        std :: string type() const;
        Matrix <double> flatten() const;
        CellGradField & operator = (const Matrix<Vector<double> > &rhs);
        friend std::ostream & operator<<(std::ostream& os, const CellGradField& field);
};

#endif /* CellGradField_H */