#pragma once
#include <Component/SimpleScene.h>
#include <stdio.h>
#include <time.h>
#include "TemaCamera.h"

using namespace std;

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;
	// create the initial scene: the first platforms
	void InitialScene(float deltaTimeSeconds, float column, std::vector <tuple <float, float, glm::vec3>>& initialColumn, int n);
	// generate a random number
	float randomNumber(float low, float high);
	void SetInitialValues();
	void SetInitialScene();
	// generate a random color for the platform
	glm::vec3 GenerateARandomPlatform();
	void MoveBall(float deltaTimeSeconds);
	void RenderBall(float deltaTimeSeconds);
	void SetCameraType();
	void RenderCombustible(float deltaTimeSeconds);
	void RenderLives();
	// check collision between a sphere and a cube
	bool Collision(float sphereX, float sphereY, float sphereZ, float cubeXmin, float cubeYmin, float cubeZmin, float cubeXmax, float cubeYmax, float cubeZmax, float sphereRadius);
	// check collision between the ball and the platforms
	void CheckCollision(float deltaTimeSeconds, float column, std::vector <tuple <float, float, glm::vec3>>& initialColumn, int i, glm::mat4 modelMatrix);
	// function used to render the ball
	void RenderMeshCamera(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	// function used to render the platforms & the combustible bar
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, TemaCamera::Camera* camera, glm::mat4 projectionMatrix);

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	TemaCamera::Camera* camera;
	TemaCamera::Camera* userCamera;
	glm::mat4 projectionMatrix, projectionMatrix1;
	bool renderCameraTarget;
	bool projectionType;

	float scaleZPlatform;
	float platformY;
	float firstColumnX, secondColumnX, thirdColumnX;
	float distanceZ;

	float translateYPlayer, translateXPlayer;
	float maximPosition, minimPosition;
	float playerSpeed;
	float initialSpeed;
	int lives = 3;

	bool jump = false;
	bool goBack = true;
	bool rotate = false;
	bool collisionBallPlatform = false;
	bool downBall = false;
	bool gameOver = false;
	bool speedRun = false;

	float combustibleScale = 1;
	float scaleBall = 1;

	time_t start_time, end_time, deltatime;

	// the initial positions of the platforms -> tuple {z, scaleZ, color}
	std::vector <std::tuple <float, float, glm::vec3>> initialColumn1, initialColumn2, initialColumn3;
	int nInitialScene;

	// colors
	glm::vec3 blue = glm::vec3(0, 0.4, 1);
	glm::vec3 red = glm::vec3(1, 0.1, 0.1);
	glm::vec3 yellow = glm::vec3(1, 1, 0.1);
	glm::vec3 orange = glm::vec3(1, 0.5, 0);
	glm::vec3 green = glm::vec3(0.1, 0.8, 0);
	glm::vec3 pink = glm::vec3(1, 0.5, 1);
	glm::vec3 gray = glm::vec3(0.3, 0.3, 0.3);
};
