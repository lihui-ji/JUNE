#include "d.hpp"
#include "interpolate.hpp"

List < Matrix <double> >  dT (CellField C, double dt, std :: string instruction){
    List < Matrix <double> > Ab (2);
    Ab[0].reshape (C.length(), C.length());
    Ab[1].reshape (C.length(), C.width());
    if (instruction == "steady"){
        Ab[0].fill(0);
        Ab[1].fill(0);
    }
    if (instruction == "transient"){
        Ab[0].setIdentity();
        Ab[0] = Ab[0] * (1/dt);
        Ab[1] = C * (-1/dt);        
    }
    return Ab;
}

List < Matrix <double> > dAdv (const CellField & C, const FaceField & Uf, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType){
    List <Matrix <double> > AbInterpolate (interpolate (C, mesh, boundary, interpolateType));
    List < Matrix <double> > Ab (2);
    Ab[0].reshape (mesh.cellNumber(), mesh.cellNumber());
    Ab[0].fill(0);
    Ab[1].reshape (mesh.cellNumber(), C.width());
    Ab[1].fill(0);
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd++){
        List <unsigned> faceInds (mesh.cells()[cellInd] -> faces());
        Vector <double> tempArow (Ab[0].row(cellInd));
        Vector <double> tempbrow (Ab[1].row(cellInd));
        for (unsigned faceIndInd = 0; faceIndInd < faceInds.size(); faceIndInd++){
            unsigned faceInd = faceInds[faceIndInd];
            double flux = (Uf.row(faceInd) * (mesh.faces()[faceInd] -> normalVector())) * (mesh.cells()[cellInd] -> direction(faceInd));
            tempArow = tempArow + AbInterpolate[0].row(faceInd) * flux;
            tempbrow = tempbrow + AbInterpolate[1].row(faceInd) * flux;
        }
    }
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd++){
        double ratio = 1/(mesh.cells()[cellInd] -> volume());
        Ab[0][cellInd] = ((Ab[0].row(cellInd)) * ratio).toList();
        Ab[1][cellInd] = ((Ab[1].row(cellInd)) * ratio).toList();
    }
    return Ab;
}

List < Matrix < Vector<double> > > grad (const CellField & C, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType){
    List <Matrix <double> > AbInterpolate (interpolate (C, mesh, boundary, interpolateType));
    List < Matrix <Vector <double> > > Ab (2);
    Ab[0].reshape (mesh.cellNumber(), mesh.cellNumber());
    Ab[0].fill(Vector<double>(0,0,0));
    Ab[1].reshape (mesh.cellNumber(), C.width());
    Ab[1].fill(Vector<double>(0,0,0));
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd++){
        List <unsigned> faceInds (mesh.cells()[cellInd] -> faces());
        Vector < Vector<double> > tempArow(Ab[0].row(cellInd));
        Vector < Vector<double> > tempbrow(Ab[1].row(cellInd));
        for (unsigned faceIndInd = 0; faceIndInd < faceInds.size(); faceIndInd++){
            unsigned faceInd = faceInds[faceIndInd];
            Vector <double> factorVector = (mesh.faces()[faceInd] -> normalVector()) * (mesh.faces()[faceInd] -> area()) * double((mesh.cells()[cellInd] -> direction(faceInd))) / (mesh.cells()[cellInd] -> volume());
            for (unsigned AcolInd = 0; AcolInd < Ab[0].width(); AcolInd++){
                tempArow[AcolInd] = tempArow[AcolInd] + AbInterpolate[0][faceInd][AcolInd] * factorVector;
            }
            for (unsigned bcolInd = 0; bcolInd < Ab[1].width(); bcolInd++){
                tempbrow[bcolInd] = tempbrow[bcolInd] + AbInterpolate[1][faceInd][bcolInd] * factorVector;
            }
        }
        Ab[0][cellInd] = tempArow.toList();
        Ab[1][cellInd] = tempbrow.toList();
    }
    return Ab;
}

List < Matrix <double> > dDiff (const FaceField & Kf, const CellField & C, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType){
    List <Matrix <Vector<double> > > gradAb (grad(C, mesh, boundary, interpolateType));
    List < Matrix <double> > Ab (2);
    Ab[0].reshape (mesh.cellNumber(), mesh.cellNumber());
    Ab[0].fill(0);
    Ab[1].reshape (mesh.cellNumber(), C.width());
    Ab[1].fill(0);
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd++){
        List <unsigned> faceInds (mesh.cells()[cellInd] -> faces());
        
        Vector < double > tempArow(Ab[0].row(cellInd));
        Vector < double > tempbrow(Ab[1].row(cellInd));
        for (unsigned faceIndInd = 0; faceIndInd < faceInds.size(); faceIndInd++){

            unsigned faceInd = faceInds[faceIndInd];
            int cellInd1 = (mesh.faces()[faceInd] -> owners())[0];
            int cellInd2 = (mesh.faces()[faceInd] -> owners())[1];
            Vector <double> faceVector =    (mesh.faces()[faceInd] -> normalVector()) 
                                            * (mesh.faces()[faceInd] -> area()) 
                                            * double(mesh.cells()[cellInd] -> direction(faceInd));
            Vector <Vector<double> > gradA1 = gradAb[0].row(cellInd1);
            Vector <Vector<double> > gradb1 = gradAb[1].row(cellInd1);
            double distance1 = mesh.cells() [cellInd1] -> distance (faceInd);
            if (cellInd2 <= -2){
                throw std::invalid_argument("Undefined or ill defined face location.");
            }
            else if (cellInd2 == -1){
                for (unsigned dimentionInd = 0; dimentionInd < C.width(); dimentionInd++){
                    std :: string variableName = C.name() + (C.width() == 1 ? "" : std::to_string(dimentionInd));
                    std :: string boundaryType = boundary.getType (variableName, mesh.faces() [faceInd] -> locationType());
                    double boundaryValue = boundary.getValue (variableName, mesh.faces() [faceInd] -> locationType());
                    if (boundaryType == "Dirichlet") {
                        Ab[0][cellInd][cellInd] = - (mesh.faces()[faceInd] -> area()) / distance1;
                        Ab[1][cellInd][dimentionInd] = boundaryValue * (mesh.faces()[faceInd] -> area()) / distance1;

                    }
                    else if (boundaryType == "Neumann") {
                        Ab[1][cellInd][dimentionInd] += faceVector * Vector <double> (boundaryValue, boundaryValue, boundaryValue) * Kf[faceInd][0];
                    }
                    else{
                        throw std::invalid_argument("Undefined or ill defined boundary condition (should be either Dirchlet or Neumann).");
                    }
                }
            }
            else{
                double distance2 = mesh.cells() [cellInd2] -> distance (faceInd);
                Vector <Vector<double> > gradA2 = gradAb[0].row(cellInd2);
                Vector <Vector<double> > gradb2 = gradAb[1].row(cellInd2);
                Vector <Vector<double> > gradAf = gradA1 + (gradA2-gradA1) * (distance1/(distance1+distance2));
                Vector <Vector<double> > gradbf = gradb1 + (gradb2-gradb1) * (distance1/(distance1+distance2));
                Vector <double> d (mesh.cells()[cellInd1] -> center(), mesh.cells()[cellInd2] -> center());
                Vector <double> Delta = ((d*faceVector)/(d*d)) * d;
                Vector <double> k = faceVector - Delta;
                for (unsigned cellIndSub = 0; cellIndSub < mesh.cellNumber(); cellIndSub++){

                    Ab[0][cellInd][cellIndSub] = Ab[0][cellInd][cellIndSub] + ((gradAf[cellIndSub] * Delta) + (gradAf[cellIndSub] * k)) * Kf[faceInd][0];
                }          
                for (unsigned dimentionInd = 0; dimentionInd < C.width(); dimentionInd++){
                    Ab[1][cellInd][dimentionInd] = Ab[1][cellInd][dimentionInd] + ((gradbf[dimentionInd] * Delta) + (gradbf[dimentionInd] * k)) * Kf[faceInd][0];
                }     
            }
        }
    }
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd++){
        double ratio = 1/(mesh.cells()[cellInd] -> volume());
        Ab[0][cellInd] = ((Ab[0].row(cellInd)) * ratio).toList();
        Ab[1][cellInd] = ((Ab[1].row(cellInd)) * ratio).toList();
    }
    return Ab;
}

List < Matrix <double> > dDiff (const CellField & C, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType){
    FaceField K (mesh.faceNumber(), 1, "K");
    K.fill(1);
    return dDiff (K, C, mesh, boundary, interpolateType);
}

Matrix <double> ddivdivuu (const CellField & U, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType){
    FaceField Uf (mesh.faceNumber(), 3, "Uf");
    interpolateInplace (Uf, U, mesh, boundary, "Linear");
    List < Matrix <double> > AbAdv (dAdv (U, Uf, mesh, boundary, "Linear"));
    Matrix <double> Adv ((AbAdv[0] & U) + AbAdv[1]);
    Matrix <double> ans (mesh.cellNumber(), 1);
    ans.fill(0);
    for (unsigned cellInd = 0; cellInd < mesh.cellNumber(); cellInd ++){
        List <unsigned> faceInds (mesh.cells()[cellInd] -> faces());     
        for (unsigned faceIndInd = 0; faceIndInd < faceInds.size(); faceIndInd++){
            unsigned faceInd = faceInds [faceIndInd];
            int cellInd1 = (mesh.faces()[faceInd] -> owners())[0];
            int cellInd2 = (mesh.faces()[faceInd] -> owners())[1];
            if (cellInd2 == -1){
                continue;
            }
            Vector <double> faceVector =    (mesh.faces()[faceInd] -> normalVector()) 
                                            * (mesh.faces()[faceInd] -> area()) 
                                            * double(mesh.cells()[cellInd] -> direction(faceInd));
            double distance1 = mesh.cells() [cellInd1] -> distance (faceInd);
            double distance2 = mesh.cells() [cellInd2] -> distance (faceInd);
            ans[cellInd][0] += faceVector * (Adv.row(cellInd1) + (Adv.row(cellInd2)-Adv.row(cellInd1)) * (distance1/(distance1+distance2)));
        }
        ans[cellInd][0] /= (mesh.cells()[cellInd] -> volume()); 
    }
    return ans;
}