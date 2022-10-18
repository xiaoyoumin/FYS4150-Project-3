#ifndef _Penning_trap_
#define _Penning_trap_

#include "particle.hpp"
#include <armadillo>
#include <vector>
#include <iomanip>
#include <string>
#include <math.h>


class PenningTrap
{
    friend class PenningTrapSim;
    private:
        double B;
        double V0;
        double d;
        double f;
        double omega;
        double t;
        std::vector<Particle> particles;

    public:

        PenningTrap();
        // One particle
        PenningTrap(double B, double V, double d);
        PenningTrap(double B, double V, double d, double f, double omega, double t0);

        void update_pars(double B, double V, double d, double f, double omega, double t0);
        void update_pars(double f, double omega, double t0);
        void update_pars(double omega, double t0);

        // Fill with random particles
        void fill_random(double m, double q, int n);
        // Reset particle positions and velocities to random values
        void reset_random();

        // Add particle to trap
        void add_particle(const arma::vec pos, const arma::vec vel, double m, double q);
        void add_particle(Particle& p);

        // Update time
        void change_time(double dt);

        // Calculate E/B field
        double V();
        arma::vec ext_E_field(const arma::vec pos);
        arma::vec ext_B_field(const arma::vec pos);

        // Coulomb force
        arma::vec force_particle(int i, int j, bool temp);

        // The total force on particle_i from the external fields
        arma::vec total_force_external(int i, bool temp);

        // The total force on particle_i from the other particles
        arma::vec total_force_particles(int i, bool temp);

        // The total force on particle_i from both external fields [and other particles]
        arma::vec total_force(int i, bool temp, bool inter);

        // Get a particle
        Particle get_particle(int i);

        // Write to file
        std::string to_string(int width, int prec);

        std::string format_value(int width, int prec, double x);

        int count_particles();
};

#endif


