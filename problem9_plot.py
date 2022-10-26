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
plt.plot(w,n/100,label="f=0.1")
f, w, n = values("Scan_broad_f_0.4_n_80000")
plt.plot(w,n/100,label="f=0.4")
f, w, n = values("Scan_broad_f_0.7_n_80000")
plt.plot(w,n/100,label="f=0.7")
plt.legend()
plt.xlabel("frequency (MHz)")
plt.ylabel("Percentage of particles")
plt.title("Particles over frequency")
plt.savefig("Problem9Output/Particles over frequency.pdf")
plt.show()

f, w, n = values("Scan_broad_interactions_f_0.1_n_80000_w1_1.7")
plt.plot(w,n/100,label="f=0.1")
f, w, n = values("Scan_broad_interactions_f_0.4_n_80000_w1_1.7")
plt.plot(w,n/100,label="f=0.4")
f, w, n = values("Scan_broad_interactions_f_0.7_n_80000_w1_1.7")
plt.plot(w,n/100,label="f=0.7")
plt.legend()
plt.xlabel("frequency (MHz)")
plt.ylabel("Percentage of particles")
plt.title("Zoomed in particles over frequency with interactions")
plt.savefig("Problem9Output/Zoomed particles over frequency.pdf")
plt.show()
