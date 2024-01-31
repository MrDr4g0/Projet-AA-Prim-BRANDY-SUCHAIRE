// PrimL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../Algo-Prim/VertexL.h"
#include "../Algo-Prim/AlgoPrim.h"

using std::cout;
using std::endl;

int main() {
    
    AlgoPrim algo;
    algo.convertFileGraphL("../graph3.txt");
    algo.executePrimForL("", 2);

}

/*
int main(int argc, char** argv)
{
    AlgoPrim algo;
      algo.convertFileGraphL("../test.txt");
      algo.executePrimForL("", 4);

    bool isValid = false;

    while (!isValid) {
        if (argc > 1) {
            // first argument : name of the file that contain the graph
            algo.convertFileGraphL(argv[1]);
            // second argument : le sommet de départ
            if (argc > 3)
                algo.executePrimForL(argv[3], std::atoi(argv[2]));
            // troisième argument (optionnel) : pour indiquer le fichier ou écrire les infos 
            else
                algo.executePrimForL("", std::atoi(argv[2]));

            isValid = true;
        }
        else {
            std::cerr << "Invalid command, syntax : " << std::endl;
            std::cerr << "./file.exe graphfile.txt int finalgraph.txt" << std::endl;
        }
    }
}
*/