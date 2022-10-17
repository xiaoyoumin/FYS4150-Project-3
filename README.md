# FYS4150-Project-3


Compile the test using

```bash
g++ Source/*.cpp tester.cpp -o test.exe -larmadillo -I Include/
```

Compile the program for generating the data for problem 8 with
```bash
g++ Source/*.cpp problem8.cpp -o main.exe -larmadillo -I Include/
```




format for the datafiles is
```
B | V | d | [m | q | x1 | x2 | x3 | v1 | v2 | v3]
(Penningtrap settings), (Particle 1 data), (Particle 2 data), ...
```
for each row, I will probably add a column for tims as well
