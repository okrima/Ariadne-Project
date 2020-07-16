#include "ariadne"

#include "numeric/numeric.hpp"
#include "function/function.hpp"

#include <cmath>
#include <vector>

#define Nt 100;
#define Nx 100;

int main(int argc, const char** argv) {
    
    //Solution variable
    std::vector<float> u(Nx);   //next value
    std::vector<float> u_1(Nx); //current value
    std::vector<float> u_2(Nx); //past value

    Real dx = 0.5, dt = 0.5;    //Initialize mesh - time & 1D space

    C = c*dt/dx;    //Courant number

    EffectiveVectorMultivariateFunction InitCond = sin(2*pi*x);

    //Set the initial condition
    for (int i = 0; i < Nx; i++)
    {
        //TODO BOUNDARY CONDITION
    }
    


    
    
    
    
    return 0;
}