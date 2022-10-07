#include "particle.hpp"

using namespace arma;

Particle::Particle(const vec& pos_, const vec& vel_, const float& m_, const float& q_){
    pos = pos_;
    vel = vel_;
    m = m_;
    q = q_;
}

// Declarations of other class methods, e.g.
void Particle::update(const vec& d_pos, const vec& d_vel){
    pos = pos + d_pos;
    vel = vel + d_vel;
}
// std::tuple<vec, vec> Particle::get_pos_vel(vec& d_pos, vec& d_vel, float& d_t);
// std::tuple<vec, vec> Particle::get_pos_vel(vec& d_pos, vec& d_vel);
vec Particle::get_pos(){
    return pos;
}

vec Particle::get_vel(){
    return vel;
}
float Particle::get_m(){
    return m;
}
float Particle::get_q(){
    return q;
}