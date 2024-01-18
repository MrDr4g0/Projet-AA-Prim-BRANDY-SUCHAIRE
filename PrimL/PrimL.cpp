// PrimL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../Algo-Prim/VertexL.h"
#include "../Algo-Prim/AlgoPrim.h"

using std::cout;
using std::endl;

int main()
{
    std::cout << "Hello World!\n";

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

    OurList<VertexM> graphM(2);

    graphM.empty() ? cout << "oui" << endl : cout << "non" << endl;

    AlgoPrim a;
    a.convertFileGraphM("../graph.txt");

    graphM = a.getGraphM();
    a.setOriginM(2);
    graphM.empty() ? cout << "oui" << endl : cout << "non" << endl;

    /*
    for (size_t i = 0; i < graphM.getSize(); ++i) {
        cout << graphM[i] << endl;
    }
    */

    a.executePrimForM();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
