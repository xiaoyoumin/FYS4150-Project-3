#include "particle.hpp"

using namespace arma;

Particle::Particle(const vec pos_, const vec vel_, double m_, double q_){
    pos = pos_;
    vel = vel_;
    m = m_;
    q = q_;
}


void Particle::update(const vec d_pos, const vec d_vel){
    pos = pos + d_pos;
    vel = vel + d_vel;
}

void Particle::update_temp(const vec d_pos, const vec d_vel){
    pos_temp = pos + d_pos;
    vel_temp = vel + d_vel;
}
// std::tuple<vec, vec> Particle::get_pos_vel(vec& d_pos, vec& d_vel, double& d_t);
// std::tuple<vec, vec> Particle::get_pos_vel(vec& d_pos, vec& d_vel);
vec Particle::get_pos(){
    return pos;
}

vec Particle::get_vel(){
    return vel;
}
double Particle::get_m(){
    return m;
}
double Particle::get_q(){
    return q;
}

// Get the time derivative of pos and vel
std::tuple<vec, vec> Particle::derivative(const vec F){
    return std::make_tuple(vel, F/m);
}

// Get the time derivative of pos and vel with temp offset
std::tuple<vec, vec> Particle::derivative_temp(const vec F){
    return std::make_tuple(vel_temp, F/m);
}

// // Get the tima derivative of pos and vel, for a particle with an offset
// std::tuple<vec, vec> Particle::derivative(const vec F, const vec d_pos, const vec d_vel);
