#include "penningTrapSim.hpp"
#include "penningTrap.hpp"
#include "particle.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

//take in two lists and poutputs it into a file

int main()
{  
    
    
    //define array of strings
    HVOR DAAAA BROOO

    //open a file for writing
    ofstream fw("plot_val.txt", std::ofstream::out);

    //check if file is open, then write values out into txt file
    if (fw.is_open())
    {
    //store array contents to text file

    for (int i = 0; i < arraySize; i++) {
        fw << List[i] << "\n";
    }
    fw.close();

    }
    else cout << "couldnt open file, perhaps missing txt file?, or error in code :(";


  }
  return 0;
}

