#include "Tema2.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <Core/Engine.h>
#include <time.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

float Tema2::randomNumber(float low, float high)
{
	float randomNumber = low + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (high - low)));
	return randomNumber;
}

void Tema2::SetInitialScene()
{
	float z = -1.0f;
	float scaleZ = 2.5f;

	// add the platforms to the initial scene
	while (z > -5.0f)
	{
		initialColumn1.push_back(make_tuple(z, scaleZ, blue));
		initialColumn2.push_back(make_tuple(z, scaleZ, blue));
		initialColumn3.push_back(make_tuple(z, scaleZ, blue));

		z -= scaleZ;
	}

	initialColumn1.push_back(make_tuple(z, scaleZ, blue));
	initialColumn3.push_back(make_tuple(z, scaleZ, blue));

	z -= scaleZ - 0.5f;
	initialColumn2.push_back(make_tuple(z, scaleZ, blue));

	z -= scaleZ - 0.5f;
	initialColumn1.push_back(make_tuple(z, scaleZ, blue));
	initialColumn3.push_back(make_tuple(z, scaleZ, blue));

	z -= scaleZ - 0.5f;
	initialColumn2.push_back(make_tuple(z, scaleZ, blue));

	// different numbers
	//std::srand(time(NULL));

	// first column
	int currentZ = z - scaleZ;
	while (currentZ > -30.0f)
	{
		// generate a random distance between platform
		currentZ -= randomNumber(1.0, 3.0);
		scaleZ = randomNumber(1.5, 2.5);
		initialColumn1.push_back(make_tuple(currentZ, scaleZ, blue));
		currentZ -= scaleZ + randomNumber(1.0, 2.0) + randomNumber(1.0, 2.0);
	}

	// second column
	currentZ = z - scaleZ;
	while (currentZ > -30.0f)
	{
		// generate a random distance between platform
		currentZ -= randomNumber(0.5, 1.0);
		scaleZ = randomNumber(1.5, 3.0);
		initialColumn2.push_back(make_tuple(currentZ, scaleZ, blue));
		currentZ -= scaleZ + randomNumber(0.5, 1.5) + randomNumber(0.5, 1.5);
	}

	// third column
	currentZ = z - scaleZ;
	while (currentZ > -30.0f)
	{
		// generate a random distance between platform
		currentZ -= randomNumber(1.0, 3.0);
		scaleZ = randomNumber(1.5, 3.0);
		initialColumn3.push_back(make_tuple(currentZ, scaleZ, blue));
		currentZ -= scaleZ + randomNumber(1.5, 3.0);
	}
}

void Tema2::SetInitialValues()
{
	// set Y position for the platforms
	platformY = 0.075;

	// set X position for each column of the platforms
	firstColumnX = -1.40;
	secondColumnX = 0;
	thirdColumnX = 1.40;

	// initial Scene
	SetInitialScene();

	// set Z distance (where the platforms start to appear)
	distanceZ = -20.0f;

	translateXPlayer = 0;
	translateYPlayer = 0.3f;
	playerSpeed = 0;
	maximPosition = 1.5f;
	deltatime = 5.0;

	combustibleScale = 0.30f;
	scaleBall = 1;

	// initial: above the middle platform
	minimPosition = translateYPlayer;

	// set initial values
	jump = false;
	goBack = true;
	rotate = false;
	collisionBallPlatform = false;
	downBall = false;
	gameOver = false;
	speedRun = false;
}

void Tema2::Init()
{

	SetInitialValues();
	renderCameraTarget = false;
	camera = new TemaCamera::Camera();

	// third camera person
	renderCameraTarget = true;
	camera->Set(glm::vec3(0, 1, 1.8f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	projectionType = true;

	// use for the user interface
	userCamera = new TemaCamera::Camera();

	{
		Mesh *mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh *mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh *mesh = new Mesh("quad");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		glm::vec3 corner = glm::vec3(0.0, 0.0, 0.0);
		float side1 = 0.36;
		float side2 = 0.09;
		glm::vec3 color = red;

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),														   // 0
			VertexFormat(corner + glm::vec3(-side1 / 2.0, side1, 0), color),					   // 1
			VertexFormat(corner + glm::vec3(+side1 / 2.0, side1, 0), color),					   // 2
			VertexFormat(corner + glm::vec3(+side1 / 2.0 - side2 / 2.0, side1 + side2, 0), color), // 3
			VertexFormat(corner + glm::vec3(+side1 / 2.0 - side2, side1, 0), color),			   // 4
			VertexFormat(corner + glm::vec3(side2 / 2.0, side1 + side2, 0), color),				   // 5
			VertexFormat(corner + glm::vec3(0, side1, 0), color),								   // 6
			VertexFormat(corner + glm::vec3(-side2 / 2.0, side1 + side2, 0), color),			   // 7
			VertexFormat(corner + glm::vec3(-side2, side1, 0), color),							   // 8
			VertexFormat(corner + glm::vec3(-side1 / 2.0 + side2 / 2.0, side1 + side2, 0), color)  // 9
		};

		std::vector<unsigned short> indices = {
			0, 1, 2,
			2, 3, 4,
			4, 3, 5,
			4, 5, 6,
			6, 7, 8,
			8, 7, 9,
			8, 9, 1 };

		Mesh* mesh = new Mesh("heart");
		mesh->InitFromData(vertices, indices);
		mesh->SetDrawMode(GL_TRIANGLES);
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// Create a shader program for drawing face polygon with the color of the normal for the platforms
	{
		Shader *shader = new Shader("PlatformShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal for the ball
	{
		Shader *shaderBall = new Shader("BallShader");
		shaderBall->AddShader("Source/Laboratoare/Tema2/ShadersBall/VertexShader.glsl", GL_VERTEX_SHADER);
		shaderBall->AddShader("Source/Laboratoare/Tema2/ShadersBall/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shaderBall->CreateAndLink();
		shaders[shaderBall->GetName()] = shaderBall;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

// utility function to find ceiling of r in arr[l..h]
int findCeil(int arr[], int r, int l, int h)
{
	int mid;
	while (l < h)
	{
		mid = l + ((h - l) >> 1); // Same as mid = (l+h)/2
		(r > arr[mid]) ? (l = mid + 1) : (h = mid);
	}
	return (arr[l] >= r) ? l : -1;
}

// used to generate random colors for the platforms
glm::vec3 Tema2::GenerateARandomPlatform()
{
	std::vector<glm::vec3> colors;
	// add colors
	colors.push_back(blue);	
	colors.push_back(red);
	colors.push_back(yellow);
	colors.push_back(orange);
	colors.push_back(green);
	colors.push_back(pink);
	colors.push_back(gray);
	int nrColors = 7;

	// frequency of platforms
	int freq[] = {250, 5, 15, 10, 15, 15, 15};

	// use a different seed value for every run.
	//std::srand(NULL);

	int prefix[8], i;
	prefix[0] = freq[0];
	for (i = 1; i < nrColors; ++i)
	{
		prefix[i] = prefix[i - 1] + freq[i];
	}

	// prefix[n-1] is sum of all frequencies
	// generate a random number with value from 1 to this sum
	int r = (rand() % prefix[nrColors - 1]) + 1;

	// find index of ceiling of r in prefix arrat
	int indexc = findCeil(prefix, r, 0, nrColors - 1);

	return colors.at(indexc);
}

void Tema2::CheckCollision(float deltaTimeSeconds, float column, std::vector<tuple<float, float, glm::vec3>> &initialColumn, int i, glm::mat4 modelMatrix)
{
	// check collision between ball and each platform
	float radius = 0.15f;
	float cubeXmin = column - 0.45f;
	float cubeXmax = column + 0.45f;
	float cubeYmin = platformY - 0.075f;
	float cubeYmax = platformY + 0.075f;
	float cubeZmin = std::get<0>(initialColumn[i]) - std::get<1>(initialColumn[i]) / 2.0;
	float cubeZmax = std::get<0>(initialColumn[i]) + std::get<1>(initialColumn[i]) / 2.0;

	// is collision and the ball is above the platform
	if (Collision(translateXPlayer, translateYPlayer, 0, cubeXmin, cubeYmin, cubeZmin,
				  cubeXmax, cubeYmax, cubeZmax, radius) && !downBall)
	{
		// special platforms
		glm::vec3 colorCollision = std::get<2>(initialColumn[i]);
		if (colorCollision == red)
		{
			// end the game
			gameOver = true;
			lives = 0;
		}
		else if (colorCollision == yellow)
		{
			// lose some combustible
			combustibleScale -= deltaTimeSeconds * 2.0;
		}
		else if (colorCollision == orange)
		{
			// block w, s & fast speed for deltatime = 5 seconds
			speedRun = true;
			initialSpeed = playerSpeed;
			playerSpeed = 5.0f;

			// to check delta time
			start_time = time(NULL);
		}
		else if (colorCollision == green)
		{
			// gain some combustible
			combustibleScale += deltaTimeSeconds * 2.0;
		}
		else if (colorCollision == pink && lives < 7) {
			// + one life
			lives++;
		}
		else if (colorCollision == gray) {
			// - one life
			lives--;
			if (lives == 0) {
				gameOver = true;
			}
		}

		// for collision -> violet
		std::get<2>(initialColumn[i]) = glm::vec3(0.5, 0, 1);
		RenderSimpleMesh(meshes["box"], shaders["PlatformShader"], modelMatrix, std::get<2>(initialColumn[i]), camera, projectionMatrix);
		collisionBallPlatform = true;
	}
	else
	{
		RenderSimpleMesh(meshes["box"], shaders["PlatformShader"], modelMatrix, std::get<2>(initialColumn[i]), camera, projectionMatrix);
	}
}

void Tema2::InitialScene(float deltaTimeSeconds, float column, std::vector<tuple<float, float, glm::vec3>> &initialColumn, int n)
{
	// for each platform in the current column
	for (int i = 0; i < n; i++)
	{
		if (std::get<0>(initialColumn[i]) < 10)
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			// new Z position
			std::get<0>(initialColumn[i]) += deltaTimeSeconds * playerSpeed; 
			modelMatrix = glm::translate(modelMatrix, glm::vec3(column, platformY, std::get<0>(initialColumn[i])));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.9f, 0.15f, std::get<1>(initialColumn[i])));

			// check collision between the ball and each platform
			CheckCollision(deltaTimeSeconds, column, initialColumn, i, modelMatrix);
		}

		// add new platforms and delete the platforms behind the player
		if (std::get<0>(initialColumn[i]) > 10)
		{
			glm::vec3 currentColor = GenerateARandomPlatform();

			// delete the current platform from the vector
			initialColumn.erase(initialColumn.begin() + i);
		
			// add a new platform to the vector
			if (column == 0)
			{
				float scaleZ = randomNumber(1.0f, 2.5f);
				initialColumn.push_back({distanceZ, scaleZ, currentColor});
			}
			else
			{
				float scaleZ = randomNumber(1.5f, 2.5f);
				initialColumn.push_back({distanceZ, scaleZ, currentColor});
			}
		}
	}
}

bool Tema2::Collision(float sphereX, float sphereY, float sphereZ, float cubeXmin, float cubeYmin, float cubeZmin,
					  float cubeXmax, float cubeYmax, float cubeZmax, float sphereRadius)
{
	// get box closest point to sphere center by clamping
	float x = std::max(cubeXmin, std::min(sphereX, cubeXmax));
	float y = std::max(cubeYmin, std::min(sphereY, cubeYmax));
	float z = std::max(cubeZmin, std::min(sphereZ, cubeZmax));

	// check collision
	float distance = std::sqrt((x - sphereX) * (x - sphereX) +
							   (y - sphereY) * (y - sphereY) + (z - sphereZ) * (z - sphereZ));

	if (distance < sphereRadius)
	{
		return true;
	}

	return false;
}

void Tema2::MoveBall(float deltaTimeSeconds)
{
	// if the ball is below the top edge of the platform
	if (translateYPlayer < 0.30f && !collisionBallPlatform)
	{
		downBall = true;

		// the ball falls to the lower limit
		if (translateYPlayer > -1.5f)
		{
			if (translateYPlayer > 0)
			{
				translateYPlayer -= deltaTimeSeconds * 2.5;
			}
			else
			{
				translateYPlayer -= deltaTimeSeconds * 0.70;
			}
		}
		else
		{
			gameOver = true;
			lives--;
		}
	}
	else
	{
		// the ball jumps
		if (translateYPlayer > minimPosition && jump == false && goBack == false)
		{
			translateYPlayer -= deltaTimeSeconds * 2.0;
		}
		else
		{
			goBack = true;
		}
	}
}

void Tema2::SetCameraType()
{
	// first camera person
	if (!renderCameraTarget && !rotate)
	{
		camera->Set(glm::vec3(translateXPlayer, translateYPlayer, -0.15f), glm::vec3(translateXPlayer, translateYPlayer, -0.16f), glm::vec3(0, 1, 0));
	}
	// third camera person
	else if (renderCameraTarget && !rotate)
	{
		camera->Set(glm::vec3(-translateXPlayer / 5, -translateYPlayer / 5 + 1.5, 2.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	}
}

void Tema2::RenderBall(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(translateXPlayer, translateYPlayer, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.30f));
		if (downBall)
		{
			scaleBall -= deltaTimeSeconds * 0.50;
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleBall));
		}


		// render the ball
		if (!speedRun) {
			RenderMeshCamera(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
		}
		// render the deformed ball, if the ball lands on the orange platform
		else {
		RenderMeshCamera(meshes["sphere"], shaders["BallShader"], modelMatrix);

		}
	}
}

void Tema2::RenderCombustible(float deltaTimeSeconds)
{
	if (!gameOver && !speedRun)
	{
		combustibleScale -= (playerSpeed + 1.0) * deltaTimeSeconds * 0.002;
	}

	// no combustible -> end game
	if (combustibleScale <= 0)
	{
		gameOver = true;
		lives--;
	}

	float x = -3.6f - 0.30f + combustibleScale;

	// green
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 4.3, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(combustibleScale, 0.05f, 0));
	RenderSimpleMesh(meshes["quad"], shaders["PlatformShader"], modelMatrix, glm::vec3(0, 1, 0), userCamera, projectionMatrix1);

	// white
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.6, 4.3, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.30f, 0.05f, 0));
	RenderSimpleMesh(meshes["quad"], shaders["PlatformShader"], modelMatrix, glm::vec3(1, 1, 1), userCamera, projectionMatrix1);
}

void Tema2::RenderLives()
{
	float x = -3.85;
	for (int i = 0; i < lives; i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x + i * 0.17f / 2.0, 4.12, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f, 0.17f, 0));
		RenderSimpleMesh(meshes["heart"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 0, 0), userCamera, projectionMatrix1);
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (lives != 0) {
		if (!gameOver)
		{
			// first camera person or third camera person
			SetCameraType();

			// render platforms and check for collision
			collisionBallPlatform = false;
			InitialScene(deltaTimeSeconds, firstColumnX, initialColumn1, initialColumn1.size());
			InitialScene(deltaTimeSeconds, secondColumnX, initialColumn2, initialColumn2.size());
			InitialScene(deltaTimeSeconds, thirdColumnX, initialColumn3, initialColumn3.size());

			// move the ball
			MoveBall(deltaTimeSeconds);

			// get delta time - if the ball lands on the orange platform it starts the speed run
			if (speedRun)
			{
				end_time = time(NULL);
				// check if the delta time has passed
				if ((end_time - start_time) >= deltatime)
				{
					speedRun = false;
					playerSpeed = initialSpeed;
				}
			}
		}
		// the game is over
		else
		{
			SetInitialValues();
			initialColumn1.clear();
			initialColumn2.clear();
			initialColumn3.clear();
			SetInitialScene();
			gameOver = false;
		}

		// display the ball
		RenderBall(deltaTimeSeconds);

		// display the combustible
		RenderCombustible(deltaTimeSeconds);

		// display lives
		RenderLives();
	}
	else {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

// the platforms & the combustible
void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color, TemaCamera::Camera *camera, glm::mat4 projectionMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint material = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(material, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// the ball
void Tema2::RenderMeshCamera(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (!downBall)
	{
		// the player's movements
		if (window->KeyHold(GLFW_KEY_W) && !speedRun)
		{
			// increase the player's speed
			if (playerSpeed < 5)
			{
				playerSpeed += deltaTime * 1.75;
			}
		}

		if (window->KeyHold(GLFW_KEY_S) && !speedRun)
		{
			// decreases the player's speed
			if (playerSpeed > 0)
			{
				playerSpeed -= deltaTime * 1.75;
			}
		}

		if (window->KeyHold(GLFW_KEY_A) && translateXPlayer > -1.7f)
		{
			// move left
			translateXPlayer -= deltaTime * 1.5;
		}

		if (window->KeyHold(GLFW_KEY_D) && translateXPlayer < 1.7f)
		{
			// move right
			translateXPlayer += deltaTime * 1.5;
		}

		if (window->KeyHold(GLFW_KEY_SPACE))
		{
			// jump
			if (translateYPlayer < maximPosition && goBack == true)
			{
				jump = true;
				translateYPlayer += deltaTime * 2.0;
			}
			else
			{
				jump = false;
				goBack = false;
			}
		}
	}
	/*
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}
	}
	*/
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_C)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	if (key == GLFW_KEY_R && lives == 0)
	{
		lives = 3;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_SPACE)
	{
		// jump
		jump = false;
		goBack = false;
	}
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		rotate = true;
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (!renderCameraTarget)
		{
			// rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
		}

		if (renderCameraTarget)
		{
			// rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event

	rotate = false;
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
