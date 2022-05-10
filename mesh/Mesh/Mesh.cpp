# include <stdexcept>
# include "Mesh.hpp"
# include <sstream>
#include <fstream>
Vector <unsigned> Mesh :: rectPointIndToXyzInd (unsigned indPoint, Vector <unsigned> & sizeVector) const{
    return Vector <unsigned> (indPoint%((sizeVector[0]+1)*(sizeVector[1]+1))%(sizeVector[0]+1), indPoint%((sizeVector[0]+1)*(sizeVector[1]+1))/(sizeVector[0]+1), indPoint/((sizeVector[0]+1)*(sizeVector[1]+1)));
}

unsigned Mesh :: rectXyzIndToPointInd (unsigned xInd, unsigned yInd, unsigned zInd, Vector <unsigned> & sizeVector) const{
    return zInd * (sizeVector[0]+1) * (sizeVector[1]+1) + yInd * (sizeVector[0] + 1) + xInd;
}

Vector < unsigned> Mesh :: rectCellIndToXyzInd (unsigned indCell, Vector <unsigned> & sizeVector) const{
    Vector <unsigned> xyzIndCell;
    xyzIndCell [2] = indCell / (sizeVector[0] * sizeVector[1]);
    xyzIndCell [1] = indCell % (sizeVector[0] * sizeVector[1]) / sizeVector[0];
    xyzIndCell [0] = indCell % (sizeVector[0] * sizeVector[1]) % sizeVector[0];
    return xyzIndCell;
}

Vector <unsigned> Mesh :: rectFaceIndToXyzInd (unsigned indFace, Vector <unsigned> & sizeVector, Vector <unsigned> & faceLevelNumber) const{
    Vector <unsigned> xyzIndFace;
    unsigned indFaceLevel;
    if (indFace < faceLevelNumber[0]){
        indFaceLevel = indFace;
        xyzIndFace [0] = indFaceLevel / (sizeVector[1] * sizeVector[2]) * 2;
        xyzIndFace [2] = indFaceLevel % (sizeVector[1] * sizeVector[2]) / sizeVector[1] * 2 + 1;
        xyzIndFace [1] = indFaceLevel % (sizeVector[1] * sizeVector[2]) % sizeVector[1] * 2 + 1;
        
    }
    else if (indFace < faceLevelNumber[0] + faceLevelNumber[1]){
        indFaceLevel = indFace - faceLevelNumber[0];
        xyzIndFace [1] = indFaceLevel / (sizeVector[0] * sizeVector[2]) * 2;
        xyzIndFace [2] = indFaceLevel % (sizeVector[0] * sizeVector[2]) / sizeVector[0] * 2 + 1;
        xyzIndFace [0] = indFaceLevel % (sizeVector[0] * sizeVector[2]) % sizeVector[0] * 2 + 1;
    }
    else {
        indFaceLevel = indFace - faceLevelNumber[0] - faceLevelNumber[1];
        xyzIndFace [2] = indFaceLevel / (sizeVector[0] * sizeVector[1]) * 2;
        xyzIndFace [1] = indFaceLevel % (sizeVector[0] * sizeVector[1]) / sizeVector[0] * 2 + 1;
        xyzIndFace [0] = indFaceLevel % (sizeVector[0] * sizeVector[1]) % sizeVector[0] * 2 + 1;
    }
    return xyzIndFace;
}

unsigned Mesh :: rectXyzIndToFacelInd (unsigned xInd, unsigned yInd, unsigned zInd, Vector <unsigned> & sizeVector, Vector <unsigned> & faceLevelNumber) const{
    unsigned ans = 0;
    if (xInd % 2 == 0){
        ans += xInd/2 * sizeVector[1] * sizeVector[2] + (zInd-1)/2*sizeVector[1] + (yInd-1)/2; 
    }
    else if (yInd % 2 == 0){
        ans += yInd/2 * sizeVector[0] * sizeVector[2] + (faceLevelNumber[0] + (zInd-1)/2*sizeVector[0] + (xInd-1)/2);
    }
    else{
        ans += zInd/2 * sizeVector[0] * sizeVector[1] + (faceLevelNumber[0] + faceLevelNumber[1] + (yInd-1)/2*sizeVector[0] + (xInd-1)/2);
    }
    return ans;
}

Mesh :: Mesh (Point corner1, Point corner2, Vector <double> cellSize, std::string problemType_) : meshProblemType(problemType_) {
    Vector <double> sizeVectorDouble (corner1, corner2);
    for (unsigned ind = 0; ind < 3; ind++){
        sizeVectorDouble[ind] = sizeVectorDouble[ind]/  cellSize[ind];
    }
    Vector <unsigned> sizeVector  = sizeVectorDouble.toUnsigned();
    if (sizeVector.size() != 3 || sizeVector[0] <=0 || sizeVector[1] <=0 || sizeVector[2] <=0){
        throw std::invalid_argument("Either corner or cellSize is incorrect.");
    }
    meshPointNumber = (sizeVector[0] + 1) * (sizeVector[1]+1) * (sizeVector[2]+1);
    Vector <unsigned> faceLevelNumber ((sizeVector[0]+1)*sizeVector[1]*sizeVector[2], (sizeVector[1]+1)*sizeVector[0]*sizeVector[2], (sizeVector[2]+1)*sizeVector[0]*sizeVector[1]);
    meshFaceNumber = faceLevelNumber[0] + faceLevelNumber[1] + faceLevelNumber[2];
    meshCellNumber = sizeVector[0] * sizeVector[1] * sizeVector[2];
    meshPoints = new Point* [meshPointNumber];
    for (size_t indPoint = 0; indPoint < pointNumber(); indPoint++){
        Vector <unsigned> pointXyzInd = rectPointIndToXyzInd (indPoint, sizeVector);
        meshPoints [indPoint] = new Point (cellSize[0]*pointXyzInd[0], cellSize[1]*pointXyzInd[1], cellSize[2]*pointXyzInd[2]);
    }
    meshFaces = new Face* [meshFaceNumber];
    for (unsigned indFace = 0; indFace < faceNumber(); indFace++){
        Vector <unsigned> faceXyzInd = rectFaceIndToXyzInd (indFace, sizeVector, faceLevelNumber);
        unsigned point1Ind, point2Ind, point3Ind, point4Ind;
        unsigned faceIndX = faceXyzInd[0], faceIndY = faceXyzInd[1], faceIndZ = faceXyzInd[2];
        // The points have to be clockwise or counterwise order
        if (faceIndX % 2 == 0){
            point1Ind = rectXyzIndToPointInd (faceIndX/2, (faceIndY-1)/2, (faceIndZ-1)/2, sizeVector);
            point2Ind = rectXyzIndToPointInd (faceIndX/2, (faceIndY-1)/2, (faceIndZ+1)/2, sizeVector);
            point3Ind = rectXyzIndToPointInd (faceIndX/2, (faceIndY+1)/2, (faceIndZ+1)/2, sizeVector);
            point4Ind = rectXyzIndToPointInd (faceIndX/2, (faceIndY+1)/2, (faceIndZ-1)/2, sizeVector);
        }
        if (faceIndY % 2 == 0){
            point1Ind = rectXyzIndToPointInd ((faceIndX-1)/2, faceIndY/2, (faceIndZ-1)/2, sizeVector);
            point2Ind = rectXyzIndToPointInd ((faceIndX-1)/2, faceIndY/2, (faceIndZ+1)/2, sizeVector);
            point3Ind = rectXyzIndToPointInd ((faceIndX+1)/2, faceIndY/2, (faceIndZ+1)/2, sizeVector);
            point4Ind = rectXyzIndToPointInd ((faceIndX+1)/2, faceIndY/2, (faceIndZ-1)/2, sizeVector);
        }
        if (faceIndZ % 2 == 0){
            point1Ind = rectXyzIndToPointInd ((faceIndX-1)/2, (faceIndY-1)/2, faceIndZ/2, sizeVector);
            point2Ind = rectXyzIndToPointInd ((faceIndX-1)/2, (faceIndY+1)/2, faceIndZ/2, sizeVector);
            point3Ind = rectXyzIndToPointInd ((faceIndX+1)/2, (faceIndY+1)/2, faceIndZ/2, sizeVector);
            point4Ind = rectXyzIndToPointInd ((faceIndX+1)/2, (faceIndY-1)/2, faceIndZ/2, sizeVector);
        }
        meshFaces [indFace] = new Face (point1Ind, point2Ind, point3Ind, point4Ind, meshPoints);
        if (faceIndX == 0){
            meshFaces [indFace] -> setLocation ("Left");
        }
        else if (faceIndX == sizeVector[0] * 2){
            meshFaces [indFace] -> setLocation ("Right");
        }
        else if (faceIndY == 0){
            meshFaces [indFace] -> setLocation ("Front");
        }
        else if (faceIndY == sizeVector[1] * 2){
            meshFaces [indFace] -> setLocation ("Back");
        }
        else if (faceIndZ == 0){
            meshFaces [indFace] -> setLocation ("Bottom");
        }
        else if (faceIndZ == sizeVector[2] * 2){
            meshFaces [indFace] -> setLocation ("Top");
        }
        else{
            meshFaces [indFace] -> setLocation ("Internal");
        }
    }
    meshCells = new Cell* [meshCellNumber];
    for (unsigned indCell = 0; indCell < cellNumber(); indCell++){
        Vector <unsigned> cellXyzInd = rectCellIndToXyzInd (indCell, sizeVector);
        unsigned cellIndX = cellXyzInd[0];
        unsigned cellIndY = cellXyzInd[1];
        unsigned cellIndZ = cellXyzInd[2];
        unsigned faceInd1 = rectXyzIndToFacelInd (cellIndX*2, cellIndY*2+1, cellIndZ*2+1, sizeVector, faceLevelNumber);
        unsigned faceInd2 = rectXyzIndToFacelInd ((cellIndX+1)*2, cellIndY*2+1, cellIndZ*2+1, sizeVector, faceLevelNumber);
        unsigned faceInd3 = rectXyzIndToFacelInd (cellIndX*2+1, cellIndY*2, cellIndZ*2+1, sizeVector, faceLevelNumber);
        unsigned faceInd4 = rectXyzIndToFacelInd (cellIndX*2+1, (cellIndY+1)*2, cellIndZ*2+1, sizeVector, faceLevelNumber);
        unsigned faceInd5 = rectXyzIndToFacelInd (cellIndX*2+1, cellIndY*2+1, cellIndZ*2, sizeVector, faceLevelNumber);
        unsigned faceInd6 = rectXyzIndToFacelInd (cellIndX*2+1, cellIndY*2+1, (cellIndZ+1)*2, sizeVector, faceLevelNumber);
        unsigned faceIndsRaw [6] = {faceInd1, faceInd2, faceInd3, faceInd4, faceInd5, faceInd6};
        List <unsigned> faceInds (6, faceIndsRaw);
        meshCells [indCell] = new Cell (faceInds, meshFaces);
        for (unsigned faceIndInd = 0; faceIndInd < 6; faceIndInd++){
            meshFaces[faceInds[faceIndInd]] -> addOwner ((int)indCell);
        }
    }
}

Mesh :: ~Mesh (){
    for (size_t indPoint = 0; indPoint < pointNumber(); indPoint++){
        delete meshPoints[indPoint];
    } 
    delete [] meshPoints;
    for (size_t indFace = 0; indFace < faceNumber(); indFace++){
        delete meshFaces[indFace];
    } 
    delete [] meshFaces;
    for (size_t indCell = 0; indCell < cellNumber(); indCell++){
        delete meshCells[indCell];
    } 
    delete [] meshCells;
}

Point** Mesh :: points () const{
    return meshPoints;
} 

unsigned Mesh :: pointNumber () const{
    return meshPointNumber;
} 

Face** Mesh :: faces () const{
    return meshFaces;
} 

unsigned Mesh :: faceNumber () const{
    return meshFaceNumber;
} 

bool Mesh :: checkCellBoundary(unsigned cellInd) const{
    if (cellInd >= cellNumber()){
        throw std::invalid_argument("The cellInd is out of mesh in bool Mesh :: checkCellBoundary(unsigned cellInd) const.");
    }
    List <unsigned> faceInds (cells()[cellInd] -> faces());
    for (unsigned faceIndInd = 0; faceIndInd < faceInds.size(); faceIndInd++){
        unsigned faceInd = faceInds[faceIndInd];
        if (faces()[faceInd] -> locationType() != "Internal"){
            return true;
        }
    }
    return false;
}

std :: string Mesh :: problemType () const{
    return meshProblemType;
}

Cell** Mesh :: cells () const{
    return meshCells;
} 

unsigned Mesh :: cellNumber () const{
    return meshCellNumber;
} 

std :: string Mesh :: describe() const{
    std :: ostringstream ss;
    ss << "Mesh problem type: " << problemType()  << "; Points of mesh: " << pointNumber() << "; Faces of mesh: " << faceNumber();
    return ss.str();
}

void Mesh :: write(){
    std :: ofstream meshOutput("mesh.txt");
    meshOutput << *this;
    meshOutput.close();
}


std :: ostream & operator << (std::ostream & os, const Mesh & mesh){
    os << mesh.describe() << std :: endl;
    os << std :: endl << "Points of mesh: " << mesh.pointNumber() << std :: endl;
    for (size_t indPoint = 0; indPoint < mesh.pointNumber(); indPoint++){
        os << indPoint << " " << *(mesh.points() [indPoint]) << std :: endl;
    }
    os << std :: endl << "Faces of mesh: " << mesh.faceNumber() << std :: endl;
    for (size_t indFace = 0; indFace < mesh.faceNumber(); indFace++){
        os << indFace << " " << *(mesh.faces() [indFace]);
        for (size_t ind = 0; ind < 4; ind++){
            size_t indtemp = (*(mesh.faces() [indFace]))[ind];
            os << " " << *(mesh.points() [indtemp]);
        }
        os << std :: endl;
    }
    os << std :: endl << "Cells of mesh: " << mesh.cellNumber() << std :: endl;
    for (size_t indCell = 0; indCell < mesh.cellNumber(); indCell++){
        os << indCell << " " << *(mesh.cells() [indCell]);
        os << std :: endl;
    }
    return os;
}

