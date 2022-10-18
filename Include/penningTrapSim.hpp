#ifndef _Penning_Trap_Sim_
#define _Penning_Trap_Sim_


#include "particle.hpp"
#include "penningTrap.hpp"
#include <string>
#include <vector>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <iomanip>


class PenningTrapSim
{
    private:
        PenningTrap trap;


    public:
        // Constructor
        PenningTrapSim(PenningTrap trap_);

        // Reset the trap to randomised starting state, update omega, and reset t
        void reset(double omega, double t0);

        // Forward Euler time step
        void time_step_FE(double dt, bool inter);

        // Runge Kutta time step
        void time_step_RK4(double dt, bool inter);

        // Multiple step simulation
        int simulate(int n, double dt, bool inter, std::string method);
        int simulate(int n, double dt, bool inter, std::string method, std::string logFile);

        PenningTrap get_trap();

        // Count the number of particles within distance d of the center of the trap
        int count_particles();

};

#endif