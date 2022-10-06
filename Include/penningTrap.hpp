#ifndef _Penning_trap_
#define _Penning_trap_

#include "particle.hpp"
#include <armadillo>

class PenningTrap
{
    private:
        float B;
        float V;
        float d;
        arma::Col<Particle> particles;

    public:
        PenningTrap(float B, float V, float d, int n);

        // Declarations of other class methods, e.g.
        void fill_random(float m, float q);
        void time_step_FE(float dt);
        void time_step_RK4(float dt);
        void add_particle(arma::vec pos, arma::vec vel, float m, float q);
        void add_particle(Particle p);
        arma::vec ext_E_field(arma::vec pos);
        arma::vec ext_E_field(arma::vec pos, float dt);
        arma::vec ext_B_field(arma::vec pos);
        arma::vec ext_B_field(arma::vec pos, float dt);
        arma::vec particle_E_field(int n);

    

};

#endif


