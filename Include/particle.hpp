#ifndef _Particle_
#define _Particle_

#include <armadillo>
#include <tuple>

class Particle 
{
    friend class PenningTrap;
    private:
        float m;
        float q;
        arma::vec pos;
        arma::vec vel;

    public:
        Particle(const arma::vec& pos, const arma::vec& vel, const float& m, const float& q);

        // Declarations of other class methods, e.g.
        void update(const arma::vec& d_pos, const arma::vec& d_vel);
        arma::vec get_pos();
        arma::vec get_vel();
        float get_m();
        float get_q();
};

#endif