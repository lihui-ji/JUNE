#include "LabeledPoint.hpp"

LabeledPoint::LabeledPoint(unsigned label_, Point &point_)
    : Point(point_),label(label_){}

std::string LabeledPoint::type(){
    return "LabeledPoint";
}

std::ostream& operator << (std::ostream& os, const LabeledPoint& labeledPoint)
{
     os << labeledPoint.label << " ";
     os << static_cast <const Point&> (labeledPoint);  
     return os;
}