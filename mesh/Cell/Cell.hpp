#ifndef Cell_H
#define Cell_H
#include "Point.hpp"
#include "List.hpp"
#include "Face.hpp"
#include "Vector.hpp"
/* Cell class */
class Cell{
    private:
        unsigned cellFacesNumber;
        double cellVolume;
        Point cellCenter;
        List <unsigned> cellFaceIndices;
        List <double> cellFaceCenterDistances;
        List <int> cellFaceDirections;            
        void assignMembers (List<unsigned> &  indList, Face**faces);
    public:
        Cell (List<unsigned> indList, Face** faces);
        Cell (Cell &cell_);
        Cell (unsigned f1, unsigned f2, unsigned f3, unsigned f4, Face** faces);
        Cell (unsigned f1, unsigned f2, unsigned f3, unsigned f4, unsigned f5, unsigned f6, Face** faces);
        
        Point center() const;
        double volume() const;
        std::string type() const;
        unsigned facesNumber() const;
        unsigned face(unsigned indCellFace) const;
        int direction(unsigned indFace) const;
        double distance(unsigned indFace) const;
        List <unsigned> faces() const;
        List <int> directions() const;
        List <double> distances() const;
        std::string describe() const;
        //print operation
        friend std::ostream& operator<<(std::ostream& os, Cell& cell);
};
#endif /* Cell_H */
