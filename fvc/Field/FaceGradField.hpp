#ifndef FaceGradField_H
#define FaceGradField_H
#include <iostream>
#include "Matrix.hpp"
/* FaceGradField class */
class FaceGradField : public Matrix<Vector<double> >{
    private:
        std :: string fieldName;
    public:
        //constructor
        FaceGradField(unsigned length_, unsigned width_, std :: string fieldName_);
        std :: string name() const;
        std :: string type() const;
        FaceGradField & operator = (const Matrix<Vector<double> > &rhs);
        friend std::ostream & operator<<(std::ostream& os, const FaceGradField& field);
};
#endif /* FaceGradField_H */