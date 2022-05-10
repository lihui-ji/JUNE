#ifndef d_H
#define d_H

#include "Matrix.hpp"
#include "Mesh.hpp"
#include "Boundary.hpp"
#include "List.hpp"
#include "CellField.hpp"
#include "FaceField.hpp"

List < Matrix <double> > dT (const CellField C, double dt, std :: string instruction);
List < Matrix <double> > dAdv (const CellField & C, const FaceField & Uf, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType);
List < Matrix < Vector<double> > > grad (const CellField & C, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType);
List < Matrix <double> > dDiff (const FaceField & Kf, const CellField & C, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType);
List < Matrix <double> > dDiff (const CellField & C, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType);
Matrix <double> ddivdivuu (const CellField & U, const Mesh & mesh, const Boundary & boundary, std :: string interpolateType);

#endif /* d_H */