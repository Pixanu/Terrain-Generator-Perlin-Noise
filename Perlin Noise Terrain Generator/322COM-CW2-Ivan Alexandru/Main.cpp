#include <SDL.h>
#include "Graphics.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "MeshLight.h"
#include "MeshTerrain.h"
#include "Water.h"

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event e = SDL_Event();

	const char* title = "3D Perlin Noise Terrain - Ivan Alexandru";
	int resX = 1280;
	int resY = 720;
	float lightPosCounter = 0;
	float normalSpeed = 0.1f;
	float movementSpeed = normalSpeed;

	//srand(time(NULL));

	bool cursorLocked = false;
	bool forward = false;
	bool backward = false;
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
	bool turbo = false;
	bool slow = false;

	bool isRunning = true;
	bool showWireframe = true;
	bool showLight = true;
	bool showNormals = false;

	
	Graphics graphics = Graphics(title, resX, resY);
	Camera camera = Camera(resX, resY, 0.01f, 1000.0f);
	Texture texture = Texture();

	//SHADERS
	Shader shader = Shader(".\\Shaders\\shader");
	Shader lightShader = Shader(".\\Shaders\\light");
	Shader normalShader = Shader(".\\Shaders\\normal");

	//MESHES
	MeshTerrain terrain = MeshTerrain(200, 200);
	Water water = Water(200, 200);
	MeshLight light = MeshLight(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));

	while (isRunning) {


		shader.Bind();
		texture.Bind(0);
		texture.Bind(1);
		

		// Render terrain mesh
		shader.Bind();
		shader.Update(terrain.getPos(), terrain.getRotation(), terrain.getScale(), camera.view, 
					 camera.projection, camera.cameraPos, light.getPos());
		graphics.DrawMesh(terrain.getVAO(), terrain.getIndices());

		//render water mesh
		shader.Bind();
		shader.Update(water.getPos(), water.getRotation(), water.getScale(), camera.view, camera.projection, camera.cameraPos, light.getPos());
		graphics.DrawMesh(water.getVAO(), water.getIndices());


		//Light pos right side - Comment to deactivate the stationary light inside the scene
		//light.setPos(glm::vec3(10, 80, 180));
		
		//"Day n Night Mode - Light is circling the mesh - Comment to deactivate
		light.setPos(glm::vec3(sin(lightPosCounter) * 100, cos(lightPosCounter) * 100, 0));
		lightPosCounter += 0.002;

		if (showWireframe)
		{
			// Render terrain wireframes
			graphics.ShowWireframe(true);
			shader.ShowWireframe(true);
			shader.Update(terrain.getPos(), terrain.getRotation(), terrain.getScale(), camera.view, camera.projection, camera.cameraPos, light.getPos());
			graphics.DrawMesh(terrain.getVAO(), terrain.getIndices());
			graphics.ShowWireframe(false);
			shader.ShowWireframe(false);
		}

		if (showNormals)
		{
			// Render lines for normals
			normalShader.Bind();
			normalShader.Update(terrain.getPos(), terrain.getRotation(), terrain.getScale(), camera.view, camera.projection, camera.cameraPos, light.getPos());
			graphics.DrawNormals(terrain.getNormalsVAO(), terrain.getNormalsPos().size());
		}
		if (showLight)
		{
			// Render light mesh
			lightShader.Bind();
			lightShader.Update(light.getPos(), glm::vec3(0, 0, 0), light.getScale(), camera.view, camera.projection, camera.cameraPos, light.getPos());
			graphics.DrawMesh(light.getVAO(), light.getIndices());
		}

		graphics.Render();


		movementSpeed = normalSpeed;
		if (turbo) movementSpeed *= 4;
		if (slow) movementSpeed /= 4;
		if (forward) camera.Move(camera.cameraPos + (camera.forward * movementSpeed));
		if (backward) camera.Move(camera.cameraPos - (camera.forward * movementSpeed));
		if (up) camera.Move(camera.cameraPos + (camera.up * movementSpeed));
		if (down) camera.Move(camera.cameraPos - (camera.up * movementSpeed));
		if (left) camera.Move(camera.cameraPos - (camera.right * movementSpeed));
		if (right) camera.Move(camera.cameraPos + (camera.right * movementSpeed));
		camera.Update();

		// Controls and user input
		while (SDL_PollEvent(&e))
		{

			if (e.type == SDL_KEYDOWN)
			{

				switch (e.key.keysym.scancode)
				{
				case(SDL_SCANCODE_W):
					forward = true;
					break;
				case(SDL_SCANCODE_A):
					left = true;
					break;
				case(SDL_SCANCODE_S):
					backward = true;
					break;
				case(SDL_SCANCODE_D):
					right = true;
					break;
				case(SDL_SCANCODE_Z):
					showWireframe = (showWireframe) ? false : true;
					break;
				case(SDL_SCANCODE_X):
					showNormals = (showNormals) ? false : true;
					break;
				case(SDL_SCANCODE_C):
					showLight = (showLight) ? false : true;
					shader.ShowLight(showLight);
					break;
				case(SDL_SCANCODE_LCTRL):
					down = true;
					break;
				case(SDL_SCANCODE_LSHIFT):
					turbo = true;
					break;
				case(SDL_SCANCODE_LALT):
					slow = true;
					break;
				case(SDL_SCANCODE_SPACE):
					up = true;
					break;
				case(SDL_SCANCODE_ESCAPE):
					SDL_SetRelativeMouseMode(SDL_FALSE);
					SDL_ShowCursor(SDL_ENABLE);
					cursorLocked = false;
					break;
				case(SDL_SCANCODE_RETURN):
					terrain.~MeshTerrain();
					new (&terrain) MeshTerrain(200, 200);
					break;
				}

			}

			if (e.type == SDL_KEYUP)
			{

				switch (e.key.keysym.scancode)
				{
				case(SDL_SCANCODE_W):
					forward = false;
					break;
				case(SDL_SCANCODE_A):
					left = false;
					break;
				case(SDL_SCANCODE_S):
					backward = false;
					break;
				case(SDL_SCANCODE_D):
					right = false;
					break;
				case(SDL_SCANCODE_LCTRL):
					down = false;
					break;
				case(SDL_SCANCODE_LSHIFT):
					turbo = false;
					break;
				case(SDL_SCANCODE_LALT):
					slow = false;
					break;
				case(SDL_SCANCODE_SPACE):
					up = false;
					break;
				}

			}

			if (e.type == SDL_MOUSEMOTION)
			{

				if (cursorLocked)
				{
					SDL_WarpMouseInWindow(graphics.window, resX / 2, resY / 2);
					camera.Rotate(-e.motion.xrel, -e.motion.yrel);
				}

			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{

				if (e.button.button == SDL_BUTTON_LEFT)
				{
					SDL_SetRelativeMouseMode(SDL_TRUE);
					SDL_ShowCursor(SDL_DISABLE);
					cursorLocked = true;
				}

			}

			if (e.type == SDL_QUIT)
			{
				isRunning = false;
			}

			if (e.type == SDL_WINDOWEVENT)
			{

				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					resX = e.window.data1;
					resY = e.window.data2;
					camera.SetResolution(e.window.data1, e.window.data2);
					glViewport(0, 0, e.window.data1, e.window.data2);
				}

				if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				{
					cursorLocked = false;
					e.motion.xrel = 0;
					e.motion.yrel = 0;
					SDL_ShowCursor(SDL_ENABLE);
				}

			}

		}
	}

	return 0;
}

 