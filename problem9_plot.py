import matplotlib.pyplot as plt
import numpy as np

def values(n):#Returns values from file n                   
    #[m | q | x1 | x2 | x3 | v1 | v2 | v3]
    with open(f"Data/{n}.txt") as f:
        lines = f.readlines()
        f, w, n = [], [], []
        for line in lines:
            vals = line.split()
            f.append(float(vals[0]))
            w.append(float(vals[1]))
            n.append(float(vals[2]))

        f=np.array(f)
        w=np.array(w)
        n=np.array(n)
    return  f, w, n
    
f, w, n = values("Scan_broad_f_0.1_n_80000")
plt.plot(w,np.log(n),label="f=0.1")
f, w, n = values("Scan_broad_f_0.4_n_80000")
plt.plot(w,np.log(n),label="f=0.4")
f, w, n = values("Scan_broad_f_0.7_n_80000")
plt.plot(w,np.log(n),label="f=0.7")
plt.legend()
plt.xlabel("frequency (MHz)")
plt.ylabel("Number of particles")
plt.title("Particles over frequency in logarithmic scale")
plt.savefig("Problem9Output/Particles over frequency.pdf")
plt.show()