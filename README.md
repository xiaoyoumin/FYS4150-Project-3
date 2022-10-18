# FYS4150-Project-3


Compile the test using

```bash
g++ Source/*.cpp tester.cpp -o test.exe -larmadillo -I Include/
```

Compile the program for generating the data for problem 8 with
```bash
g++ Source/*.cpp problem8.cpp -o main.exe -larmadillo -I Include/
```
You should make sure that you have a folder called Data in the folder where you run the program.

Compile the program for generating the data for problem 9 with
```bash
g++ Source/*.cpp problem9.cpp -o main.exe -larmadillo -I Include/
```
The executable for problem 9 can be run without arguments to do the broad sweep, or with arguments for more precise sweeps. If you want to do more precise sweeps use the folowing arguments, all arguments are required.
```bash
f, omega_min, omega_max, d_omega, n_steps (int), interaction (bool: 0/1), filename (string)
```
You should make sure that you have a folder called Data in the folder where you run the program when you run without command line arguments.




format for the datafiles is
```
B | V | d | t | [m | q | x1 | x2 | x3 | v1 | v2 | v3]
(Penningtrap settings), (Particle 1 data), (Particle 2 data), ...
```
for each row.
