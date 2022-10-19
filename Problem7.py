import numpy as np
import matplotlib.pyplot as plt



# RK-4 method
def rk4(u, f, k, t):
    dt = t[k+1] - t[k]
    dt2 = dt/2.0
    K1 = dt*f(u[k], t[k])
    K2 = dt*f(u[k] + 0.5*K1, t[k] + dt2)
    K3 = dt*f(u[k] + 0.5*K2, t[k] + dt2)
    K4 = dt*f(u[k] + K3, t[k] + dt)
    u_new = u[k] + (1/6.0)*(K1 + 2*K2 + 2*K3 + K4)
    return u_new

rk4(x0,y0,xn,step)


