#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm.hpp>


class Graphics
{
public:
	SDL_Window* window;
	SDL_GLContext glContext;

	Graphics();
	Graphics(const char* title, int resX, int resY);
	void DrawMesh(GLuint elementBufferObject, std::vector<unsigned short> indices);
	void DrawNormals(GLuint normalVAO, int numVertices);
	void ShowWireframe(bool enabled);
	void Render();
	~Graphics();




};

#endif // !GRAPHICS_H





