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
        // TrapSim();
        PenningTrapSim(PenningTrap trap_);

        // Forward Euler time step
        void time_step_FE(double dt, bool inter);

        // Runge Kutta time step
        void time_step_RK4(double dt, bool inter);

        // Multiple step simulation
        int simulate(int n, double dt, bool inter, std::string method);
        int simulate(int n, double dt, bool inter, std::string method, std::string logFile);
        // void simulate(int n, double dt, filestream logFile);
        // filestream make_file(std::string filename);

        PenningTrap get_trap();

};

#endif