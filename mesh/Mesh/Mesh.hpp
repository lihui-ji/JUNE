#ifndef Mesh_H
#define Mesh_H
#include "Face.hpp"
#include "Cell.hpp"

/* Mesh class */
class Mesh{
    private:
        Point ** meshPoints;
        Face ** meshFaces;
        Cell ** meshCells;
        unsigned meshPointNumber;
        unsigned meshFaceNumber;
        unsigned meshCellNumber;
        std :: string meshProblemType;
        Vector <unsigned> rectPointIndToXyzInd (unsigned indPoint, Vector <unsigned> & sizeVector) const;
        unsigned rectXyzIndToPointInd (unsigned xInd, unsigned yInd, unsigned zInd, Vector <unsigned> & sizeVector) const;
        Vector < unsigned> rectCellIndToXyzInd (unsigned indCell, Vector <unsigned> & sizeVector) const;
        // note face indices range from 0 to 2Nx (Ny or Nz). Even index Indi means face points' indPointI is constant (not average to half)
        Vector <unsigned> rectFaceIndToXyzInd (unsigned indFace, Vector <unsigned> & sizeVector, Vector <unsigned> & faceLevelNumber) const;
        unsigned rectXyzIndToFacelInd (unsigned xInd, unsigned yInd, unsigned zInd, Vector <unsigned> & sizeVector, Vector <unsigned> & faceLevelNumber) const;
    public:
        // contructed from two corners 
        Mesh (Point corner1, Point corner2, Vector <double> cellSize, std::string problemType_);
        ~Mesh();
        // return the pointer of points
        Point** points () const;
        // return point number
        unsigned pointNumber () const;
        // return the pointer of faces
        Face** faces () const;
        // return face number
        unsigned faceNumber () const;
        // return the pointer of cells
        Cell** cells () const;
        // return cell number
        unsigned cellNumber () const;
        // check if cell is at boundary
        bool checkCellBoundary(unsigned cellInd) const;
        std :: string problemType () const;        
        // std::string describe();
        std :: string describe() const;
        void write();
        friend std::ostream& operator<< (std::ostream& os, const Mesh & mesh);
};
#endif /* Mesh_H */

