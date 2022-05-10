#include <stdexcept>
#include "Face.hpp"
#include "Vector.hpp"
#include <sstream>
// Face class constructor
//Face::Face() : List(4), faceOwners(2), faceLocationType("undefined"), numberPoints(4){}
// The points have to be clockwise or counterwise order

Face::Face(List<unsigned> indList, Point** points): List(indList), faceOwners(2), faceLocationType("undefined"){
    if (indList.size() <3){
        throw std::invalid_argument("Too small point number of face (should >=3.");
    }    
    numberPoints = indList.size();
    assignCenter (indList, points);
    assignArea (indList, points);
    assignNormalVector (indList, points);
    assignOwners (-2, -2);
}

// Face class copy constructor
Face::Face(Face &face_): 
    List<unsigned>(face_.size()), 
    faceCenter(face_.center()),
    faceArea(face_.area()), 
    faceNormalVector(face_.normalVector()),
    faceOwners(face_.owners()), 
    numberPoints (face_.pointsNumber()),
    faceLocationType(face_.locationType()){
    for (size_t ind = 0; ind < face_.size(); ind++){
        (*this)[ind] = face_[0];
    }
}

// convenient constructor for length 3 or 4 list (point or face)
Face::Face(unsigned x1, unsigned x2, unsigned x3, Point** points): List(3), faceOwners(2), numberPoints(3), faceLocationType("undefined"){
    (*this)[0] = x1;
    (*this)[1] = x2;
    (*this)[2] = x3;
    unsigned pointInds[3] = {x1, x2, x3};
    List <unsigned> indList (3, pointInds);
    assignMembers (indList, points);
}
Face::Face(unsigned x1, unsigned x2, unsigned x3, unsigned x4, Point** points): List(4), faceOwners(2), numberPoints(4), faceLocationType("undefined"){
    (*this)[0] = x1;
    (*this)[1] = x2;
    (*this)[2] = x3;
    (*this)[3] = x4;    
    unsigned pointInds[4] = {x1, x2, x3, x4};
    List <unsigned> indList (4, pointInds);
    assignMembers (indList, points);
}

/* private functions */
void Face:: assignCenter (List<unsigned> & indList, Point** points){
    double x = 0, y = 0, z = 0;
    for (size_t ind = 0; ind < indList.size(); ind++){
        unsigned currInd = indList [ind];
        x += (*points[currInd])[0];
        y += (*points[currInd])[1];
        z += (*points[currInd])[2];
    }
    
    faceCenter = Point(x/indList.size(), y/indList.size(), z/indList.size());
}

void Face:: assignArea (List<unsigned> & indList, Point** points){
    double area = 0;
    for (unsigned ind=0; ind < numberPoints; ind++){
        Vector <double> vector1 (faceCenter, *(points[indList[ind]]));
        Vector <double> vector2 (faceCenter, *(points[indList[(ind+1)%numberPoints]]));
        area += 0.5 * (vector1 & vector2).norm();
    }
    faceArea = area;
}

void Face:: assignNormalVector (List<unsigned> & indList, Point** points){
    Vector <double> vector1 (faceCenter, *(points[indList[0]]));
    Vector <double> vector2 (faceCenter, *(points[indList[1]]));
    faceNormalVector = (vector1 & vector2);
    faceNormalVector = faceNormalVector/faceNormalVector.norm();
    //std::cout << "in initialization faceNormalVector is " << faceNormalVector << std::endl;
}

void Face::assignOwners (int firstOwner, int secondOwner){
    faceOwners[0] = firstOwner;
    faceOwners[1] = secondOwner;
}

void Face::assignMembers (List<unsigned> & indList, Point** points){
    assignCenter (indList, points);
    assignArea (indList, points); 
    assignNormalVector (indList, points);
    assignOwners (-2, -2);
}


/* public functions */



void Face::addOwner (int owner){
    if (faceOwners.lookUp(owner) != -1){
        throw std::invalid_argument("The owner to add already exists.");
    }
    int ind = faceOwners.lookUp(-2);
    if (faceOwners.lookUp(-2) == -1){
        throw std::invalid_argument("The owner of current face is already full.");
    }
    if (owner == -1){
        ind = 1;
    }
    faceOwners [ind] = owner;
}

void Face::setLocation (std::string locationType){
    faceLocationType = locationType;
    if (locationType != "Internal"){
        faceOwners[1] = -1;
    }
}

std::string Face::type() const{
    return "Face";
}

//return face center
Point Face::center(){
    return faceCenter;
}

//return face area
double Face::area() const{
    return faceArea;
}

//return face normal vector
Vector <double> Face::normalVector(){
    return faceNormalVector;
}

//return points number
unsigned Face:: pointsNumber() const{
    return numberPoints;
}

//return face owners
List<int> Face:: owners(){
    return faceOwners;
}

//return face locationType
std::string Face:: locationType ()const{
    return faceLocationType;
}

//describe face properties
std :: string Face :: describe() {
    std :: ostringstream ss;
    ss << "center " << center() << " area " << area() << " normal vector " << normalVector() << " owners " << owners() << " locationType " << locationType();
    return ss.str();
}

std::ostream& operator << (std::ostream& os, Face& face)
{   
    os << face.describe() << std::endl;
    os << static_cast <const List<unsigned>&> (face);  
    return os;
}
