#include "penningTrap.hpp"
#include "particle.hpp"
#include <iostream>
#include <string>

#include <armadillo>

// PenningTrap default values:
// B = 9.65 * 10**1
// V = 2.41 * 10**6
// d = 500


int test_particle(){
    arma::vec a = {0,0,0};
    Particle p = Particle(a , a, 1, 1);
    std::cout << "Tested Particle creation\n";
    arma::vec b = {1.,2.,3.};
    arma::vec c = {-1.,-2.,-3.};
    p.update(b, c);
    if (not arma::approx_equal(p.get_pos(), b, "absdiff", 0.002)){
        std::cout << p.get_pos() << "!=\n" << b << '\n';
        std::cout << "Particle.update is not working (pos)\n";
    }
    if (not arma::approx_equal(p.get_vel(), c, "absdiff", 0.002)){
        std::cout << p.get_vel() << "!=\n" << c << '\n';
        std::cout << "Particle.update is not working (vel)\n";
    }
    std::cout << "tested Particle.update\n";

    return 0;
}

int test_penning_trap(){
    double x0 = 20., z0 = 20, v0 = 25;
    double B = 9.65e1, V = 2.41e6, d = 500.;
    double m = 40.078, q = 1.;
    int n = 1000;
    PenningTrap trap = PenningTrap(B, V, d);
    trap.add_particle(arma::vec{x0, 0., z0}, arma::vec{0., v0, 0.}, m, q);
    for (int i = 0; i < n; i++){
        trap.time_step_FE(0.01);
        // std::cout << arma::norm(trap.get_particle(0).get_pos()) << '\n';
    }
    // Particle p = trap.get_particle(0);
    // std::cout << p.get_pos() << '\n';
    // std::cout << p.get_vel() << '\n';
    return 0;
}

int main(){
    test_particle();
    test_penning_trap();

    return 0;
}
