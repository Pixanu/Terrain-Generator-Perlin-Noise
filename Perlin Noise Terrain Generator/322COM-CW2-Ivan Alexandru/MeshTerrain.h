#ifndef MESHTERRAIN_H
#define MESHTERRAIN_H

#include "Mesh.h"
#include <chrono>
#include "PerlinNoise.h"
#include <math.h>
#include <iostream>

class MeshTerrain : public Mesh
{

public:
	int rows, cols;

	MeshTerrain();
	MeshTerrain(int rows, int cols);
	void createMesh(int rows, int cols);
	void createNormals();
	void createVertex(glm::vec3 pos, glm::vec2 texCoord);
	~MeshTerrain();

};

#endif // !MESHTERRAIN_H
