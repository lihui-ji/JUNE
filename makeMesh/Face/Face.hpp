#ifndef Face_H
#define Face_H
#include <iostream>
#include "Point.hpp"
#include "Vector.hpp"
/* Face class */
// The face should be convex polygon
class Face : public List<unsigned>{
    private:
        Point faceCenter;
        double faceArea;
        Vector <double> faceNormalVector;
        void assignCenter (List<unsigned> & indList, Point** points);
        void assignArea (List<unsigned> & indList, Point** points);
        void assignNormalVector (List<unsigned> & indList, Point** points);
        void assignOwners (int firstOwner, int secondOwner);
        void assignMembers (List<unsigned> & indList, Point** points);
        List <int> faceOwners;
        unsigned numberPoints;
        std :: string faceLocationType;

    public:
        //constructor
        //Face();
        Face(List<unsigned> indList, Point** points);
        Face(Face &Face_);
        // convenient constructor for length 3 or 4 list (point or face)
        Face(unsigned x1, unsigned x2, unsigned x3, Point** points);
        Face(unsigned x1, unsigned x2, unsigned x3, unsigned x4, Point** points);
        /* member functions */        
        //add face owner
        //Note: once added, the face owner cannnot be modified
        void addOwner (int owner);
        //set location (internal or boundary types)
        void setLocation (std::string boundaryType);
        //get type
        std::string type() const;
        //print operation
        friend std::ostream& operator<<(std::ostream& os, Face& face);
        //return face center
        Point center();
        //return face area
        double area() const;
        //return face normal vector
        Vector <double> normalVector();
        //return points number
        unsigned pointsNumber() const;
        //return face owners
        List<int> owners();
        //return face locationType
        std::string locationType() const;        
        //describe face properties
        std :: string describe();
};
#endif /* Face_H */
