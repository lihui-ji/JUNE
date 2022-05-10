#ifndef FaceField_H
#define FaceField_H
#include <iostream>
#include "Matrix.hpp"
/* FaceField class */
class FaceField : public Matrix<double>{
    private:
        std :: string fieldName;
    public:
        //constructor
        FaceField(unsigned length_, unsigned width_, std :: string fieldName_);
        std :: string name() const;
        std :: string type() const;
        FaceField & operator = (const Matrix<double> &rhs);
        friend std::ostream & operator<<(std::ostream& os, const FaceField& field);
};
#endif /* FaceField_H */