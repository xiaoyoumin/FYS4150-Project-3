import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d

"""
each row consists of: B | V | d | t | [m | q | x1 | x2 | x3 | v1 | v2 | v3]

where B, V, d, t
and [m | q | x1 | x2 | x3 | v1 | v2 | v3]
consist of mass, charge and position set of particle 1, 

"""

def f(B, V, d, t, m, q, x1, x3, v2):#analytical function
    V0=V[0]
    v0=v2[0]
    z0=x3[0]
    x0=x1[0]
    B0=B[0]

    w0=q*B0/m
    wz=(2*q*V0/(m*d**2))**0.5
    wp=(w0+(w0**2-2*wz**2)**0.5)/2
    wm=(w0-(w0**2-2*wz**2)**0.5)/2
    Ap=(v0+wm*x0)/(wm-wp)
    Am=-(v0+wp*x0)/(wm-wp)
    f=Ap*np.exp(-1j*(wp*t))+Am*np.exp(-1j*(wm*t))
    return f.real,f.imag,z0*np.cos(wz*t)

def values(n,two=False):#Returns values from file n                   
    #[m | q | x1 | x2 | x3 | v1 | v2 | v3]
    with open(f"Data/{n}.txt") as f:
        lines = f.readlines()
        B, V, d, t = [], [], [], []
        m, q = [], []
        x1, x2, x3 = [], [], []
        v1, v2, v3 = [], [], []

        x1i, x2i, x3i = [], [], []
        for line in lines:
            vals = line.split()
            B.append(float(vals[0]))
            V.append(float(vals[1]))
            d.append(float(vals[2]))
            t.append(float(vals[3]))
            m.append(float(vals[4]))
            q.append(float(vals[5]))
            x1.append(float(vals[6]))
            x2.append(float(vals[7]))
            x3.append(float(vals[8]))
            v1.append(float(vals[9]))
            v2.append(float(vals[10]))
            v3.append(float(vals[11]))
            if two:
                x1i.append(float(vals[14]))
                x2i.append(float(vals[15]))
                x3i.append(float(vals[16]))

        B=np.array(B)
        V=np.array(V)
        d=np.array(d)
        t=np.array(t)
        m=np.array(m)
        q=np.array(q)
        x1=np.array(x1)
        x2=np.array(x2)
        x3=np.array(x3)
        v1=np.array(v1)
        v2=np.array(v2)
        v3=np.array(v3)
        if two:
            return x1,x2,x3,x1i,x2i,x3i
    
    return  B, V, d, t, m, q, x1, x2, x3, v1, v2, v3 


#files = ['singleParticle_FE_4000', 'singleParticle_FE_8000', 'singleParticle_FE_16000',
#         'singleParticle_FE_32000', 'singleParticle_RK_4000', 'singleParticle_RK_8000', 
#         'singleParticle_RK_16000', 'singleParticle_RK_32000', 'twoParticle_RK_4000',
#          'twoParticle_RK_8000', 'twoParticle_RK_16000', 'twoParticle_RK_32000' ]
#filenames for ease of access


#Plots
x1,x2,x3,x1i,x2i,x3i=values("twoParticle_RK_32000",True)
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(x1, x2, x3,label="Particle 1")
ax.plot3D(x1i, x2i, x3i,label="Particle 2")
ax.set_title("Two particle 3D position")
ax.set_xlabel("x-position")
ax.set_ylabel("y-position")
ax.set_zlabel("z-position")
ax.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Two particles 3D position.pdf")
plt.show()


B, V, d, t, m, q, x1, x2, x3, v1, v2, v3  = values("singleParticle_RK_32000")
Bi, Vi, di, ti, mi, qi, x1i, x2i, x3i, v1i, v2i, v3i  = values("twoParticle_RK_32000")
V0=V[0]
wz=(2*q*V0/(m*d**2))**0.5
plt.plot(t,v3,label="motion in z direction")
plt.ylabel('z-velocity')
plt.xlabel('time (microseconds)')
plt.plot(t,np.cos(wz*t),label="cos(wt*t)")
plt.title("Particle motion in z direction")
plt.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Particle motion in z direction.pdf")
plt.show()

plt.plot(x1, x2,label="without interactions")
plt.ylabel('y-position')
plt.xlabel('x-position')
plt.plot(x1i, x2i,label="with interactions")
plt.title("Particle position x/y plane")
plt.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Particle position x-y plane.pdf")
plt.show()

plt.plot(x1, v1,label="without interactions")
plt.ylabel('x-velocity')
plt.xlabel('x-position')
plt.plot(x1i, v1i,label="with interactions")
plt.title("Phase Space Plot x-axis")
plt.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Phase Space Plot x-axis.pdf")
plt.show()

plt.plot(x3, v3,label="without interactions")
plt.ylabel('z-velocity')
plt.xlabel('z-position')
plt.plot(x3i, v3i,label="with interactions")
plt.title("Phase Space Plot z-axis")
plt.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Phase Space Plot z-axis.pdf")
plt.show()

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(x1, x2, x3,label="without interactions")
ax.plot3D(x1i, x2i, x3i,label="with interactions")
ax.set_title("Particle 3D position")
ax.set_xlabel("x-position")
ax.set_ylabel("y-position")
ax.set_zlabel("z-position")
ax.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Particle 3D position.pdf")
plt.show()

x,y,z=f(B, V, d, t, m, q, x1, x3, v2)

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot3D(x, y, z,label="analytical solution")
ax.plot3D(x1, x2, x3,label="simulated solution")
ax.set_title("Analytical Particle 3D position")
ax.set_xlabel("x-position")
ax.set_ylabel("y-position")
ax.set_zlabel("z-position")
ax.legend()
plt.axis("equal")
plt.savefig("Problem8Output/Analytical Particle 3D position.pdf")
plt.show()

#Find relative error
#Store positions and change dimensions
B, V, d, t, m, q, x4000, y4000, z4000, v1, v2, v3  = values("singleParticle_RK_4000")
x4,y4,z4=f(B, V, d, t, m, q, x4000, z4000, v2)
pos4=np.dstack((x4,y4,z4))

B, V, d, t, m, q, x8000, y8000, z8000, v1, v2, v3  = values("singleParticle_RK_8000")
x8,y8,z8=f(B, V, d, t, m, q, x8000, z8000, v2)
pos8=np.dstack((x8,y8,z8))

B, V, d, t, m, q, x16000, y16000, z16000, v1, v2, v3  = values("singleParticle_RK_16000")
x16,y16,z16=f(B, V, d, t, m, q, x16000, z16000, v2)
pos16=np.dstack((x16,y16,z16))

B, V, d, t, m, q, x32000, y32000, z32000, v1, v2, v3  = values("singleParticle_RK_32000")
x32,y32,z32=f(B, V, d, t, m, q, x32000, z32000, v2)
pos32=np.dstack((x32,y32,z32))

pos4000=np.dstack((x4000,y4000,z4000))
pos8000=np.dstack((x8000,y8000,z8000))
pos16000=np.dstack((x16000,y16000,z16000))
pos32000=np.dstack((x32000,y32000,z32000))

def element_wise_norm(A):
    return np.array([np.linalg.norm(v) for v in A[0]])

def relative(actual,expected):
    return np.abs(np.divide(np.abs(element_wise_norm(actual-expected)),np.abs(element_wise_norm(expected))))

#interpolation is done to be able to dee the errors next to each other
h=np.linspace(0,50,4000)
y=np.interp(h,np.linspace(0,50,4000),np.log(relative(pos4000,pos4)))
plt.plot(h,y,label="RK4000")
y=np.interp(h,np.linspace(0,50,8000),np.log(relative(pos8000,pos8)))
plt.plot(h,y,label="RK8000")
y=np.interp(h,np.linspace(0,50,16000),np.log(relative(pos16000,pos16)))
plt.plot(h,y,label="RK16000")
y=np.interp(h,np.linspace(0,50,32000),np.log(relative(pos32000,pos32)))
plt.plot(h,y,label="RK32000")
plt.legend()
plt.title("Relative error over time in logarithmic scale")
plt.xlabel("time (microseconds)")
plt.ylabel("Relative error")
plt.savefig("Problem8Output/Relative error over time in logarithmic scale.pdf")
plt.show()

#Find the error convergence rate
max4=(pos4000-pos4)
max4=np.amax(element_wise_norm(max4))

max8=(pos8000-pos8)
max8=np.amax(element_wise_norm(max8))

max16=(pos16000-pos16)
max16=np.amax(element_wise_norm(max16))

max32=(pos32000-pos32)
max32=np.amax(element_wise_norm(max32))

max=[max4,max8,max16,max32]

def rerr(max):
    s=0
    n=np.array([4000,8000,16000,32000])
    h=50/n
    for k in range(1,4):
        s+=(np.log(max[k]/max[k-1])/np.log(h[k]/h[k-1]))
    s*=(1/3)
    return s

print("Error convergence rate:",rerr(max))
#Error convergence rate: 0.997724175604406
