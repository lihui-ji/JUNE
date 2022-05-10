#include "interpolate.hpp"
#include <stdexcept>
#include <string> 

void interpolateInplace (FaceField & faceValues, const CellField & cellValues, const Mesh & mesh, const Boundary & boundary, const std::string type){
    if (faceValues.length() != mesh.faceNumber()){
        throw std::invalid_argument("The face values should be size of face numbers in mesh in interpolate.");
    }    
    List <Matrix <double> > Ab = interpolate (cellValues, mesh, boundary, type);
    faceValues = (Ab[0] & cellValues) + Ab[1];
}

List <Matrix <double> > interpolate (const CellField & cellValues, const Mesh & mesh, const Boundary & boundary, const std::string type){
    List <Matrix <double> > ans (2);
    if (cellValues.length() != mesh.cellNumber()){
        throw std::invalid_argument("The cell values should be size of cell numbers in mesh in interpolate.");
    }
    if (type == "Linear"){
        ans = interpolateLinear (cellValues, mesh, boundary);
    }
    return ans;
}


List <Matrix <double> > interpolateLinear (const CellField & cellValues, const Mesh & mesh, const Boundary & boundary){
    List < Matrix <double> > Ab (2);
    Ab[0].reshape (mesh.faceNumber(), mesh.cellNumber());
    Ab[0].fill(0);
    Ab[1].reshape (mesh.faceNumber(), cellValues.width());
    Ab[1].fill(0);

    for (unsigned indFace = 0; indFace < mesh.faceNumber(); indFace++){
        int cellInd1 = (mesh.faces()[indFace] -> owners())[0];
        int cellInd2 = (mesh.faces()[indFace] -> owners())[1];
        double distance1 = mesh.cells() [cellInd1] -> distance (indFace);
        Vector <double> value1 (cellValues.row(cellInd1));
        if (cellInd2 <= -2){
            throw std::invalid_argument("Undefined or ill defined face location.");
        }
        else if (cellInd2 == -1){
            for (unsigned dimentionInd = 0; dimentionInd < cellValues.width(); dimentionInd++){
                std :: string variableName = cellValues.name() + (cellValues.width() == 1 ? "" : std::to_string(dimentionInd));
                std :: string boundaryType = boundary.getType (variableName, mesh.faces() [indFace] -> locationType());
                double boundaryValue = boundary.getValue (variableName, mesh.faces() [indFace] -> locationType());
                if (boundaryType == "Dirichlet") {
                    Ab[1][indFace][dimentionInd] = boundaryValue;
                }
                else if (boundaryType == "Neumann") {
                    Ab[0][indFace][cellInd1] = 1;
                    Ab[1][indFace][dimentionInd] = -boundaryValue * distance1;
                }
                else{
                    throw std::invalid_argument("Undefined or ill defined boundary condition (should be either Dirchlet or Neumann).");
                }
            }
        }
        else{
            double distance2 = mesh.cells() [cellInd2] -> distance (indFace);
            if (distance1 + distance2 <= 0){
                throw std::invalid_argument("Distance between two neighbouring cells is non-positive.");
            }
            Ab[0][indFace][cellInd1] = distance2/(distance1+distance2);
            Ab[0][indFace][cellInd2] = distance1/(distance1+distance2);
        }
    }
    return Ab;
}

void correctBoundary (CellField & cellValues, const Mesh & mesh, const Boundary & boundary){
    FaceField faceValues (mesh.faceNumber(), cellValues.width(), cellValues.name()+"f");
    interpolateInplace (faceValues, cellValues, mesh, boundary, "Linear");
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd++){
        if (mesh.checkCellBoundary(cellInd) == false){
            continue;
        }
        List <unsigned> faceInds (mesh.cells()[cellInd] -> faces());
        Vector <double> tempRow (cellValues.width());
        double ratio = 0;
        for (unsigned faceIndInd = 0; faceIndInd < faceInds.size(); faceIndInd++){
            unsigned faceInd = faceInds[faceIndInd];
            double currDistance = mesh.cells()[cellInd] -> distance(faceInd);
            ratio += 1.0/currDistance;
            tempRow = tempRow + faceValues.row(faceInd) * 1.0/currDistance;
        }
        cellValues[cellInd] = (tempRow * (1.0/ratio) ).toList();
    }
}