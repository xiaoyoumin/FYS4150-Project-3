#ifndef _Particle_
#define _Particle_

#include <armadillo>
#include <tuple>

class Particle 
{
    friend class PenningTrap;
    private:
        double m;
        double q;
        arma::vec pos;
        arma::vec vel;
        arma::vec pos_temp;
        arma::vec vel_temp;

    public:
        Particle(const arma::vec pos, const arma::vec vel, double m, double q);

        // Declarations of other class methods, e.g.
        void update(const arma::vec d_pos, const arma::vec d_vel);
        void update_temp(const arma::vec d_pos, const arma::vec d_vel);
        arma::vec get_pos();
        arma::vec get_vel();
        double get_m();
        double get_q();

        // Get the time derivative of pos and vel
        std::tuple<arma::vec, arma::vec> derivative(const arma::vec F);
        
        // Get the tima derivative of pos and vel, for a particle with a temporary offset
        std::tuple<arma::vec, arma::vec> derivative_temp(const arma::vec F);
};

#endif