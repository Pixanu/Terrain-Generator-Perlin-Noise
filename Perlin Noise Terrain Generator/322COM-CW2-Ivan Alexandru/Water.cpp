#include "Water.h"

Water::Water()
{

}

Water::Water(int rows, int cols)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	const double PI = 3.14159265358979323846264338327950288;
	pos = glm::vec3(0, 7, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	this->rows = rows;
	this->cols = cols;
	numVertices = 0;

	createMesh(rows, cols);
	createNormals();

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords2;
	std::vector<glm::vec3> normals;

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos);
		texCoords2.push_back(vertices[i].texCoord);
		normals.push_back(vertices[i].CalculateNormal());
		normalsPos.push_back(vertices[i].pos);
		normalsPos.push_back(
			glm::vec3(
				vertices[i].pos.x + normals[i].x,
				vertices[i].pos.y + normals[i].y,
				vertices[i].pos.z + normals[i].z
			)
		);
	}

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, vertexBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[POSITION_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_INDEX);
	glVertexAttribPointer(POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[TEXCOORD_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords2[1]), &texCoords2[1], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXCOORD_INDEX);
	glVertexAttribPointer(TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[NORMAL_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_INDEX);
	glVertexAttribPointer(NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObject[ELEMENT_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	//Normal vertices
	glGenVertexArrays(1, &normalsVAO);
	glGenBuffers(1, normalsVBO);

	glBindVertexArray(normalsVAO);

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, normalsPos.size() * sizeof(normalsPos[1]), &normalsPos[1], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(1);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	std::cout << "Generated map in: " << elapsedTime.count() << " seconds, " << numVertices << " vertices" << std::endl;

}

void Water::createMesh(int rows, int cols)
{
	//PerlinNoise pn(time(NULL));
	double xOff = 0;
	double zOff = 0;
	double min = 0;
	double max = 0;
	double noiseValue = 0.0;
	float modifier = GetRandF(0.01f, 0.08f);

	std::cout << "Max height that can be allocated: " << max << " - Modifier: " << modifier << std::endl;

	for (int i = 0; i < rows; i++)
	{
		xOff = 0.0;

		for (int j = 0; j < cols; j++)
		{
			glm::vec3 vertPos = glm::vec3((-1.0f * cols / 4) + (j * 0.5f), 0, (1.0f * rows / 4) - (i * 0.5f));
			//noiseValue = pn.noise(xOff, 0, zOff);
			vertPos.y = MapValue(min, max, noiseValue);

			createVertex(vertPos, glm::vec2(j, i));

			xOff += modifier;
		}
		zOff += modifier;
	}

	bool firstRow = true;

	for (int i = 0; i < numVertices; i++)
	{
		int a = i;
		int b = i + cols;
		int c = i + cols + 1;
		int d = i + 1;

		if ((i + 1) % cols == 0) continue;
		if (i >= (rows * cols) - cols) continue;

		indices.push_back(a);
		indices.push_back(d);
		indices.push_back(b);

		indices.push_back(b);
		indices.push_back(d);
		indices.push_back(c);

	}

}


void Water::createNormals()
{

	for (int i = 0; i != indices.size(); i += 3) {

		try
		{
			Vertex p1 = vertices.at(indices.at(i));
			Vertex p2 = vertices.at(indices.at(i + 1));
			Vertex p3 = vertices.at(indices.at(i + 2));

			glm::vec3 U(p2.pos - p1.pos);
			glm::vec3 V(p3.pos - p1.pos);

			glm::vec3 normal = glm::cross(U, V);

			vertices.at(indices.at(i)).AddNormal(normal);
			vertices.at(indices.at(i + 1)).AddNormal(normal);
			vertices.at(indices.at(i + 2)).AddNormal(normal);

		}
		catch (const std::out_of_range& e)
		{
			std::cout << "Error: index out of range: " << i << std::endl;
		}
	}

}

void Water::createVertex(glm::vec3 pos, glm::vec2 texCoord2)
{
	vertices.push_back(Vertex(pos, texCoord2));
	numVertices++;
}

Water::~Water()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}


