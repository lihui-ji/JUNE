#include <stdexcept>
#include "Cell.hpp"
#include <sstream>

Cell :: Cell (List<unsigned> indList, Face** faces): cellFacesNumber (indList.size()), cellFaceIndices(indList), cellFaceCenterDistances (indList.size()), cellFaceDirections (indList.size()){
    if (indList.size() <4){
        throw std::invalid_argument("Too small face number of cell (should >=4.");
    }    
    assignMembers (indList, faces);
}

Cell :: Cell (Cell &cell_): cellFacesNumber (cell_.facesNumber()), cellVolume (cell_.volume()), cellCenter (cell_.center()), cellFaceIndices(cell_.facesNumber()), cellFaceCenterDistances (cell_.facesNumber()), cellFaceDirections (cell_.facesNumber()){
    for (size_t indCellFace = 0; indCellFace < cellFacesNumber; indCellFace++){
        cellFaceIndices = cell_.face(indCellFace);
        cellFaceCenterDistances [indCellFace] = cell_.distance(indCellFace);
        cellFaceDirections [indCellFace] = cell_.direction(indCellFace);
    }
}

Cell :: Cell (unsigned f1, unsigned f2, unsigned f3, unsigned f4, Face** faces): cellFacesNumber (4), cellFaceIndices(4), cellFaceCenterDistances (4), cellFaceDirections (4){
    unsigned temp[4] = {f1, f2, f3, f4};
    List <unsigned> indList (4, temp);
    cellFaceIndices = indList;
    assignMembers (indList, faces);
}

Cell :: Cell (unsigned f1, unsigned f2, unsigned f3, unsigned f4, unsigned f5, unsigned f6, Face** faces): cellFacesNumber (6), cellFaceIndices(6), cellFaceCenterDistances (6), cellFaceDirections (6){
    unsigned temp[6] = {f1, f2, f3, f4, f5, f6};
    List <unsigned> indList (6, temp);
    cellFaceIndices = indList;
    assignMembers (indList, faces);
}

// private functions
void Cell :: assignMembers (List<unsigned> &  indList, Face** faces){
    cellVolume = 0; //then add subcell volumes up
    for (size_t indCellFace = 0; indCellFace < cellFacesNumber; indCellFace++){
        size_t faceInd = indList[indCellFace];
        cellCenter[0] += faces[faceInd] -> center()[0]/(double)cellFacesNumber;
        cellCenter[1] += faces[faceInd] -> center()[1]/(double)cellFacesNumber;
        cellCenter[2] += faces[faceInd] -> center()[2]/(double)cellFacesNumber;
    }
    for (size_t indCellFace = 0; indCellFace < cellFacesNumber; indCellFace++){
        size_t faceInd = indList[indCellFace];
        Point faceCenter (faces[faceInd] -> center());
        Vector <double> vector (cellCenter, faceCenter);
        double innerProduct = vector * faces[faceInd] -> normalVector();
        if (innerProduct >= 0){
            cellFaceDirections [indCellFace] = 1;
            cellFaceCenterDistances [indCellFace] = innerProduct;
        } 
        else{
            cellFaceDirections [indCellFace] = -1;
            cellFaceCenterDistances [indCellFace] = -innerProduct;  
        }
        cellVolume += cellFaceCenterDistances [indCellFace] * faces[faceInd] -> area() / 3;
    }
}

// public functions
Point Cell :: center() const{
    return cellCenter;
}
double Cell :: volume() const{
    return cellVolume;
}
std::string Cell :: type() const{
    return "Cell";
}
unsigned Cell :: facesNumber() const{
    return cellFacesNumber;
}
unsigned Cell :: face(unsigned indCellFace) const{
    return cellFaceIndices[indCellFace];
}
int Cell :: direction(unsigned indCellFace) const{
    return cellFaceDirections[indCellFace];
}
double Cell :: distance(unsigned indCellFace) const{
    return cellFaceCenterDistances[indCellFace];
}

List <unsigned> Cell :: faces() const{

    return List <unsigned> (cellFaceIndices);
}
List <int> Cell :: directions() const{
    return List <int> (cellFaceDirections);
}
List <double> Cell :: distances() const{
    return List <double> (cellFaceCenterDistances);
}

std::string Cell :: describe() const{
    std :: ostringstream ss;
    ss << "center " << center() << " volume " << volume();
    return ss.str();
}

std :: ostream & operator << (std :: ostream & os, Cell & cell){
    os << cell.describe() << std :: endl;
    os << "faces " << cell.faces();
    os << "face directions " << cell.directions();
    os << "distances from cell center to faces " << cell.distances() << std:: endl;
    return os;
}
