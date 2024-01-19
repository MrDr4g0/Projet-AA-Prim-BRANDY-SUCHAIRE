// PrimM.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include "../Algo-Prim/AlgoPrim.h"

using std::cout;
using std::endl;
using std::cerr;

int main(int argc,char *argv[])
{
    if (argc < 3) {
        cerr << "Error Not Enough Arguments : The program need at least 2 arguments !" << endl;
        return 1;
    }

    if (argc > 4) {
        cerr << "Error Too Many Arguments : The program need only 2 to 3 arguments !" << endl;
        return 1;
    }

    std::string fileGraph = argv[1];

    try {
        unsigned int origin = std::stoi(argv[2]);

        AlgoPrim AlgoPM;
        AlgoPM.convertFileGraphM(fileGraph);
        AlgoPM.setOriginM(origin);

        if (argc == 4) {
            AlgoPM.executePrimForM(argv[3]);
            cout << "The has succesfully been written in " << argv[3] << " !" << endl;
        }
        else {
            AlgoPM.executePrimForM();
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;  // Return an error code
    }
    
    

  
    return 0;
}