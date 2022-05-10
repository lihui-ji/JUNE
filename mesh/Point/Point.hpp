#ifndef Point_H
#define Point_H
#include <iostream>
#include "List.hpp"
/* Point class */
class Point : public List<double>{
    public:
        //constructor
        Point();
        virtual std::string type();
        Point(double* arr_);
        Point(Point &point_);
        Point(const Point &point_);
        Point(double x, double y, double z);
        friend std::ostream& operator<<(std::ostream& os, const Point& point);
};
#endif /* Point_H */
