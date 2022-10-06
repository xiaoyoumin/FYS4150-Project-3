#include "particle.hpp"

Particle Particle(arma::vec pos, arma::vec vel, float m, float q);

// Declarations of other class methods, e.g.
void time_step(arma::vec& d_pos, arma::vec& d_vel, float& d_t);
std::tuple<arma::vec, arma::vec> get_pos_vel(arma::vec& d_pos, arma::vec& d_vel, float& d_t);
std::tuple<arma::vec, arma::vec> get_pos_vel(arma::vec& d_pos, arma::vec& d_vel);
float get_m();
float get_q();