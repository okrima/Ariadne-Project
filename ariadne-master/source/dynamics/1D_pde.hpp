//#include "ariadne.hpp"

#include "numeric/numeric.hpp"
#include "numeric/real.hpp"
#include "algebra/algebra.hpp"
#include "algebra/vector.hpp"
#include "utility/array.hpp"
#include "function/function.decl.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

namespace Ariadne
{
    struct pde_solution_1D
    {
        Array<Real> nextV;  //Next solution
        Array<Real> currV;  //Current solution
        Array<Real> prevV;  //Previous solution
    };

    struct string1D
    {
        Real length;    //Length of string
        Real frequency; //Frequency of oscillation
        Real wavelength;    // n*L
        Real damping;   //damping
        Real CourantNumber; //Courant Number 
    };    


    // Solving the one dimensional pde
    pde_solution_1D pde_1Dsolver(pde_solution_1D& solution, std::function<Real(Real)> &phi0, string1D& stringParameter, Real Nx);
    
    // Set initial condition
    pde_solution_1D setIC(pde_solution_1D& solution, std::function<Real(Real)> &phi0, Real Nx, Array<Real> spacePoint);

    // Create the linespace
    Array<Real> linspace(Real L, Real n);

}   // namespace Ariadne