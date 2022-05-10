#include "Point.hpp"
#include "Face.hpp"
#include "Cell.hpp"
#include "Mesh.hpp"
#include "List.hpp"
#include "DynamicList.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Boundary.hpp"
#include "interpolate.hpp"
#include "d.hpp"
#include "CellField.hpp"
#include "FaceField.hpp"
#include "CellGradField.hpp"
#include "FaceGradField.hpp"

int main(int argc, char **argv){
    std :: string dtInstruction = argv[1];
    double rho = 1000;
    Mesh mesh (Point (0,0,0), Point (0.1,0.1,0.1), Vector <double> (0.01,0.01,0.01), "test");
    CellField U (mesh.cellNumber(), 3, "U");
    CellField nu (mesh.cellNumber(), 1, "nu");
    CellField P (mesh.cellNumber(), 1, "P");
    CellGradField gradP (mesh.cellNumber(), 1, "P");
    U.fill(0);
    nu.fill(0.001);
    P.fill(0);
    FaceField Uf (mesh.faceNumber(), 3, "Uf");
    FaceField nuf (mesh.faceNumber(), 1, "nuf");
    FaceField Pf (mesh.faceNumber(), 1, "Pf");
    Boundary boundary("cavityTest");
    std :: cout << mesh;
    std :: cout << boundary;
    double dt = 0.001;
    unsigned N = 100;
    double t;
    CellField prevU = U;
    DynamicList <double> convergences;
    double convergence = 1;

    for (unsigned n = 0; n < N+1; n++){
        t = dt * n;
        prevU = U;
        if (n % 10 ==0){
            std :: cout << "************************************" << std :: endl;
            std :: cout << "n=" << n << std :: endl;
            if (dtInstruction == "transient"){
                std :: cout << "t=" << t << std :: endl;                
            }
            std :: cout << "U :" << std :: endl << U << std :: endl;
            std :: cout << "P :" << std :: endl << P << std :: endl;
            std :: cout << "************************************" << std :: endl;
            if (convergence < 0.000001 && dtInstruction == "steady"){
                break;
            }            
        }

        interpolateInplace (Uf, U, mesh, boundary, "Linear");
        interpolateInplace (nuf, nu, mesh, boundary, "Linear");
        interpolateInplace (Pf, P, mesh, boundary, "Linear");

        List < Matrix <double> > AbT (dT (U, dt, dtInstruction));
        List < Matrix <double> > AbAdv (dAdv (U, Uf, mesh, boundary, "Linear"));
        List < Matrix <double> > AbDiff (dDiff (nuf, U, mesh, boundary, "Linear"));
        List <Matrix <Vector <double> > > Abgrad (grad(U, mesh, boundary, "Linear"));
        gradP = (Abgrad[0] & P) + Abgrad[1].col(0);

        Matrix <double> H = AbT[0] + AbAdv[0] - AbDiff[0];
        Matrix <double> B = AbT[1] + AbAdv[1] - AbDiff[1]; 
        U = (H.inverse() & (gradP.flatten() * (-1/rho) - B));
        correctBoundary (U, mesh, boundary);
        List <Matrix <double> > AbDiffP (dDiff (P, mesh, boundary, "Linear"));
        Matrix <double> valueDdivdivuu (ddivdivuu (U, mesh, boundary, "Linear"));
        P = AbDiffP[0].inverse() & (valueDdivdivuu * (-rho) - AbDiffP[1]);
        correctBoundary (P, mesh, boundary);       
        convergence = (U-prevU).norm() / prevU.norm();
        std :: cout << "n = " << n << " convergence is " << convergence << std :: endl;
        convergences.append(convergence);
    }
    std :: cout << "convergence with time is " << convergences << std :: endl;
}