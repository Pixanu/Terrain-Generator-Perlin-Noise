#include "Texture.h"
#include "Shader.h"

Texture::Texture()
{
	
	LoadTexture(".\\Assets\\grass.jpg", GL_TEXTURE0, 0);
	//LoadTexture(".\\Assets\\water2.jpg", GL_TEXTURE1,0);
}

void Texture::Bind(int index)
{
	glBindTexture(GL_TEXTURE_2D, textures[index]);
}

void Texture::LoadTexture(std::string filepath, GLenum texIndex, unsigned int shaderProgram)
{
	int width, height;
	unsigned char* texture = SOIL_load_image(filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	if (texture)
	{
		std::cout << "Loaded texture: " + filepath << std::endl;
	}
	else
	{
		std::cerr << "Texture " + filepath + " failed to load!" << std::endl;
	}
	
	//Terrain Texture
	glGenTextures(2, textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), textures[0]-1);

	//Water Texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shaderProgram, "water"), textures[1]-1);
	

}

Texture::~Texture()
{
	glDeleteTextures(1, &textures[2]);





}
