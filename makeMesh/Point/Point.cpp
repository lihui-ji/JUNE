#include "Point.hpp"

Point::Point(): Point(0, 0, 0){}
Point::Point(double* arr_): List<double>(3, arr_){}
Point::Point(Point &point_): List<double>(3){
    for (int ind = 0; ind < 3; ind++){
        (*this)[ind] = point_[ind];
    }    
}
Point::Point(const Point &point_): List<double>(3){
    for (int ind = 0; ind < 3; ind++){
        (*this)[ind] = point_[ind];
    }    
}
Point::Point(double x, double y, double z): List<double>(3){
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}
std::string Point::type(){
    return "Point";
}

std::ostream& operator << (std::ostream& os, const Point& point)
{
     os << static_cast <const List<double>&> (point);  
     return os;
}