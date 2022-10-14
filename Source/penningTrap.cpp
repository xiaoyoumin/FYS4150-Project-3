#include "penningTrap.hpp"


#include <string>

using namespace arma;


// One particle
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

// Forward Euler time step
void PenningTrap::time_step_FE(double dt){
    int n = particles.size();
    mat d_pos_list = mat(3, n);
    mat d_vel_list = mat(3, n);

    for (int i = 0; i < n; i++){
        vec d_pos;
        vec d_vel;
    
        std::tie(d_pos, d_vel) = particles.at(i).derivative(total_force(i, false));
        d_pos_list.col(i) = dt * d_pos;
        d_vel_list.col(i) = dt * d_vel;
    }
    for (int i = 0; i < particles.size(); i++){
        particles.at(i).update(d_pos_list.col(i), d_vel_list.col(i));
    }
}

// // Runge Kutta time step
void PenningTrap::time_step_RK4(double dt){
    int n = particles.size();
    mat k_1_pos = mat(3, n);
    mat k_1_vel = mat(3, n);
    mat k_2_pos = mat(3, n);
    mat k_2_vel = mat(3, n);
    mat k_3_pos = mat(3, n);
    mat k_3_vel = mat(3, n);
    mat k_4_pos = mat(3, n);
    mat k_4_vel = mat(3, n);
    vec ddt_pos;
    vec ddt_vel;

    // Calculate K1
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = particles.at(i).derivative(total_force(i, false));
        k_1_pos.col(i) = ddt_pos;
        k_1_vel.col(i) = ddt_vel;
    }

    // Prepare the particles for calculating K2
    for (int i = 0; i < particles.size(); i++){
        particles.at(i).update_temp(0.5*dt*k_1_pos.col(i), 0.5*dt*k_1_vel.col(i));
    }
    
    // Calculate K2
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = particles.at(i).derivative(total_force(i, true));
        k_2_pos.col(i) = ddt_pos;
        k_2_vel.col(i) = ddt_vel;
    }

    // Prepare the particles for calculating K3
    for (int i = 0; i < particles.size(); i++){
        particles.at(i).update_temp(0.5*dt*k_2_pos.col(i), 0.5*dt*k_2_vel.col(i));
    }
    
    // Calculate K3
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = particles.at(i).derivative(total_force(i, true));
        k_3_pos.col(i) = ddt_pos;
        k_3_vel.col(i) = ddt_vel;
    }

    // Prepare the particles for calculating K4
    for (int i = 0; i < particles.size(); i++){
        particles.at(i).update_temp(dt*k_3_pos.col(i), dt*k_3_vel.col(i));
    }
    
    // Calculate K4
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = particles.at(i).derivative(total_force(i, true));
        k_4_pos.col(i) = ddt_pos;
        k_4_vel.col(i) = ddt_vel;
    }

    // Do the actual time step
    for (int i = 0; i < particles.size(); i++){
        particles.at(i).update(
            dt/6.*(k_1_pos.col(i) + 2*k_2_pos.col(i) + 2*k_3_pos.col(i) + k_4_pos.col(i)),
            dt/6.*(k_1_vel.col(i) + 2*k_2_vel.col(i) + 2*k_3_vel.col(i) + k_4_vel.col(i)));
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



