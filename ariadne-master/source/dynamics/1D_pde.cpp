#include "1D_pde.hpp"

//using namespace std;
namespace Ariadne{

    Array<Real> linspace(Real L, Real n)
    {
        Array<Real> linspaced(n.get_d());

        if (n.get_d() == 0)
            return linspaced;
        if (n.get_d() == 1)
        {
            linspaced[0] = L;
            return linspaced;
        }

        Real delta = L/(n - 1);

        for (SizeType i = 0; i < (n.get_d() - 1); i++)
        {
            linspaced[i] = 0 + delta*i;
        }
        linspaced[n.get_d() - 1] = L;
        
        return linspaced;
    }
    // Set initial condition
    pde_solution_1D setIC(pde_solution_1D& solution, std::function<Real(Real)> &phi0, Real Nx, Array<Real> spacePoint)
    {
        for (SizeType i = 0; i < Nx.get_d(); i++)
        {
            solution.currV[i] = phi0(spacePoint[i]);
        }  
        return solution;
    }


    //Solving one dimensional pde
    pde_solution_1D pde_1Dsolver(pde_solution_1D& solution, std::function<Real(Real)> &phi0, string1D& stringParameter, Real Nx)
    {
        Real c = stringParameter.frequency*stringParameter.wavelength;
        Real T = stringParameter.wavelength/c;

        Real C2 = pow(stringParameter.CourantNumber, 2);

        Array<Real> space = linspace(stringParameter.length, Nx);

        Real dx = space[1] - space[0];
        Real dt = stringParameter.CourantNumber*dx/c;
        Real Nt = round(T/dt);

        Array<Real> time = linspace(Nt*dt, Nt);

        Real k = 2*pi/stringParameter.wavelength;

        solution = setIC(solution, phi0, Nx, space);

        // Set Boundary Condition
        solution.nextV[0] = 0;
        solution.nextV[Nx.get_d() - 1] = 0;

        // Set first Time step
        SizeType n = 0;
        for (SizeType i = 0; i < Nx.get_d() - 1; i++)
        {
            solution.nextV[i] = solution.currV[i] //+ dt*velIC
                            - 0.5_q*C2*(solution.currV[i-1] - 2*solution.currV[i] + solution.currV[i+1]);
                            // + 0.5_q*pow(dt,2)*source(space[i], time[n])
        }//first time step

        solution.nextV[0] = 0;
        solution.nextV[Nx.get_d() - 1] = 0;
        
        //switch variables
        solution.prevV = solution.currV;
        solution.currV = solution.nextV;

        // For each time step - main loop
        for (n = 1; n < Nt.get_d(); n++)
        {
            // Update inner points
            for (SizeType i = 0; i < Nx.get_d() - 1; i++)
            {
                solution.nextV[i] = (1/(1+0.5_q*stringParameter.damping*dt))*(-(solution.prevV[i])+1.1_q*solution.currV[i] + stringParameter.damping*dt/2*solution.prevV[i] +
                    C2*(solution.currV[i-1] - 2*solution.currV[i] + solution.currV[i+1]));
                    //+ pow(dt,2)*source(space[i], time[n]))
            }

            solution.nextV[0] = 0;
            solution.nextV[Nx.get_d() - 1] = 0;

            //switch variables
            solution.prevV = solution.currV;
            solution.currV = solution.nextV;
        }

        return solution;
        
    }
}// namespace Ariadne