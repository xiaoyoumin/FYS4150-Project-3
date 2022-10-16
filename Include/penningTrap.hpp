#ifndef _Penning_trap_
#define _Penning_trap_

#include "particle.hpp"
#include <armadillo>
#include <vector>
#include <iomanip>


class PenningTrap
{
    friend class PenningTrapSim;
    private:
        double B;
        double V;
        double d;
        std::vector<Particle> particles;

    public:

        PenningTrap();
        // One particle
        PenningTrap(double B, double V, double d);

        // Fill with random particles
        void fill_random(double m, double q, int n);

        // Add particle to trap
        void add_particle(const arma::vec pos, const arma::vec vel, double m, double q);
        void add_particle(Particle& p);

        // Calculate E/B field
        arma::vec ext_E_field(const arma::vec pos);
        arma::vec ext_B_field(const arma::vec pos);

        // Coulomb force
        arma::vec force_particle(int i, int j, bool temp);

        // The total force on particle_i from the external fields
        arma::vec total_force_external(int i, bool temp);

        // The total force on particle_i from the other particles
        arma::vec total_force_particles(int i, bool temp);

        // The total force on particle_i from both external fields and other particles
        arma::vec total_force(int i, bool temp);

        // Get a particle
        Particle get_particle(int i);

        // Write to file
        std::string to_string(int width, int prec);

        std::string format_value(int width, int prec, double x);
};

#endif


