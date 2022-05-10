#ifndef Boundary_H
#define Boundary_H

#include "List.hpp"
#include "Mesh.hpp"

/* the Boundary class documents the boundary condition of the problem */
/* For Neumann boundary condition, the flux is always pointing outward (specify negative value for inward flux)*/
class Boundary{
    private:
        List <std :: string> locations;
        List <std :: string> variables;
        List <List <std :: string> > types;
        List <List <double> > values;
    public:
        Boundary (unsigned locationNumber, unsigned variableNumber);
        Boundary (std :: string caseString);
        List <std :: string> * getPointerLocations();
        List <std :: string> * getPointerVariables();
        List <List <std :: string> > * getPointerTypes();
        List <List <double> > * getPointerValues();
        List <std :: string > getLocations() const;
        List <std :: string> getVariables() const;
        List <std :: string> getTypes(std :: string variable) const;
        List <double> getValues(std :: string variable) const;
        std :: string getType(std :: string variable, std :: string location) const;
        double getValue(std :: string variable, std :: string location) const;
        friend std::ostream& operator<< (std::ostream& os, const Boundary & boundary);      
};

#endif /* Boundary_H */