#ifndef WATER_H
#define WATER_H

#include "Mesh.h"
#include <chrono>
//#include "PerlinNoise.h"
#include <math.h>
#include <iostream>

class Water : public Mesh
{

public:
	int rows, cols;

	Water();
	Water(int rows, int cols);
	void createMesh(int rows, int cols);
	void createNormals();
	void createVertex(glm::vec3 pos, glm::vec2 texCoord2);
	~Water();

};

#endif // WATER_H

