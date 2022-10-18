#include "penningTrapSim.hpp"


using namespace arma;
using namespace std;



// TrapSim::TrapSim(){
PenningTrapSim::PenningTrapSim(PenningTrap trap_){
    trap = trap_;
}

// Reset the trap to randomised starting state, update omega, and reset t
void PenningTrapSim::reset(double omega, double t0){
    trap.update_pars(omega, t0);
    trap.reset_random();
}

// Forward Euler time step
void PenningTrapSim::time_step_FE(double dt, bool inter){
    int n = trap.particles.size();
    mat d_pos_list = mat(3, n);
    mat d_vel_list = mat(3, n);

    for (int i = 0; i < n; i++){
        vec d_pos;
        vec d_vel;
    
        std::tie(d_pos, d_vel) = trap.particles.at(i).derivative(trap.total_force(i, false, inter));
        d_pos_list.col(i) = dt * d_pos;
        d_vel_list.col(i) = dt * d_vel;
    }
    for (int i = 0; i < trap.particles.size(); i++){
        trap.particles.at(i).update(d_pos_list.col(i), d_vel_list.col(i));
    }
    trap.change_time(dt);
}

// // Runge Kutta time step
void PenningTrapSim::time_step_RK4(double dt, bool inter){
    int n = trap.particles.size();
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
        std::tie(ddt_pos, ddt_vel) = trap.particles.at(i).derivative(trap.total_force(i, false, inter));
        k_1_pos.col(i) = ddt_pos;
        k_1_vel.col(i) = ddt_vel;
    }

    // Prepare the particles for calculating K2
    for (int i = 0; i < trap.particles.size(); i++){
        trap.particles.at(i).update_temp(0.5*dt*k_1_pos.col(i), 0.5*dt*k_1_vel.col(i));
    }
    trap.change_time(0.5*dt);
    
    // Calculate K2
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = trap.particles.at(i).derivative(trap.total_force(i, true, inter));
        k_2_pos.col(i) = ddt_pos;
        k_2_vel.col(i) = ddt_vel;
    }

    // Prepare the particles for calculating K3
    for (int i = 0; i < trap.particles.size(); i++){
        trap.particles.at(i).update_temp(0.5*dt*k_2_pos.col(i), 0.5*dt*k_2_vel.col(i));
    }
    
    // Calculate K3
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = trap.particles.at(i).derivative(trap.total_force(i, true, inter));
        k_3_pos.col(i) = ddt_pos;
        k_3_vel.col(i) = ddt_vel;
    }

    // Prepare the particles for calculating K4
    for (int i = 0; i < trap.particles.size(); i++){
        trap.particles.at(i).update_temp(dt*k_3_pos.col(i), dt*k_3_vel.col(i));
    }
    trap.change_time(0.5*dt);
    
    // Calculate K4
    for (int i = 0; i < n; i++){
        std::tie(ddt_pos, ddt_vel) = trap.particles.at(i).derivative(trap.total_force(i, true, inter));
        k_4_pos.col(i) = ddt_pos;
        k_4_vel.col(i) = ddt_vel;
    }

    // Do the actual time step
    for (int i = 0; i < trap.particles.size(); i++){
        trap.particles.at(i).update(
            dt/6.*(k_1_pos.col(i) + 2*k_2_pos.col(i) + 2*k_3_pos.col(i) + k_4_pos.col(i)),
            dt/6.*(k_1_vel.col(i) + 2*k_2_vel.col(i) + 2*k_3_vel.col(i) + k_4_vel.col(i)));
    }
}


int PenningTrapSim::simulate(int n, double dt, bool inter, string method){
    if (method == "FE"){
        for (int i = 0; i < n; i++){
            time_step_FE(dt, inter);
        }
        return 0;
    }
    if (method == "RK"){
        for (int i = 0; i < n; i++){
            time_step_RK4(dt, inter);
        }
        return 0;
    }
    return 1;
}

int PenningTrapSim::simulate(int n, double dt, bool inter, string method, string logFile){
    ofstream stream;
    stream.open(logFile);

    if (method == "FE"){
        for (int i = 0; i < n; i++){
            time_step_FE(dt, inter);
            stream << trap.to_string(12, 4);
            stream << '\n';
        }
        stream.close();
        return 0;
    }
    if (method == "RK"){
        for (int i = 0; i < n; i++){
            time_step_RK4(dt, inter);
            stream << trap.to_string(12, 4);
            stream << '\n';
        }
        stream.close();
        return 0;
    }
    stream.close();
    return 1;
}

PenningTrap PenningTrapSim::get_trap(){
    return trap;
}

// Count the number of particles within distance d of the center of the trap
int PenningTrapSim::count_particles(){
    return trap.count_particles();
}