import matplotlib.pyplot as plt
import numpy as np

"""
each row consists of: B | V | d | t | [m | q | x1 | x2 | x3 | v1 | v2 | v3]

where B, V, d, t
and [m | q | x1 | x2 | x3 | v1 | v2 | v3]
consist of mass, charge and position set of particle 1, 

"""

"""
opening our  txt files from problem 8 using pythons built in 'open'

file_x = open('problem2_x.txt')
for values in file_x:
    numbers = values.split(" ")
    x = np.array(numbers)
print(x[3])

"""

def values(n):                            
    #[m | q | x1 | x2 | x3 | v1 | v2 | v3]
    with open(f"../Data/{n}.txt") as f:
        lines = f.readlines()
        B, V, d, t = [], [], [], []
        m, q = [], []
        x1, x2, x3 = [], [], []
        v1, v2, v3 = [], [], []
        for line in lines:
            vals = line.split("\t")
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
    
    return  B, V, d, t, m, q, x1, x2, x3, v1, v2, v3 
        
    #v=np.array(v)[1:-1]
    #x=np.array(x)[1:-1]

def rel_error(u, v):                    #calculates relative error
    u, v = np.array(u), np.array(v)

    log10eps = np.zeros(len(u))
    for i in range(0, len(u)):
        log10eps = np.log10(abs((u[i] - v[i])/u[i]))

    return log10eps #np.log10(abs((u-v)/u)) #this is perhaps faster and better?

#real = rel_error(u, x)

def plot_file(filename):
    B, V, d, t, m, q, x1, x2, x3, v1, v2, v3  = values(filename)

    plt.title(f'z position over time from a {filename}')
    plt.ylabel('z-position')
    plt.xlabel('time')
    plt.plot(x3, t)
    plt.show()

    plt.title(f'x and y position from a {filename}')
    plt.ylabel('y-position')
    plt.xlabel('x-position')
    plt.plot(x1, x2)
    plt.show()

    plt.title(f'velocity in x-direction as a function of x position from a {filename}')
    plt.ylabel('x-velocity')
    plt.xlabel('x-position')
    plt.plot(x1, v1)
    plt.show()

    plt.title(f'velocity in z-direction as a function of z position from a {filename}')
    plt.ylabel('z-velocity')
    plt.xlabel('z-position')
    plt.plot(x1, v1)
    plt.show()

    





files = ['singleParticle_FE_4000', 'singleParticle_FE_8000', 'singleParticle_FE_16000',
         'singleParticle_FE_32000', 'singleParticle_RK_4000', 'singleParticle_RK_8000', 
         'singleParticle_RK_16000', 'singleParticle_RK_32000', 'twoParticle_RK_4000',
          'twoParticle_RK_8000', 'twoParticle_RK_16000', 'twoParticle_RK_32000' ]


for i in range(len(files)):
    plot_file(files[i])

