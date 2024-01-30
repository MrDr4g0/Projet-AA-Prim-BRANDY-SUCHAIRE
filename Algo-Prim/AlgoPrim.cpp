// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"
#include <iostream>
#include <fstream>
#include <chrono>


AlgoPrim::AlgoPrim() : graphL(0), graphM(0),originL(0), originM(0)
{
}
void AlgoPrim::convertFileGraphM(std::string file)
{
}
void AlgoPrim::convertFileGraphL(std::string file)
{
	std::ifstream inputFile(file);


	if (!inputFile.is_open())
		std::cout << "File cannot open : " << file << std::endl;
	else
	{
        // Read the number of vertices
        int numVertices;
        inputFile >> numVertices;

        // Creating a graph with the same number of vertices
        OurList<VertexL> graph(numVertices);

        // Read vertex data
        for (int i = 0; i < numVertices; ++i) {
            
            unsigned int vertexNumber;
            inputFile >> vertexNumber;

            // Read neighbors and distances
            unsigned int neighborVertex, distance;
            OurList<edge> neigbhors;

            // Je ne parcours pas de la bonne manière

            while (inputFile >> neighborVertex && neighborVertex != 0) {
                
                // Check the distance
                if (!(inputFile >> distance)) {
                    std::cerr << "Error reading distance for vertex " << vertexNumber << std::endl;
                    break;
                }
                
                // add neighbors
                edge neighbor{ distance, neighborVertex };
                neigbhors.insert_back(neighbor);
                
                // 
                for (int i = 0; i < graph.getSize(); i++) {
                    if (graph[i].getValue() == neighborVertex) {
                        graph[i].AddNeighbor(vertexNumber, distance);
                    }
                }
            }

            VertexL vertex(vertexNumber, neigbhors);

            

            // Add Vertex
            graph.insert_back(vertex);

            for (int j = 0; j < graph.getSize(); j++) {
                VertexL cvertex = graph[j];
                cvertex.getValue();
                OurList<edge> neigbhorss = cvertex.getNeighbors();
            }
        }

        graphL = graph;
    }
}
void AlgoPrim::executePrimForL(std::string outputFile , int start)
{    
    // Start algo
    std::chrono::high_resolution_clock::time_point startClock = std::chrono::high_resolution_clock::now();

    // Collect size of graph
    size_t graphSize = graphL.getSize();

    // create an empty tree
    OurList<VertexL> finalTree(graphSize);

    // create tree of visited vertex
    OurList<bool> inTree(graphSize, false);

    // I choose my start point
    for (int i = 0; i < graphSize; i++) {
        if (start == graphL[i].getValue()) // My vertex exist
        {
            inTree[i] = true; // set start to visited 

            finalTree.insert_back(graphL[i].getValue()); // add the start to the final Tree

            unsigned int lesscost;
            unsigned int father;
            unsigned int child;

            // graphSize is the number of steps of the algorithm
            for (int j = 0; j < graphSize; j++) {
                lesscost = UINT_MAX;
                // check each vertex of the tree
                for (int k = 0; k < finalTree.getSize(); k++) {
                    // for each neighbors
                    for (int l = 0; l < graphL[finalTree[k].getValue()-1].getNeighbors().getSize(); l++) {
                        //Verify the most less cost and also if its not visited
                        if (graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_cost < lesscost && !inTree[graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_value-1]) {
                            lesscost = graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_cost;
                            child = graphL[finalTree[k].getValue()-1].getNeighbors()[l].v_value;

                            father = graphL[finalTree[k].getValue()-1].getValue();
                        }
                    }
                }

                if (lesscost != UINT_MAX) {
                    // add the next vertex and the edge
                    VertexL newVertex(child);
                            
                    newVertex.AddNeighbor(father, lesscost);

                    for (int i = 0; i < finalTree.getSize(); i++) {
                         if (finalTree[i].getValue() == father) {
                             finalTree[i].AddNeighbor(child, lesscost);
                         }
                    }

                    finalTree.insert_back(newVertex);

                    inTree[child - 1] = true;
                }
            }
            break;
        }
    }
    // End algo
    std::chrono::high_resolution_clock::time_point endClock = std::chrono::high_resolution_clock::now();

    // Total time
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(endClock - startClock);

    
    // If the user want to write in a file
    std::ofstream output(outputFile, std::ios::out);

    // Check if graph is connexe 
    bool isConnex = true;
    for (int i = 0; i < inTree.getSize(); i++) {
        if (inTree[i] == false) {
            isConnex = false;
        }
    }

    // If its not specified
    if (outputFile == "")
    {
        // Check if its connexe
        isConnex ? std::cout << "LE GRAPHE EST CONNEXE" << std::endl << std::endl : std::cout << "LE GRAPHE N'EST PAS CONNEXE" << std::endl << std::endl;

        // print start point
        std::cout << "L'arbre couvrant a partir de : " << start << std::endl;

        // print my final tree
        for (size_t i = 0; i < finalTree.getSize(); i++) {
            if (i == 0) {
                std::cout << "(" << finalTree[i].getValue() << " -> _ : _)" << std::endl;
            }
            else if (i > 0) {
                std::cout << "(" << finalTree[i].getValue() << " -> " << finalTree[i].getNeighbors()[0].v_value << " : " << finalTree[i].getCost(finalTree[i].getValue()) << ")" << std::endl;
            }
        }

        std::cout << std::endl << "Temps d'execution de l'algorithme de Prim sur les listes d'adjacence est de : " << duration.count() << " micros" << std::endl;

    }
    else {
        // Check if its connexe
        isConnex ? output << "LE GRAPHE EST CONNEXE" << std::endl << std::endl : output << "LE GRAPHE N'EST PAS CONNEXE" << std::endl << std::endl;

        // print start point
        output << "L'arbre couvrant a partir de : " << start << std::endl;

        // Write in the final tree
        for (size_t i = 0; i < finalTree.getSize(); i++) {
            if (i == 0) {
                output << "(" << finalTree[i].getValue() << " -> _ : _)" << std::endl;
            }
            else if (i > 0) {
                output << "(" << finalTree[i].getValue() << " -> " << finalTree[i].getNeighbors()[0].v_value << " : " << finalTree[i].getCost(finalTree[i].getValue()) << ")" << std::endl;
            }
        }

        // Write execution time 
        output << std::endl << "Temps d'execution de l'algorithme de Prim sur les listes d'adjacence est de : " << duration.count() << " micros" << std::endl;
        output.close();


    }
};
