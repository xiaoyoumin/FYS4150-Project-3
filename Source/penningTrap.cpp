#include "penningTrap.hpp"

using namespace arma;


// One particle
PenningTrap::PenningTrap(double B, double V, double d){
    B = B;
    V = V;
    d = d;
    particles = std::vector<Particle>();
}

// Fill with random particles
void PenningTrap::fill_random(double m, double q, int n){
    for (int i = 0; i < n; i++){
        vec r = vec(3).randn() * 0.1 * d;  // random initial position
        vec v = vec(3).randn() * 0.1 * d;  // random initial velocity
    }
}

// Forward Euler time step
void PenningTrap::time_step_FE(double dt){
    std::vector<vec> d_pos_list;
    std::vector<vec> d_vel_list;
    vec d_pos;
    vec d_vel;
    for (int i = 0; i < particles.size(); i++){
        std::tie(d_pos, d_vel) = particles.at(i).derivative(total_force(i));
        d_pos_list.push_back(dt * d_pos);
        d_vel_list.push_back(dt * d_vel);
    }
    for (int i = 0; i < particles.size(); i++){
        particles.at(i).update(d_pos_list.at(i), d_vel_list.at(i));
    }
}

// // Runge Kutta time step
// void PenningTrap::time_step_RK4(double dt);

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
vec PenningTrap::force_particle(int i, int j){
    vec F = {0,0,0};
    return F;
}

// The total force on particle_i from the external fields
vec PenningTrap::total_force_external(int i){
    Particle p = particles.at(i);
    vec E = ext_E_field(p.pos);
    vec B = ext_B_field(p.pos);
    vec F = p.q * (E + arma::cross(p.vel, B));
    return F;
}

// The total force on particle_i from the other particles
vec PenningTrap::total_force_particles(int i){
    vec F = {0,0,0};
    for (int iter = 0; iter < particles.size(); iter++){
        if (iter != i){
            F += force_particle(i, iter);
        }
    }
    return F;
}

// The total force on particle_i from both external fields and other particles
vec PenningTrap::total_force(int i){
    vec F = total_force_external(i) + total_force_particles(i);
    return F;
}



