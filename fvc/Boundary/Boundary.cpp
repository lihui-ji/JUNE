#include "Boundary.hpp"

Boundary :: Boundary (unsigned locationNumber, unsigned variableNumber) : locations(locationNumber), variables(variableNumber), types (locationNumber), values (locationNumber){
    for (unsigned ind = 0; ind < locations.size(); ind++){
        types[ind].resize(variables.size());
        values[ind].resize(variables.size());
    }
}

Boundary :: Boundary (std :: string caseString) : Boundary (6, 6) {
    if (caseString == "cavityTest") {
        locations[0] = "Left"; locations[1] = "Right"; locations[2] = "Front"; locations[3] = "Back"; locations[4] = "Top"; locations[5] = "Bottom"; 
        variables[0] = "U0"; variables[1] = "U1"; variables[2] = "U2"; 
        variables[3] = "P"; variables[4] = "rho"; variables[5] = "nu"; 
        for (unsigned ind = 0; ind < locations.size(); ind++){
            types[ind][0] = "Dirichlet"; values[ind][0] = (ind == 4? 1 : 0);
            types[ind][1] = "Dirichlet"; values[ind][1] = 0;
            types[ind][2] = "Dirichlet"; values[ind][2] = 0;                        
            types[ind][3] = "Neumann"; values[ind][3] = 0;
            types[ind][4] = "Neumann"; values[ind][4] = 0;
            types[ind][5] = "Neumann"; values[ind][5] = 0;
        }
    }
}

List <std :: string> * Boundary :: getPointerLocations(){
    return &locations;
}

List <std :: string> * Boundary :: getPointerVariables(){
    return &variables;
}

List <List <std :: string> > * Boundary :: getPointerTypes(){
    return &types;
}

List <List <double> > * Boundary ::  getPointerValues(){
    return &values;
}

List <std :: string> Boundary :: getLocations() const{
    return locations;
}

List <std :: string> Boundary :: getVariables() const{
    return variables;
}

List <std :: string> Boundary :: getTypes(std :: string variable) const{
    List <std :: string> ans (locations.size());
    int varInd = variables.lookUp(variable);
    if (varInd == -1){
        throw std::invalid_argument("The variable undefined.");
    }
    for (unsigned locInd = 0; locInd < locations.size(); locInd++){
        ans [locInd] = types[locInd][varInd];
    }
    return ans;
}

List <double> Boundary ::  getValues(std :: string variable) const{
    List <double> ans (locations.size());
    int varInd = variables.lookUp(variable);
    if (varInd == -1){
        throw std::invalid_argument("The variable undefined.");
    }
    for (unsigned locInd = 0; locInd < locations.size(); locInd++){
        ans [locInd] = values[locInd][varInd];
    }
    return ans;
}

std :: string Boundary :: getType(std :: string variable, std :: string location) const{
    int varInd = variables.lookUp(variable);
    int locInd = locations.lookUp(location);
    if (varInd == -1){
        throw std::invalid_argument(variable + "Variable not exit in boundary.");
    }
    if (locInd == -1){
        throw std::invalid_argument(location + "Location not exit in boundary.");
    }    
    return types[locInd][varInd];
}

double Boundary ::  getValue(std :: string variable, std :: string location) const{
    int varInd = variables.lookUp(variable);
    int locInd = locations.lookUp(location);
    return values[locInd][varInd];
}

std::ostream& operator<< (std::ostream& os, const Boundary & boundary){
    for (unsigned indLoc = 0; indLoc < boundary.getLocations().size(); indLoc++){
        os  << "location: " << boundary.getLocations()[indLoc] << std :: endl;
            for (unsigned indVar = 0; indVar < boundary.getVariables().size(); indVar++){
                std :: string varCurr =  boundary.getVariables()[indVar];
                os << " " << varCurr << " boundary: " << boundary.getTypes(varCurr)[indLoc] << " " << boundary.getValues(varCurr)[indLoc] << std :: endl;
            }
    }
    return os;
}
