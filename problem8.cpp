#include "penningTrapSim.hpp"
#include "penningTrap.hpp"
#include "particle.hpp"
#include <iostream>
#include <string>

#include <armadillo>

using namespace std;
using namespace arma;


// PenningTrap default values:
// B = 9.65 * 10**1
// V = 2.41 * 10**6
// d = 500

// particle default values:
// m = 40.078
// q = 1.

void run_sim_1p(int n, string method){
    double B = 9.65e1;
    double V = 2.41e6;
    double d = 500;

    double m = 40.078;
    double q = 1.;

    double dt = 50./n;

    PenningTrap trap = PenningTrap(B, V, d);
    trap.add_particle(vec{20.,0.,20.}, vec{0.,25.,0.}, m, q);
    PenningTrapSim sim = PenningTrapSim(trap);
    
    string filename = "Data/singleParticle_" + method + "_" + to_string(n) + ".txt";
    sim.simulate(n, dt, method, filename);
    cout << "Made log of simulation in " << filename << '\n';
}

int main(){
    string methods [2] = {"RK", "FE"};
    for (int i = 0; i < 2; i++){
        for (int n = 4000; n < 40000; n *= 2){
            run_sim_1p(n, methods[i]);
        }
    }
    return 0;
}