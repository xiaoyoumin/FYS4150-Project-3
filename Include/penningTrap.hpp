#ifndef _Penning_trap_
#define _Penning_trap_

#include "particle.hpp"
#include <armadillo>
#include <vector>


class PenningTrap
{
    private:
        double B;
        double V;
        double d;
        std::vector<Particle> particles;

    public:
        // One particle
        PenningTrap(double B, double V, double d);

        // Fill with random particles
        void fill_random(double m, double q, int n);

        // Forward Euler time step
        void time_step_FE(double dt);

        // Runge Kutta time step
        void time_step_RK4(double dt);

        // Add particle to trap
        void add_particle(const arma::vec pos, const arma::vec vel, double m, double q);
        void add_particle(Particle& p);

        // Calculate E/B field
        arma::vec ext_E_field(const arma::vec pos);
        arma::vec ext_B_field(const arma::vec pos);

        // Coulomb force
        arma::vec force_particle(int i, int j);

        // The total force on particle_i from the external fields
        arma::vec total_force_external(int i);

        // The total force on particle_i from the other particles
        arma::vec total_force_particles(int i);

        // The total force on particle_i from both external fields and other particles
        arma::vec total_force(int i);

        Particle get_particle(int i);

};

#endif


