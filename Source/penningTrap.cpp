#include "penningTrap.hpp"


// #include <string>

using namespace arma;
using namespace std;

PenningTrap::PenningTrap(){}

// Constructor
PenningTrap::PenningTrap(double B_, double V_, double d_){
    B = B_;
    V = V_;
    d = d_;
    particles = std::vector<Particle>();
}

// Fill with random particles
void PenningTrap::fill_random(double m, double q, int n){
    for (int i = 0; i < n; i++){
        vec r = vec(3).randn() * 0.1 * d;  // random initial position
        vec v = vec(3).randn() * 0.1 * d;  // random initial velocity
    }
}

// Add particle to trap
void PenningTrap::add_particle(const vec pos, const vec vel, double m, double q){
    Particle p = Particle(pos, vel, m, q);
    PenningTrap::add_particle(p);
}
void PenningTrap::add_particle(Particle& p){
    particles.push_back(p);
}

// Calculate E/B field
vec PenningTrap::ext_E_field(const vec pos){
    vec E_ = {pos(0), pos(1), -2*pos(2)};
    return V/(2*d*d)*E_;
}
vec PenningTrap::ext_B_field(const vec pos){
    vec B_ = {0,0,B};
    return B_;
}

// Coulomb force
vec PenningTrap::force_particle(int i, int j, bool temp){
    vec F = {0,0,0};
    return F;
}

// The total force on particle_i from the external fields
vec PenningTrap::total_force_external(int i, bool temp){
    Particle p = particles.at(i);
    vec E, B, F;
    if (temp){
        E = ext_E_field(p.pos_temp);
        B = ext_B_field(p.pos_temp);
        F = p.q * (E + arma::cross(p.vel_temp, B));
    }
    else{
        E = ext_E_field(p.pos);
        B = ext_B_field(p.pos);
        F = p.q * (E + arma::cross(p.vel, B));
    }
    return F;
}

// The total force on particle_i from the other particles
vec PenningTrap::total_force_particles(int i, bool temp){
    vec F = {0,0,0};
    for (int iter = 0; iter < particles.size(); iter++){
        if (iter != i){
            F += force_particle(i, iter, temp);
        }
    }
    return F;
}

// The total force on particle_i from both external fields and other particles
vec PenningTrap::total_force(int i, bool temp){
    vec F = total_force_external(i, temp) + total_force_particles(i, temp);
    return F;
}

Particle PenningTrap::get_particle(const int i){
    return particles.at(i);
}

// Write contents to file
string PenningTrap::to_string(int width, int prec){
    ostringstream out;
    out << format_value(width, prec, B)
    << format_value(width, prec, V)
    << format_value(width, prec, d);
    for (int i = 0; i < particles.size(); i++){
        out << particles.at(i).to_string(width, prec);
    }
    return out.str();
}

string PenningTrap::format_value(int width, int prec, double x){
    ostringstream out;
    out << std::setw(width) << std::setprecision(prec) << std::scientific << x;
    return out.str();
}



