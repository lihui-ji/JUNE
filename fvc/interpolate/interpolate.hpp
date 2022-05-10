#ifndef interpolate_H
#define interpolate_H

#include "FaceField.hpp"
#include "CellField.hpp"
#include "Mesh.hpp"
#include "Boundary.hpp"

void interpolateInplace (FaceField & faceValues, const CellField & cellValues, const Mesh & mesh, const Boundary & boundary, const std::string type);
List <Matrix <double> > interpolate (const CellField & cellValues, const Mesh & mesh, const Boundary & boundary, const std::string type);
List <Matrix <double> > interpolateLinear (const CellField & cellValues, const Mesh & mesh, const Boundary & boundary);
void correctBoundary (CellField & cellValues, const Mesh & mesh, const Boundary & boundary);
#endif /* interpolate_H */