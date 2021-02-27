#pragma once

#include <Component/SimpleScene.h>
#include <iterator>
#include <vector>
#include <map>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:

	void CreateObjects();
	void CreateGameOver();
	void RenderBalloon(float leftCornerX, float translateY, std::string polyline, std::string triangle, std::string circle);
	void RenderShuriken(float leftCornerY, float deltaTimeSeconds, float translateX);
	void RenderBow(float leftCornerX, float leftCornerY, float translateY, float deltaTimeSeconds);
	void ThroughArrow(float x_value, float y_value, float deltaTimeSeconds);
	void RenderPowerBar(float deltaTimeSeconds);
	void RenderLives();
	void RenderGameOver(float deltaTimeSeconds);
	void Shurikens(float deltaTimeSeconds);
	void Ballons(float deltaTimeSeconds);
	void Tema1::RenderScoreBar(float deltaTimeSeconds);

	void FatalCollision(float leftCornerYShuriken, float translateXShuriken, float leftCornerXBow, float leftCornerYBow, float translateYBow);
	bool CollisionArrowShuriken(float leftCornerYShuriken, float translateXShuriken, float x_value, float y_value, int id);
	bool CollisionArrowBalloon(float leftCornerxBallon, float translateYBalloon, float x_value, float y_value);
	void RenderBalloonDown(float leftCornerX, float translateY, std::string polyline, std::string triangle, std::string circle);

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
	glm::mat3 modelMatrix;
	glm::ivec2 resolution;
	GLint64 start_time, end_time;
	float pressed_time; // count the time

	std::map<float, float> balloonPairs; // key: x_translate(final) value: y_translate
	std::map<float, float> balloonScale; // key: x_translate(final) value: scale_factor
	std::map<float, bool> balloonDown; // key: x_translate(final) value: y_translate
	std::map<float, float> shurikenPairs; // key: y_translate(final) value: isCollision?
	std::map<float, float> shurikenCollision; // key: y_translate(final) value: y_translate
	std::map<float, bool> shurikenDown; // key: y_translate(final) value: isCollision?

	float translateX, translateY; // for bow & arrow movement
	float x_value, y_value; // for arrow translation (initial positions)
	float translateXArrow, translateYArrow; // for arrow translation

	float tooBig; // game over animation
	float scaleX, scaleY; // game over animation
	float scaleScore = 1;
	float scaleBalloon;

	float angularStep; // shuriken rotation
	float angleBow, angleArrow; // bow & arrow rotation

	float mousePosX, mousePosY; // mouse position - press
	float mouseReleaseX, mouseReleaseY; // mouse position - release
	int dead = 3; // counter for lives
	float power; // powerbar

	float shurikenLength; // shuriken side
	float arrowLine; 
	float arrowSide;

	bool mouseRelease = false;
	bool finally = true; // the arrow left the scene?
	bool press = false;
	bool gameOver = false;
	bool collisionShurikenBow = false;
	bool restart = false; // for restarting the game, when it's over
};
