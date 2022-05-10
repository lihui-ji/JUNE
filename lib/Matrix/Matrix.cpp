#include "Matrix.hpp"
#include <stdexcept>

template <class T>
Matrix <T> :: Matrix() : Matrix(0,0){}

template <class T>
Matrix <T> :: Matrix(size_t length_, size_t width_) : List <List <T> > (length_){
    matrixLength = length_;
    matrixWidth = width_;    
    for (size_t indLength = 0; indLength < matrixLength; indLength++){
        (*this).arr[indLength].resize(matrixWidth);
    }
}

template <class T>
Matrix <T> ::  Matrix(size_t length_, size_t width_, T** arr_) :  Matrix (length_, width_){
    for (size_t indLength = 0; indLength < length_; indLength++){
        for (size_t indWidth = 0; indWidth < width_; indWidth++){
            (*this)[indLength][indWidth] = arr_[indLength][indWidth];
        }
    }    
}

template <class T>
Matrix<T> :: Matrix(Vector <Vector <T> > vecVec_) : Matrix (vecVec_.size(), vecVec_[0].size() ){
    for (size_t indLength = 0; indLength < length(); indLength++){
        for (size_t indWidth = 0; indWidth < width(); indWidth++){
            (*this)[indLength][indWidth] = vecVec_[indLength][indWidth];
        }
    }  
}

template <class T>
Matrix<T> :: Matrix(List <List <T> > listList_) : List <List <T> > (listList_){
    matrixLength = listList_.size();
    matrixWidth = listList_[0].size();
    for (size_t indLength = 0; indLength < matrixLength; indLength++){
        if (listList_[indLength].size() != matrixWidth){
            throw std::invalid_argument("Sizes of lists are different.");
        }
    }
}


template <class T>
Matrix <T> ::  Matrix(Matrix<T> & Matrix_) :  Matrix (Matrix_.length(), Matrix_.width()){
    for (size_t indLength = 0; indLength < matrixLength; indLength++){
        for (size_t indWidth = 0; indWidth < matrixWidth; indWidth++){
            (*this)[indLength][indWidth] = Matrix_[indLength][indWidth];
        }
    }    
}

// resize matrix
template <class T> 
void Matrix <T> :: reshape (size_t length_, size_t width_){
    (*this).matrixLength = length_;
    (*this).matrixWidth = width_;
    if ((*this).size() != length_){
        (*this).resize(length_);
    } 
    for (size_t ind = 0; ind < (*this).size(); ind++){
        if ((*this)[ind].size() != width_){
            (*this)[ind].resize(width_);
        }
    }
}

template <class T>
void Matrix <T> :: setIdentity(){
    if (!ifSquare()){
        throw std::invalid_argument("Can't set matrix to identity for non-square matrix.");
    } 
    for (size_t indLength = 0; indLength < matrixWidth; indLength++){
        for (size_t indWidth = 0; indWidth < matrixWidth; indWidth++){
            (*this)[indLength][indWidth] = (indLength == indWidth? 1 : 0);
        }
    }   
}

template <class T>
void Matrix <T> :: fill(T value){
    for (size_t indLength = 0; indLength < matrixLength; indLength++){
        for (size_t indWidth = 0; indWidth < matrixWidth; indWidth++){
            (*this)[indLength][indWidth] = value;
        }
    }   
}

template <class T>
Matrix <double> Matrix <T> :: toDouble() const{
    Matrix <double> ans (matrixWidth, matrixLength);
    for (unsigned ind1 = 0; ind1 < matrixLength; ind1++){
        for (unsigned ind2 = 0; ind2 < matrixLength; ind2++){
            ans [ind1][ind2] = (double) (*this) [ind1][ind2];
        }
    }
    return ans;
}

template <class T>
bool Matrix <T> :: ifClose (T a, T b) const{
    return ( (a-b) < 0.000001 && (a-b) > -0.000001 );
}

template <class T>
void Matrix <T> :: swap (size_t row1, size_t row2){
    if (row1 >= matrixLength || row1 < 0 || row2 >= matrixLength || row2 < 0){
        throw std::invalid_argument("row index exceeds maximum value.");
    }
    if (row1 != row2){
        List <T> temp ((*this)[row1]);
        (*this)[row1] = (*this)[row2];
        (*this)[row2] = temp;                 
    }         
}

template <class T>
std::string Matrix <T> :: type() const{
    return "Matrix";
}

template <class T>
size_t Matrix <T> :: length() const{
    return matrixLength;
}

template <class T>
size_t Matrix <T> :: width() const{
    return matrixWidth;
}

template <class T>
bool Matrix <T> :: ifIdentity() const{
    if (matrixWidth != matrixLength){
        return false;
    }
    for (size_t indLength = 0; indLength < matrixWidth; indLength++){
        for (size_t indWidth = 0; indWidth < matrixWidth; indWidth++){
            T currValue =  (*this)[indLength][indWidth];
            if (indLength == indWidth){
                if (!ifClose(currValue-1.0, currValue*0.0)){
                    return false;
                }
            }
            else{
                if (!ifClose(currValue, currValue*0.0)){
                    return false;
                }                
            }
        }
    }    
    return true;
}

template <class T>
bool Matrix <T> :: ifSquare() const{
    return matrixWidth == matrixLength;
}

template <class T>
double Matrix <T> :: det() const{
    if (!ifSquare()){
        throw std::invalid_argument("Non-square matrix doesnot have det(). in double Matrix <T> :: det()");
    }    
    Matrix <double> toolMatrix (toDouble());
    for (unsigned ind1 = 0; ind1 < matrixWidth; ind1++){
        // first put non zero on top row
        for (unsigned ind2 = ind1; ind2 < matrixLength; ind2++){
            if (toolMatrix[ind1][ind1] == 0){
                if (toolMatrix[ind2][ind1] != 0 ){
                    toolMatrix.swap(ind1, ind2);
                }                
            }
        }
        if (toolMatrix[ind1][ind1] == 0){
            return 0;
        }
        for (unsigned ind3 = ind1 + 1; ind3 < matrixLength; ind3 ++){
            if (toolMatrix[ind3][ind1] != 0 && toolMatrix[ind1][ind1] != 0){
                toolMatrix[ind3] = (toolMatrix.row(ind3)- toolMatrix.row(ind1) * toolMatrix[ind3][ind1] / toolMatrix[ind1][ind1]).toList();
            }
        }
    }
    double ans = 1;
    for (unsigned ind4 = 0; ind4 < matrixLength; ind4++){
        ans *= toolMatrix[ind4][ind4];
    }
    return sqrt(ans);
}

template <class T>
double Matrix <T> :: norm() const{
    double ans = 0;
    for (unsigned indLength = 0; indLength < length(); indLength++){
        for (unsigned indWidth = 0; indWidth < width(); indWidth++){
            ans += ((*this)[indLength][indWidth] * (*this)[indLength][indWidth]);
        }
    }
    return sqrt(ans);
}

template <class T>
Vector<T> Matrix <T> :: row(size_t rowInd_) const{
    return Vector <T> ((*this)[rowInd_]);
}

template <class T>
Vector<T> Matrix <T> :: col(size_t colInd_) const{
    Vector <T> ans (matrixLength);
    for (size_t rowInd = 0; rowInd < matrixLength; rowInd ++){
        ans [rowInd] = (*this)[rowInd][colInd_];
    }
    return ans;
}

template <class T>
Matrix<double> Matrix <T> :: inverse() const{
    if (!ifSquare()){
        throw std::invalid_argument("Non-square matrix cannot be inversed.");
    }
    Matrix <double> toolMatrix (toDouble());
    Matrix <double> ans (matrixLength, matrixWidth);
    ans.setIdentity();

    for (unsigned ind1 = 0; ind1 < matrixWidth; ind1++){
        // first put non zero on top row
        for (unsigned ind2 = ind1; ind2 < matrixLength; ind2++){
            if (toolMatrix[ind1][ind1] == 0){
                if (toolMatrix[ind2][ind1] != 0 ){
                    toolMatrix.swap(ind1, ind2);
                    ans.swap(ind1, ind2);
                }                
            }
        }
        if (toolMatrix[ind1][ind1] == 0){
            throw std::invalid_argument("zero determinant matrix cannot be inversed."); 
        }
        ans[ind1] = (ans.row(ind1)/toolMatrix[ind1][ind1]).toList();
        toolMatrix[ind1] = (toolMatrix.row(ind1)/toolMatrix[ind1][ind1]).toList();
        for (unsigned ind3 = ind1 + 1; ind3 < matrixLength; ind3 ++){
            if (toolMatrix[ind3][ind1] != 0 && toolMatrix[ind1][ind1] != 0){
                ans[ind3] = (ans.row(ind3)- ans.row(ind1) * toolMatrix[ind3][ind1] / toolMatrix[ind1][ind1]).toList();
                toolMatrix[ind3] = (toolMatrix.row(ind3)- toolMatrix.row(ind1) * toolMatrix[ind3][ind1] / toolMatrix[ind1][ind1]).toList();  
            }
        }
    }
    for (unsigned ind4 = matrixWidth - 1; ind4 >= 1; ind4--){
        for (unsigned ind5 = ind4 - 1; (int)ind5 >= 0; ind5--){
            if (toolMatrix[ind5][ind4] != 0){
                ans[ind5] = (ans.row(ind5)- ans.row(ind4) * toolMatrix[ind5][ind4] / toolMatrix[ind4][ind4]).toList();
                toolMatrix[ind5] = (toolMatrix.row(ind5)- toolMatrix.row(ind4) * toolMatrix[ind5][ind4] / toolMatrix[ind4][ind4]).toList();
            }
        }
    }
    return ans;
}

//assignment operator
template <class T> 
Matrix<T> & Matrix <T> :: operator= (const Matrix<T> &rhs){
    (*this).reshape(rhs.length(), rhs.width());
    for (size_t ind = 0; ind < (*this).size(); ind++){
        (*this)[ind] = rhs[ind];
    }
    return *this;
}

/* overload operators*/
// element wise +
template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs){
    if (lhs.length() != rhs.length() || lhs.width() != rhs.width()){
        throw std::invalid_argument("Size mismatch.");
    }  
    Matrix<T> ans(lhs.length(), lhs.width());
    for (size_t indLength = 0; indLength < lhs.length(); indLength++){
        for (size_t indWidth = 0; indWidth < lhs.width(); indWidth++){
            ans[indLength][indWidth] = lhs[indLength][indWidth] + rhs[indLength][indWidth];
        }
    }    
    return ans;
}

// + Vector to each colomn
template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Vector<T>& rhs){
    if (lhs.length() != rhs.size()){
        throw std::invalid_argument("Size mismatch.");
    }  
    Matrix<T> ans(lhs.length(), lhs.width());
    for (size_t indLength = 0; indLength < lhs.length(); indLength++){
        for (size_t indWidth = 0; indWidth < lhs.width(); indWidth++){
            ans[indLength][indWidth] = lhs[indLength][indWidth] + rhs[indWidth];
        }
    }    
    return ans;
}

// element wise -
template <class T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs){
    if (lhs.length() != rhs.length() || lhs.width() != rhs.width()){
        throw std::invalid_argument("Size mismatch.");
    }  
    Matrix<T> ans(lhs.length(), lhs.width());
    for (size_t indLength = 0; indLength < lhs.length(); indLength++){
        for (size_t indWidth = 0; indWidth < lhs.width(); indWidth++){
            ans[indLength][indWidth] = lhs[indLength][indWidth] - rhs[indLength][indWidth];
        }
    }    
    return ans;
}

// inner product*
template <class T>
double operator*(const Matrix<T>& lhs, const Matrix<T>& rhs){
    if (lhs.length() != rhs.length() || lhs.width() != rhs.width()){
        throw std::invalid_argument("Size mismatch.");
    }  
    double ans;
    for (size_t indLength = 0; indLength < lhs.length(); indLength++){
        for (size_t indWidth = 0; indWidth < lhs.width(); indWidth++){
            ans += lhs[indLength][indWidth] * rhs[indLength][indWidth];
        }
    }    
    return ans;
}

// multiply a value *
template <class T>
Matrix<T> operator*(const Matrix<T>& lhs, const double& rhs){
    Matrix<T> ans(lhs.length(), lhs.width());
    for (size_t indLength = 0; indLength < lhs.length(); indLength++){
        for (size_t indWidth = 0; indWidth < lhs.width(); indWidth++){
            ans[indLength][indWidth] = lhs[indLength][indWidth] * rhs;
        }
    }    
    return ans;
}

// standard matrix multiplication &
template <class T>
Matrix<T> operator & (const Matrix<T>& lhs, const Matrix<double>& rhs){
    if (lhs.width() != rhs.length()){
        throw std::invalid_argument("Size mismatch.");
    }  
    Matrix<T> ans(lhs.length(), rhs.width());
    for (size_t indLength = 0; indLength < lhs.length(); indLength++){
        for (size_t indWidth = 0; indWidth < rhs.width(); indWidth++){
            ans[indLength][indWidth] = lhs.row(indLength) * rhs.col(indWidth);
        }
    }    
    return ans;
}

//print operation
template<class T>
std::ostream & operator<<(std::ostream& os, const Matrix<T> & matrix){
    os << matrix.type() << " " << matrix.length() << " X " << matrix.width() << std::endl;
    for (size_t indLength = 0; indLength < matrix.length(); indLength++){
        for (size_t indWidth = 0; indWidth < matrix.width(); indWidth++){
            os << matrix[indLength][indWidth];
            if (indWidth != matrix.width()-1){
                os << " ";
            }            
        }
        os << std::endl; 
    }   
    return os;
}

template class Matrix < double >;
template Matrix<double> operator+ (const Matrix<double>&, const Matrix<double>&);
template Matrix<double> operator+ (const Matrix<double>&, const Vector<double>&);
template Matrix<double> operator- (const Matrix<double>&, const Matrix<double>&);
template double operator* (const Matrix<double>&, const Matrix<double>&);
template Matrix <double> operator* (const Matrix<double>&, const double&);
template Matrix<double> operator& (const Matrix<double>&, const Matrix<double>&);
template std::ostream & operator << (std::ostream&, const Matrix < double > &);

template class Matrix < unsigned >;
template std::ostream & operator << (std::ostream&, const Matrix < unsigned > &);

template class Matrix < Vector <double> >;
template Matrix<Vector <double> > operator+ (const Matrix<Vector <double>>&, const Matrix<Vector <double>>&);
template Matrix<Vector <double> > operator+ (const Matrix<Vector <double>>&, const Vector<Vector <double>>&);
template Matrix<Vector <double> > operator- (const Matrix<Vector <double>>&, const Matrix<Vector <double>>&);
template Matrix <Vector <double> > operator* (const Matrix<Vector <double> >&, const double&);
template Matrix <Vector <double> > operator& (const Matrix<Vector <double> >&, const Matrix<double> &);
template std::ostream & operator << (std::ostream&, const Matrix < Vector <double> > &);