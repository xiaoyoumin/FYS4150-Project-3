#include "penningTrap.hpp"



PenningTrap(float& B, float& V, float& d, int& n);
PenningTrap_random(float& B, float& V, float& d, int& n);

// Declarations of other class methods, e.g.
void time_step_FE(float& dt);
void time_step_RK4(float& dt);
void add_particle(arma::vec& pos, arma::vec& vel, float& m, float& q);
void add_particle(Particle p);
arma::vec ext_E_field(arma::vec& pos);
arma::vec ext_E_field(arma::vec& pos, float& dt);
arma::vec ext_B_field(arma::vec& pos);
arma::vec ext_B_field(arma::vec& pos, float& dt);
arma::vec particle_E_field(int& n);