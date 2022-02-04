#ifndef VERTEX_H
#define VERTEX_h

#include <glm.hpp>
#include <vector>

using namespace std;

class Vertex
{
public:
	glm::vec3 pos;
	glm::vec2 texCoord;
	vector<glm::vec3> normals;

	Vertex();
	Vertex(glm::vec3 pos);
	Vertex(glm::vec3 pos, glm::vec2 texCoord);
	void AddNormal(glm::vec3 normal);
	glm::vec3 CalculateNormal();
	~Vertex();

};


#endif // !VERTEX_H




