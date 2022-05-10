#ifndef LabeledPoint_H
#define LabeledPoint_H
#include "Point.hpp"
/* LabeledPoint class */
class LabeledPoint : public Point{
    private:
        unsigned label;
    public:
        //constructor
        LabeledPoint(unsigned label_, Point &point_);
        std::string type();
        friend std::ostream& operator<<(std::ostream& os, const LabeledPoint& labeledPoint);
};
#endif /* LabeledPoint_H */