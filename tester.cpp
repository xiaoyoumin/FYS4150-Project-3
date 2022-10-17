#include "penningTrapSim.hpp"
#include "penningTrap.hpp"
#include "particle.hpp"
#include <iostream>
#include <string>

#include <armadillo>

// PenningTrap default values:
// B = 9.65 * 10**1
// V = 2.41 * 10**6
// d = 500

// particle default values:
// m = 40.078
// q = 1.


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
    std::cout << "Tested Particle.update\n";

    return 0;
}

int test_penning_trap(){
    double x0 = 20., z0 = 20, v0 = 25;
    double B = 9.65e1, V = 2.41e6, d = 500.;
    double m = 40.078, q = 1.;
    int n = 50;
    PenningTrap trapFE = PenningTrap(B, V, d);
    trapFE.add_particle(arma::vec{x0, 0., z0}, arma::vec{0., v0, 0.}, m, q);
    PenningTrapSim simFE = PenningTrapSim(trapFE);
    for (int i = 0; i < n; i++){
        simFE.time_step_FE(0.01, false);
        // std::cout << arma::norm(trapFE.get_particle(0).get_pos()) << '\n';
    }
    // Particle p = trapFE.get_particle(0);
    // std::cout << p.get_pos() << '\n';
    // std::cout << p.get_vel() << '\n';
    
    std::cout << "Tested Penning trap Forward Euler stability\n";

    n = 50;
    PenningTrap trapRK = PenningTrap(B, V, d);
    trapRK.add_particle(arma::vec{x0, 0., z0}, arma::vec{0., v0, 0.}, m, q);
    PenningTrapSim simRK = PenningTrapSim(trapRK);
    for (int i = 0; i < n; i++){
        simRK.time_step_RK4(0.01, false);
        // std::cout << arma::norm(trapRK.get_particle(0).get_pos()) << '\n';
    }

    std::cout << "Tested Penning trap Runge Kutta stability\n";

    Particle pFE = trapFE.get_particle(0);
    Particle pRK = trapRK.get_particle(0);

    if (
        arma::approx_equal(pFE.get_pos(), pRK.get_pos(), "absdiff", 1) and
        arma::approx_equal(pFE.get_vel(), pRK.get_vel(), "absdiff", 1)
    ){//then
        std::cout << "Forward Euler and Runge Kutta agree \n";
    }
    else{
        std::cout << "Forward Euler and Runge Kutta disagree\n";
        return 1;
    }

    std::cout << "Tested Penning trap Runge Kutta agreement\n";
    return 0;
}

int main(){
    bool error = false;
    error = error or test_particle();
    error = error or test_penning_trap();

    return int(error);
}
