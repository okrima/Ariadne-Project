#include "ariadne"

#include "numeric/numeric.hpp"
#include "function/function.hpp"

#include <cmath>
#include <vector>
#include <time.h>

#include "matplotlibcpp.h"

template<typename T>
std::vector<double> linspace(T start, T end, int num)
{
    std::vector<double> linspaced;

    double startIn = static_cast<double>(start);
    double endIn = static_cast<double>(end);
    double numIn = static_cast<double>(num);

    if (numIn == 0)
        return linspaced;
    if (numIn == 1)
    {
        linespaced.push_back(startIn);
        return linspaced;
    }

    double delta = (endIn - startIn)/(num - 1);

    for (int i = 0; i < end - 1; i++)
    {
        linspaced.push_back(startIn + delta*i);
    }
    linspaced.push_back(end);
       
    return linspaced;
}

int main(int argc, const char** argv) {
    
    //Solution variable
    std::vector<float> u(Nx, 0);   // Next value
    std::vector<float> u_1(Nx, 0); // Current value
    std::vector<float> u_2(Nx, 0); // Past value

    Real L = 0.5;   // m - Lenght
    Real T = 10;     // s - Simulation Time
    Real c = 1.5;   // m/s - wave velocity

    C = 0.75;        // Courant Number
    C2 = pow(C,2);

    int Nx = 100                        // # point in space
    int Nt = round(T/dt);               // # point in time

    auto space = linspace(0, L, Nx);    // Mesh in space
    Real dx = space[1] - space[0];

    dt = C*dx/c;
    auto time = linspace(0, Nt*dt, Nt);

    auto PosInitCond = [](int x){return sin(pi/L*x)};  // Set function initial position condition
    auto VelInitCond = [](int x){return 0};            // Set function initial velocity position
    auto source = [](int x, int t){return 0};

    // Set the initial condition
    for (int i = 0; i <= Nx; i++)
    {
        u_1[i] = InitCond(space[i]);   // Set initial condition
    }

    // Set Boundary Condition
    u[0] = 0;
    u[Nx] = 0;

    // Set first time step
    int n = 0;
    for (int i = 1; i < Nx; i++)
    {
        u[i] = u_1[i] + dt*VelInitCond(space[i]) 
            + 0.5*C2*(u_1[i-1] - 2*u_1[i] + u_1[i+1]) 
                + 0.5*pow(dt, 2)*source(space[i], time[n]);
    }

    u_2 = u_1;
    u_1 = u;

    // For each time step
    for (int n = 1; n <= Nt; n++)
    {
        // Update the inner points
        for (i = 1; i < Nx; i++)
        {
            u[i] = -u_2[i] + 2*u_1[i] 
                + C2*(u_1[i-1] - 2*u_1[i] + u_1[i+1]) 
                    + pow(dt, 2)*source(space[i], time[n]);
        }
        // Insert Boundary Condition
        u[0] = 0;
        u[Nx] = 0;

        // Before next step switch variables
        u_2 = u_1;
        u_1 = u;
        
    }

    
    

    return 0;
}