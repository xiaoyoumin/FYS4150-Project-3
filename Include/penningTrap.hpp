#ifndef _Penning_trap_
#define _Penning_trap_

using #armadillo

class PenningTrap
{
    
    private:
        float m;
        float q;
        arma::vec pos;
        arma::vec vel;

    public:
        Particle(arma::vec& pos, arma::vec& vel, float& m, float& q);

        // Declarations of other class methods, e.g.
        void time_step(arma::vec& d_pos, arma::vec& d_vel, float& d_t);
        std::tuple<arma::vec, arma::vec> get_pos_vel(arma::vec& d_pos, arma::vec& d_vel, float& d_t);
        std::tuple<arma::vec, arma::vec> get_pos_vel(arma::vec& d_pos, arma::vec& d_vel);
        float get_m();
        float get_q();
    

};

#endif


