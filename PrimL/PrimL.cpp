// PrimL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../Algo-Prim/VertexL.h"
#include "../Algo-Prim/AlgoPrim.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    //std::cout << "Hello World!\n";

    //OurList<OurList<unsigned int>> matrix(4);

    //matrix.insert_back(OurList<unsigned int>(4));
    //matrix.insert_back(OurList<unsigned int>(4));
    //matrix.insert_back(OurList<unsigned int>(4));
    //matrix.insert_back(OurList<unsigned int>(4));
    //
    //for (size_t i = 0; i < matrix.getSize(); ++i) {
    //    // Accessing individual containers
    //    OurList<unsigned int>& innerList = matrix[i];

    //    // Adding elements to inner containers
    //    innerList.insert_back(1);
    //    innerList.insert_back(2);
    //    innerList.insert_back(5);
    //    innerList.insert_back(std::numeric_limits<unsigned int>::max());
    //}

    //cout << matrix[0][3];
    AlgoPrim algo;
    algo.convertFileGraphL("../test.txt");
    algo.executePrimForL("", 4);

    /*if (argc > 1) {
        cout << "salut" << std::endl;
        algo.convertFileGraphL(argv[1]);
    }*/
}