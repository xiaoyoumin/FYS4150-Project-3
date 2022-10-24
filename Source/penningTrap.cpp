#include "penningTrap.hpp"


// #include <string>

using namespace arma;
using namespace std;

PenningTrap::PenningTrap(){}

// Constructor
PenningTrap::PenningTrap(double B_, double V_, double d_){
    B = B_;
    V0 = V_;
    d = d_;
    f = 0.;
    omega = 0.;
    t = 0.;
    particles = std::vector<Particle>();
}

PenningTrap::PenningTrap(double B_, double V_, double d_, double f_, double omega_, double t0){
    B = B_;
    V0 = V_;
    d = d_;
    f = f_;
    omega = omega_;
    t = t0;
    particles = std::vector<Particle>();
}

void PenningTrap::update_pars(double B_, double V_, double d_, double f_, double omega_, double t0){
    B = B_;
    V0 = V_;
    d = d_;
    f = f_;
    omega = omega_;
    t = t0;
}

void PenningTrap::update_pars(double f_, double omega_, double t0){
    f = f_;
    omega = omega_;
    t = t0;
}

void PenningTrap::update_pars(double omega_, double t0){
    omega = omega_;
    t = t0;
}

// Fill with random particles
void PenningTrap::fill_random(double m, double q, int n){
    for (int i = 0; i < n; i++){
        vec r = vec(3).randn() * 0.1 * d;  // random initial position
        vec v = vec(3).randn() * 0.1 * d;  // random initial velocity
        add_particle(r, v, m, q);
    }
}

// Reset particle positions to random values
void PenningTrap::reset_random(){
    Particle p;
    for (int i = 0; i < particles.size(); i++){
        p = particles[i];
        p.pos = vec(3).randn() * 0.1 * d;  // random position
        p.vel = vec(3).randn() * 0.1 * d;  // random velocity
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

// Update time
void PenningTrap::change_time(double dt){
    t += dt;
}

// Calculate E/B field
double PenningTrap::V(){
    return V0 * (1+f*cos(omega * t));
}

vec PenningTrap::ext_E_field(const vec pos){
    if (norm(pos) < d){
        vec E_ = {pos(0), pos(1), -2*pos(2)};
        return V()/(d*d)*E_;
    }
    else{
        return vec{0.,0.,0.};
    }
}
vec PenningTrap::ext_B_field(const vec pos){
    if (norm(pos) < d){
        vec B_ = {0,0,B};
        return B_;
    }
    else{
        return vec{0.,0.,0.};
    }
}

// Coulomb force
vec PenningTrap::force_particle(int i, int j, bool temp){
    double ke = 1.38935333e5;
    Particle p1 = particles[i];
    Particle p2 = particles[j];
    vec rel;
    if (temp){
        rel = p1.pos_temp - p2.pos_temp;
    }
    else{
        rel = p1.pos - p2.pos;
    }
    vec F = rel * ke / (norm(rel)*norm(rel)*norm(rel));
    return F;
}

// The total force on particle_i from the external fields
vec PenningTrap::total_force_external(int i, bool temp){
    Particle p = particles[i];
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
vec PenningTrap::total_force(int i, bool temp, bool inter){
    if (inter){
        vec F = total_force_external(i, temp) + total_force_particles(i, temp);
        return F;
    }
    else{
        vec F = total_force_external(i, temp);
        return F;
    }
}

Particle PenningTrap::get_particle(const int i){
    return particles.at(i);
}

// Write contents to file
string PenningTrap::to_string(int width, int prec){
    ostringstream out;
    out << format_value(width, prec, B)
    << format_value(width, prec, V())
    << format_value(width, prec, d)
    << format_value(width, prec, t);
    for (int i = 0; i < particles.size(); i++){
        out << particles[i].to_string(width, prec);
    }
    return out.str();
}

string PenningTrap::format_value(int width, int prec, double x){
    ostringstream out;
    out << std::setw(width) << std::setprecision(prec) << std::scientific << x;
    return out.str();
}

int PenningTrap::count_particles(){
    int count = 0;
    for (int i = 0; i < particles.size(); i++){
        if (norm(particles[i].pos) < d){
            count++;
        }
    }
    return count;
}

