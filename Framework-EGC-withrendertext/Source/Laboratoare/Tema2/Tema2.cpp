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

void Tema2::LoadTextures() 
{
	// Load textures
	const string textureLoc = "Source/Laboratoare/Tema2/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass5.jpg").c_str(), GL_REPEAT);
		mapTextures["ground"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wall_grass.jpg").c_str(), GL_REPEAT);
		mapTextures["wall"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wall_top.jpg").c_str(), GL_REPEAT);
		mapTextures["wall_top"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "metal_floor.jpg").c_str(), GL_REPEAT);
		mapTextures["platform"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "death.jpg").c_str(), GL_REPEAT);
		mapTextures["platform_death"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "ice.jpg").c_str(), GL_REPEAT);
		mapTextures["platform_speedrun"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "lava.jpg").c_str(), GL_REPEAT);
		mapTextures["platform_loseLife"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "heart.jpg").c_str(), GL_REPEAT);
		mapTextures["platform_gainLife"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "speedrun.jpg").c_str(), GL_REPEAT);
		mapTextures["platform_gainComb"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "Tileable5f.png").c_str(), GL_REPEAT);
		mapTextures["platform_loseComb"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "barrier.jpg").c_str(), GL_REPEAT);
		mapTextures["barrier"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "bitcoin.jpg").c_str(), GL_REPEAT);
		mapTextures["coin"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wall_grass1.jpg").c_str(), GL_REPEAT);
		mapTextures["sky"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "fractal4.jpg").c_str(), GL_REPEAT);
		mapTextures["ball"] = texture;
	}
}

void Tema2::LoadObjects()
{
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("quad");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Tema2::CreateHeart()
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

void Tema2::CreateCube()
{
	vector<glm::vec3> vertices{
		/*This is the bottom face*/
		glm::vec3(1, 0, 0), //0
		glm::vec3(1, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 0),

		//top face
		glm::vec3(1, 1, 0), //6
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 1),
		glm::vec3(1, 1, 0),
		glm::vec3(0, 1, 1),
		glm::vec3(1, 1, 1),

		//right face
		glm::vec3(1, 0, 0), //0
		glm::vec3(1, 1, 0), //9
		glm::vec3(1, 1, 1), //11
		glm::vec3(1, 0, 0), //0
		glm::vec3(1, 1, 1), //11
		glm::vec3(1, 0, 1),

		//front face
		glm::vec3(1, 0, 1), // 1
		glm::vec3(1, 1, 1), // 11
		glm::vec3(0, 1, 1), // 10
		glm::vec3(1, 0, 1),
		glm::vec3(0, 1, 1),
		glm::vec3(0, 0, 1),

		//left face
		glm::vec3(0, 0, 1),
		glm::vec3(0, 1, 1),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 0),

		//back face
		glm::vec3(1, 1, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(1, 1, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)

	};

	vector<glm::vec3> normals{
		/*This is the bottom face*/
		glm::vec3(0.5, 0, 0.5),

		//top face
		glm::vec3(0.0f, 1.0f, 0.0f),

		//right face
		glm::vec3(1.0f, 0.0f, 0.0f),

		//front face
		glm::vec3(0.0f, 0.0f, 1.0f),

		//left face
		glm::vec3(-1.0f, 0.0f, 0.0f),

		//back face
		glm::vec3(0.0f, 0.0f, -1.0f) };

	// texture coordinates for the square
	vector<glm::vec2> textureCoords{
		// bottom face
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),

		//top face
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f), // pana aici e verificat

		// right face
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),

		// front face
		glm::vec2(1.0f, 0.0f), //verificat
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),

		// left face
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),

		// bottom face
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f) };

	vector<unsigned short> indices =
	{
		0, 1, 2,
		3, 4, 5,

		6, 7, 8,
		9, 10, 11,

		12, 13, 14,
		15, 16, 17,

		18, 19, 20,
		21, 22, 23,

		24, 25, 26,
		27, 28, 29,

		30, 31, 32,
		33, 34, 35 };

	// Create a new mesh from buffer data
	//Mesh* cubec = CreateMesh(name, vertices, indices);
	Mesh* mesh = new Mesh("cubec");
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	meshes[mesh->GetMeshID()] = mesh;
}

void Tema2::CreateQuads()
{
	// Create a simple quad vertical
	{
		vector<glm::vec3> vertices{
			glm::vec3(0.5f, 0.5f, 0.0f),   // Top Right
			glm::vec3(0.5f, -0.5f, 0.0f),  // Bottom Right
			glm::vec3(-0.5f, -0.5f, 0.0f), // Bottom Left
			glm::vec3(-0.5f, 0.5f, 0.0f),  // Top Left
		};

		vector<glm::vec3> normals{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0) };

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords{
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f) };

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3 };

		Mesh* mesh = new Mesh("squareVert");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple quad
	{
		vector<glm::vec3> vertices{
			glm::vec3(0.5f, 0.0f, 0.5f),   // Top Right
			glm::vec3(0.5f, 0.0f, -0.5f),  // Bottom Right
			glm::vec3(-0.5f, 0.0f, -0.5f), // Bottom Left
			glm::vec3(-0.5f, 0.0f, 0.5f),  // Top Left
		};

		vector<glm::vec3> normals{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0) };

		// Complete texture coordinates for the square
		vector<glm::vec2> textureCoords{
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f) };

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3 };

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Tema2::SetInitialWalls()
{
	wallsLeft.clear();
	wallsRight.clear();
	scaleWallX = 1.0f;
	scaleWallY = 2.0f;
	scaleWallZ = 1.5f;
	posWallXleft = -3.0f;
	posWallXright = 2.0f;
	posWallY = -0.4f;
	posWallZ = 0.0f;
	level = -30.0f;

	while (posWallZ > level)
	{
		wallsLeft.push_back({ posWallXleft, posWallZ });
		wallsRight.push_back({ posWallXright, posWallZ });
		posWallZ -= scaleWallZ;
	}

	// top
	wallsTopLeft.clear();
	wallsTopRight.clear();
	posWallTopY = posWallY + scaleWallY;
	posWallTopZ = 0.0f;

	while (posWallTopZ > level)
	{
		wallsTopLeft.push_back({ posWallXleft, posWallTopZ });
		wallsTopRight.push_back({ posWallXright, posWallTopZ });
		posWallTopZ -= scaleWallZ;
	}
}

void Tema2::SetInitialScene()
{
	float z = -1.0f;
	float scaleZ = 4.0f;

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

	z -= scaleZ - 2.0f;
	initialColumn2.push_back(make_tuple(z, scaleZ, black));

	z -= scaleZ - 2.0f;
	initialColumn1.push_back(make_tuple(z, scaleZ, blue));
	initialColumn3.push_back(make_tuple(z, scaleZ, white));

	z -= scaleZ - 2.0f;
	initialColumn2.push_back(make_tuple(z, scaleZ, blue));

	// different numbers
	//std::srand(time(NULL));

	// first column
	int currentZ = z - scaleZ;
	int chooseColor = 0;
	while (currentZ > -30.0f)
	{
		// generate a random distance between platform
		currentZ -= randomNumber(1.0, 3.0);
		scaleZ = randomNumber(3.5, 4.5);
		if (chooseColor % 3 || chooseColor % 5)
		{
			initialColumn1.push_back(make_tuple(currentZ, scaleZ, black));
		}
		else
		{
			initialColumn1.push_back(make_tuple(currentZ, scaleZ, blue));
		}
		initialColumn1.push_back(make_tuple(currentZ - scaleZ, scaleZ, blue));
		currentZ -= scaleZ * 2 + randomNumber(1.0, 1.8) + randomNumber(1.0, 1.7);
		chooseColor++;
	}

	// second column
	currentZ = z - scaleZ;
	while (currentZ > -30.0f)
	{
		// generate a random distance between platform
		currentZ -= randomNumber(1.0, 3.0);
		scaleZ = randomNumber(3.5, 4.5);
		if (chooseColor % 4 || chooseColor % 7)
		{
			initialColumn2.push_back(make_tuple(currentZ, scaleZ, black));
		}
		else
		{
			initialColumn2.push_back(make_tuple(currentZ, scaleZ, blue));
		}
		initialColumn2.push_back(make_tuple(currentZ - scaleZ, scaleZ, blue));
		currentZ -= scaleZ * 2 + randomNumber(1, 1.8) + randomNumber(1.0, 1.7);
		chooseColor++;
	}

	// third column
	currentZ = z - scaleZ;
	while (currentZ > -30.0f)
	{
		// generate a random distance between platform
		currentZ -= randomNumber(1.0, 3.0);
		scaleZ = randomNumber(3.5, 4.5);
		if (chooseColor % 2)
		{
			initialColumn3.push_back(make_tuple(currentZ, scaleZ, white));
		}
		else
		{
			initialColumn3.push_back(make_tuple(currentZ, scaleZ, blue));
		}
		initialColumn3.push_back(make_tuple(currentZ - scaleZ, scaleZ, blue));
		currentZ -= scaleZ * 2 + randomNumber(1.0, 2.0);
		chooseColor++;
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

	// initial Scene5
	SetInitialScene();
	SetInitialWalls();

	// set Z distance (where the platforms start to appear)
	distanceZ = -20.0f;

	translateXPlayer = 0;
	translateYPlayer = 0.3f;
	playerSpeed = 0;
	maximPosition = 1.5f;
	deltatime = 5.0;

	combustibleScale = 0.30f;
	scaleBall = 1;

	coinAngle = 0;

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

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	LoadObjects();
	LoadTextures();
	CreateHeart();

	// create textured cube
	CreateCube();

	// create quads 
	CreateQuads();	

	// Create a shader program for drawing face polygon with the color of the normal for the platforms
	{
		Shader* shader = new Shader("PlatformShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create a shader program for drawing face polygon with the color of the normal for the ball
	{
		Shader* shaderBall = new Shader("BallShader");
		shaderBall->AddShader("Source/Laboratoare/Tema2/ShadersBall/VertexShader.glsl", GL_VERTEX_SHADER);
		shaderBall->AddShader("Source/Laboratoare/Tema2/ShadersBall/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shaderBall->CreateAndLink();
		shaders[shaderBall->GetName()] = shaderBall;
	}

	// Create a shader program for drawing face polygon with texture
	{
		Shader* shaderTex = new Shader("TexturedShader");
		shaderTex->AddShader("Source/Laboratoare/Tema2/ShadersTextured/VertexShader.glsl", GL_VERTEX_SHADER);
		shaderTex->AddShader("Source/Laboratoare/Tema2/ShadersTextured/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shaderTex->CreateAndLink();
		shaders[shaderTex->GetName()] = shaderTex;
	}

	// Text renderer
	glm::ivec2 resolution = window->GetResolution();
	Text = new TextRenderer(resolution.x, resolution.y);

	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 60);
}

void Tema2::drawHud(std::string text)
{
	glm::vec3 colorText = glm::vec3(0.3, 0.3, 0.3);
	Text->RenderText(text, 1150.0f, 20, 1.0f, colorText);
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.4, 0.9, 1, 1);
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
	colors.push_back(white); // power-ups
	colors.push_back(black); // obstacle
	int nrColors = 9;

	// frequency of platforms
	int freq[] = { 250, 5, 15, 10, 15, 15, 15, 50, 50 };

	// use a different seed value for every run.
	//std::srand(NULL);

	int prefix[10], i;
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

// collision between two sphere
bool Tema2::Collision2Sphere(float sphereX, float sphereY, float sphereZ, float pointX, float pointY, float pointZ, float sphereRadius, float pointRadius)
{
	float distance = std::sqrt((pointX - sphereX) * (pointX - sphereX) +
		(pointY - sphereY) * (pointY - sphereY) +
		(pointZ - sphereZ) * (pointZ - sphereZ));

	if (distance < (sphereRadius + pointRadius))
	{
		return true;
	}

	return false;
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

void Tema2::InitialScene(float deltaTimeSeconds, float column, std::vector<tuple<float, float, glm::vec3>>& initialColumn, int n)
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
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.9f, 0.05f, std::get<1>(initialColumn[i])));

			// check collision between the ball and each platform
			CheckCollision(deltaTimeSeconds, column, initialColumn, i, modelMatrix, std::get<0>(initialColumn[i]));
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
				float scaleZ = randomNumber(3.0f, 4.5f);
				initialColumn.push_back({ distanceZ - 4.0f, scaleZ, currentColor });
			}
			else
			{
				float scaleZ = randomNumber(3.0f, 4.0f);
				initialColumn.push_back({ distanceZ - 4.5f, scaleZ, currentColor });
			}
		}
	}
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
		if (!speedRun)
		{
			RenderMeshCamera(meshes["sphere"], shaders["TexturedShader"], modelMatrix, mapTextures["ball"], projectionMatrix);
		}
		// render the deformed ball, if the ball lands on the orange platform
		else
		{
			RenderMeshCamera(meshes["sphere"], shaders["BallShader"], modelMatrix, mapTextures["ball"], projectionMatrix);
		}
	}
}

void Tema2::RenderCombustible(float deltaTimeSeconds)
{
	if (!gameOver && !speedRun)
	{
		combustibleScale -= playerSpeed * deltaTimeSeconds * 0.002;
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
	for (int i = 0; i < lives; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x + i * 0.17f / 2.0, 4.12, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.17f, 0.17f, 0));
		RenderSimpleMesh(meshes["heart"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 0, 0), userCamera, projectionMatrix1);
	}
}

// render the decorative elements
void Tema2::RenderWalls(std::vector<std::pair<float, float>>& walls, std::vector<std::pair<float, float>>& wallsTop, float deltaTimeSeconds)
{
	// the ground
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -scaleWallY, -5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 0, 10));
		RenderTexturedMesh(meshes["square"], shaders["TexturedShader"], modelMatrix, mapTextures["ground"], camera, projectionMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -scaleWallY, -15));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 0, 10));
		RenderTexturedMesh(meshes["square"], shaders["TexturedShader"], modelMatrix, mapTextures["ground"], camera, projectionMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -scaleWallY, -25));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 0, 10));
		RenderTexturedMesh(meshes["square"], shaders["TexturedShader"], modelMatrix, mapTextures["ground"], camera, projectionMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -scaleWallY, -35));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 0, 10));
		RenderTexturedMesh(meshes["square"], shaders["TexturedShader"], modelMatrix, mapTextures["ground"], camera, projectionMatrix);
	}

	// the sky
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -scaleWallY + 2.0f, -23.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(4, scaleWallY * 2, 0));
		RenderTexturedMesh(meshes["squareVert"], shaders["TexturedShader"], modelMatrix, mapTextures["sky"], camera, projectionMatrix);
	}

	// the walls
	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].second += deltaTimeSeconds * playerSpeed;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(walls[i].first, posWallY, walls[i].second));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleWallX, scaleWallY, scaleWallZ));
		RenderTexturedMesh(meshes["cubec"], shaders["TexturedShader"], modelMatrix, mapTextures["wall"], camera, projectionMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(walls[i].first, posWallY - scaleWallY, walls[i].second));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleWallX, scaleWallY, scaleWallZ));
		RenderTexturedMesh(meshes["cubec"], shaders["TexturedShader"], modelMatrix, mapTextures["wall"], camera, projectionMatrix);

		if (walls[i].second > 5)
		{
			walls.erase(walls.begin() + i);
			walls.push_back({ walls[i + 1].first, distanceZ - 5 });
		}
	}

	for (int i = 0; i < wallsTop.size(); i++)
	{
		wallsTop[i].second += deltaTimeSeconds * playerSpeed;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(wallsTop[i].first, posWallTopY, wallsTop[i].second));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleWallX, scaleWallY / 4.0, scaleWallZ / 4.0));
		RenderTexturedMesh(meshes["cubec"], shaders["TexturedShader"], modelMatrix, mapTextures["wall_top"], camera, projectionMatrix);

		if (wallsTop[i].second > 5)
		{
			wallsTop.erase(wallsTop.begin() + i);
			wallsTop.push_back({ wallsTop[i + 1].first, distanceZ - 5 });
		}
	}
}

void Tema2::RenderObstacle(float column, float posZ)
{
	float posY = 0.05f + platformY;
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(column, platformY + 0.2f, posZ));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 0.4f, 0.2f));

	// check collision between ball and current obstacle
	float radius = 0.15f;
	float cubeXmin = column - 0.35f;
	float cubeXmax = column + 0.35f;
	float cubeYmin = platformY + 0.05f;
	float cubeYmax = platformY + 0.05f + 0.4f;
	float cubeZmin = posZ - -0.2f;
	float cubeZmax = posZ + 0.2f;

	// check if it is collision between the ball and the obstacle
	if (Collision(translateXPlayer, translateYPlayer, 0, cubeXmin, cubeYmin, cubeZmin,
		cubeXmax, cubeYmax, cubeZmax, radius) &&
		!downBall)
	{
		// - one life
		lives--;
		gameOver = true;
		collisionBarrier = true;
	}

	// render
	RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["barrier"], camera, projectionMatrix);
}

void Tema2::RenderBonus(float column, float posZ, float deltaTimeSeconds, std::vector<tuple<float, float, glm::vec3>>& initialColumn, int index)
{
	float posY = platformY + 0.05f + 2.0f;

	// used for rotation
	coinAngle = coinAngle + deltaTimeSeconds * 1.0f;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(column, platformY + 0.50f, posZ));
	modelMatrix = glm::rotate(modelMatrix, coinAngle, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.30f, 0.50f, 0.05f));

	float radiusBall = 0.15f;
	float radiusCoin = 0.25f;
	float xCoin = column;
	float yCoin = platformY + 0.50f;
	float zCoin = posZ;

	// collision
	if (Collision2Sphere(translateXPlayer, translateYPlayer, 0, xCoin, yCoin, zCoin, radiusBall, radiusCoin))
	{
		// change the color of the platform
		std::get<2>(initialColumn[index]) = blue;

		// +1 score
		score++;
	}
	else
	{
		// render
		RenderTexturedMesh(meshes["sphere"], shaders["TexturedShader"], modelMatrix, mapTextures["coin"], camera, projectionMatrix);
	}
}

void Tema2::CheckCollision(float deltaTimeSeconds, float column, std::vector<tuple<float, float, glm::vec3>>& initialColumn, int i, glm::mat4 modelMatrix, float posZPlatform)
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
		cubeXmax, cubeYmax, cubeZmax, radius) &&
		!downBall)
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
		else if (colorCollision == pink && lives < 7)
		{
			// + one life
			lives++;
		}
		else if (colorCollision == gray)
		{
			// - one life
			lives--;
			if (lives == 0)
			{
				gameOver = true;
			}
		}
		glm::vec3 color = std::get<2>(initialColumn[i]);
		// for collision -> violet
		if (color != black && color != white)
		{
			std::get<2>(initialColumn[i]) = glm::vec3(0.5, 0, 1);
		}
		collisionBallPlatform = true;
	}
	// render the platforms
	glm::vec3 color = std::get<2>(initialColumn[i]);
	if (color == blue || color == violet)
	{ // normal platform
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform"], camera, projectionMatrix);
	}
	else if (color == red)
	{ // loose a life
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform_death"], camera, projectionMatrix);
	}
	else if (color == orange)
	{ // speed run
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform_speedrun"], camera, projectionMatrix);
	}
	else if (color == black)
	{ // obstacle
		RenderObstacle(column, posZPlatform);
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform"], camera, projectionMatrix);
	}
	else if (color == white)
	{ // power up
		RenderBonus(column, posZPlatform, deltaTimeSeconds, initialColumn, i);
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform"], camera, projectionMatrix);
	}
	else if (color == gray)
	{ // lose a life
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform_loseLife"], camera, projectionMatrix);
	}
	else if (color == pink)
	{ // gain a life
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform_gainLife"], camera, projectionMatrix);
	}
	else if (color == green)
	{ // gain some comb
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform_gainComb"], camera, projectionMatrix);
	}
	else if (color == yellow)
	{ // lose some comb
		RenderTexturedMesh(meshes["box"], shaders["TexturedShader"], modelMatrix, mapTextures["platform_loseComb"], camera, projectionMatrix);
	}
	else
	{
		RenderSimpleMesh(meshes["box"], shaders["PlatformShader"], modelMatrix, std::get<2>(initialColumn[i]), camera, projectionMatrix);
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (lives != 0)
	{
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

			// render the walls & the ground
			RenderWalls(wallsLeft, wallsTopLeft, deltaTimeSeconds);
			RenderWalls(wallsRight, wallsTopRight, deltaTimeSeconds);
		}
		// the game is over
		else
		{
			SetInitialValues();
			initialColumn1.clear();
			initialColumn2.clear();
			initialColumn3.clear();
			SetInitialScene();
			SetInitialWalls();
			gameOver = false;
		}

		// display the ball
		RenderBall(deltaTimeSeconds);

		// display the combustible
		RenderCombustible(deltaTimeSeconds);

		// display lives
		RenderLives();
	}
	else
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		score = 0;
	}
}

void Tema2::FrameEnd()
{
	std::string currentScore = "";
	if (score < 10 && score != 0)
	{
		currentScore += "0";
	}
	currentScore += to_string(score);

	// display the score
	drawHud(currentScore);

	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

// the textured meshes
void Tema2::RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, TemaCamera::Camera* camera, glm::mat4 projectionMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int loc_time = glGetUniformLocation(shader->program, "time");

	int loc_mix = glGetUniformLocation(shader->program, "mixer");
	glUniform1i(loc_mix, mix);

	if (texture1)
	{
		// activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		// bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		// send texture uniform value
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
	}

	// draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// the lives & the combustible
void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, TemaCamera::Camera* camera, glm::mat4 projectionMatrix)
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
void Tema2::RenderMeshCamera(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, glm::mat4 projectionMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	if (texture1)
	{
		// Activate texture location 0
		// Bind the texture1 ID
		//Send texture uniform value
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

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
				playerSpeed += deltaTime * 0.75;
			}
		}

		if (window->KeyHold(GLFW_KEY_S) && !speedRun)
		{
			// decreases the player's speed
			if (playerSpeed > 0)
			{
				playerSpeed -= deltaTime * 0.75;
			}
		}

		if (window->KeyHold(GLFW_KEY_A) && translateXPlayer > -1.7f)
		{
			// move left
			translateXPlayer -= deltaTime * 0.75;
		}

		if (window->KeyHold(GLFW_KEY_D) && translateXPlayer < 1.7f)
		{
			// move right
			translateXPlayer += deltaTime * 0.75;
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

		if (window->KeyHold(GLFW_KEY_W))
		{
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S))
		{
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q))
		{
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E))
		{
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
