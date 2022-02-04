#ifndef MESHLIGHT_H
#define MESHLIGHT_H

#include "Mesh.h"
#include <glm.hpp>
#include <GL/glew.h>
#include <vector>


class MeshLight : public Mesh
{
public:
	MeshLight();
	MeshLight(glm::vec3 pos, glm::vec3 scale);
	void CreateMesh();
	void CreateVertex(glm::vec3 pos);
	~MeshLight();

};

#endif // !MESHLIGHT_H