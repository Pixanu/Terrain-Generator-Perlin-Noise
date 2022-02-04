#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>

class Texture {
	public:
		GLuint textures[2];

		Texture();
		void Bind(int index);
		void LoadTexture(std::string filepath, GLenum texIndex, unsigned int shaderprogram);
		~Texture();
	};




#endif // !TEXTURE_H



