#include "penningTrap.hpp"
#include "particle.hpp"
#include <iostream>
#include <string>

#include <armadillo>


int main(){
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
}
