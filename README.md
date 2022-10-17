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
You should make sure that you have a folder called Data in the folder where you run the program.




format for the datafiles is
```
B | V | d | t | [m | q | x1 | x2 | x3 | v1 | v2 | v3]
(Penningtrap settings), (Particle 1 data), (Particle 2 data), ...
```
for each row.
