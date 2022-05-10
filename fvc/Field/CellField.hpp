#ifndef CellField_H
#define CellField_H
#include <iostream>
#include "Matrix.hpp"
/* CellField class */
class CellField : public Matrix<double>{
    private:
        std :: string fieldName;
    public:
        //constructor
        CellField(unsigned length_, unsigned width_, std :: string fieldName_);
        std :: string name() const;
        std :: string type() const;
        CellField & operator = (const Matrix<double> &rhs);
        friend std::ostream & operator<<(std::ostream& os, const CellField& field);
};
#endif /* CellField_H */
