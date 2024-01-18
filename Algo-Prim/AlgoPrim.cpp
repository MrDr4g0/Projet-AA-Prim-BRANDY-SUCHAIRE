// Algo-Prim.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "AlgoPrim.h"
#include <iostream>
#include <fstream>

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

        // Creating graph
        OurList<VertexL> graph(numVertices);


        // Read vertex data
        for (int i = 0; i < numVertices; ++i) {
            
            int vertexNumber;
            inputFile >> vertexNumber;
            VertexL vertex(vertexNumber);

            // Read neighbors and distances
            int neighborVertex, distance;
            while (inputFile >> neighborVertex && neighborVertex != 0) {

                // Check the distance
                if (!(inputFile >> distance)) {
                    std::cerr << "Error reading distance for vertex " << vertexNumber << std::endl;
                    break;
                }

                VertexL neighbor(neighborVertex);
                vertex.AddNeighbor(neighborVertex, distance);
            }

            // Add Vertex
            graph.insert_back(vertex);
        }

        for (int i = 0; i < graph.getSize(); i++) {
            std::cout <<"Sommet : "<< graph[i] << std::endl;
            std::cout << "Liste d'adjacence : " << std::endl;
            OurList<edge> neighbors = graph[i].getNeighbors();
            for (int j = 0; j < neighbors.getSize(); j++) {
                std::cout << "valeur : " << neighbors[j].v_value << " ";
                std::cout << "distance : " << neighbors[j].v_cost << std::endl;
            }
            std::cout << std::endl;
        }
    }
};
