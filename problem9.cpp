#include "penningTrapSim.hpp"
#include "penningTrap.hpp"
#include "particle.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <iomanip>

using namespace std;


int frequency_survivors(PenningTrapSim& sim, double omega, double t, int n_steps, bool inter, string method){
    sim.reset(omega, 0);
    sim.simulate(n_steps, t/n_steps, inter, method);
    return sim.count_particles();
}

void run_frequency_sweep(double f, double omega_min, double omega_max, double d_omega, int n_particles, double t, int n_steps, bool inter, string filename){
    double B = 9.65e1;
    double V = 2.41e6;
    double d = 500;

    double m = 40.078;
    double q = 1.;

    PenningTrap trap = PenningTrap(B, V, d, f, omega_min, 0);
    trap.fill_random(m, q, n_particles);
    PenningTrapSim sim = PenningTrapSim(trap);

    ofstream stream;
    stream.open(filename);
    int count;
    int width = 12;
    int prec = 4;
    for (double omega = omega_min; omega < omega_max; omega += d_omega){
        count = frequency_survivors(sim, omega, t, n_steps, inter, "RK");
        stream << setw(width) << setprecision(prec) << scientific << f
               << setw(width) << setprecision(prec) << scientific << omega
               << "  " << count << '\n';
        cout << to_string(omega) << '\n';
    }
    stream.close();
}

int main(int argc, char *argv[]){
    if (argc == 1){
        run_frequency_sweep(0.1, 0.2, 2.5, 0.01, 100, 500, 80000, false, "Data/Scan_broad_f_0.1_n_80000.txt");
        run_frequency_sweep(0.4, 0.2, 2.5, 0.01, 100, 500, 80000, false, "Data/Scan_broad_f_0.4_n_80000.txt");
        run_frequency_sweep(0.7, 0.2, 2.5, 0.01, 100, 500, 80000, false, "Data/Scan_broad_f_0.7_n_80000.txt");
    }
    else{
        if (argc == 8){
            double f = stod(argv[1]);
            double omega_min = stod(argv[2]);
            double omega_max = stod(argv[3]);
            double d_omega = stod(argv[4]);
            int n_steps = stoi(argv[5]);
            int inter = stoi(argv[6]);
            run_frequency_sweep(f, omega_min, omega_max, d_omega, 100, 500, n_steps, inter, argv[7]);
        }
        else{
            cout << "\nPlease supply the function with no arguments or 7 arguments with the folowing meaning:\n"
                 << "f, omega_min, omega_max, d_omega, n_steps (int), interaction (bool: 0/1), filename (string)\n\n";
        }
    }
    return 0;
}