#include "Tema1.h"

#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include "glm/gtx/string_cast.hpp"
#include "Transform.h"
#include "Object.h"
#include "GameOver.h"

#include <Core/Engine.h>

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::CreateObjects()
{
    glm::vec3 corner = glm::vec3(0, 0, 0);

    // create arrow
    arrowLine = 50;
    arrowSide = 10;
    Mesh* arrow = Object::CreateArrow("bow", corner, arrowLine, arrowSide, glm::vec3(0, 0, 1));
    AddMeshToList(arrow);

    // create player
    float segments = 360;
    Mesh* player = Object::CreatePlayer("player", corner, segments, glm::vec3(0, 0, 1));
    AddMeshToList(player);

    // create shuriken
    shurikenLength = 50;
    Mesh* shuriken = Object::CreateShuriken("shuriken", corner, shurikenLength, glm::vec3(1, 0, 1));
    AddMeshToList(shuriken);

    // create polyline
    float polylineSide = 25;
    Mesh* polylineR = Object::CreatePolyline("polylineRed", corner, polylineSide, glm::vec3(1, 0, 0));
    AddMeshToList(polylineR);

    Mesh* polylineY = Object::CreatePolyline("polylineYellow", corner, polylineSide, glm::vec3(1, 1, 0));
    AddMeshToList(polylineY);

    // create triangle
    float triangleSide = polylineSide / 2.0;
    Mesh* triangleR = Object::CreateTriangle("triangleRed", corner, triangleSide, glm::vec3(1, 0, 0));
    AddMeshToList(triangleR);

    Mesh* triangleY = Object::CreateTriangle("triangleYellow", corner, triangleSide, glm::vec3(1, 1, 0));
    AddMeshToList(triangleY);

    // create circle
    float triangles = 360;
    Mesh* circleR = Object::CreateCircle("circleRed", corner, triangles, glm::vec3(1, 0, 0));
    AddMeshToList(circleR);

    Mesh* circleY = Object::CreateCircle("circleYellow", corner, triangles, glm::vec3(1, 1, 0));
    AddMeshToList(circleY);

    // create powerbar
    float length = 100;
    float width = 40;
    Mesh* powerbar = Object::CreateRectangle("powerbar", corner, length, width, glm::vec3(0, 1, 0));
    AddMeshToList(powerbar);

    // create scorebar
    length = 5;
    Mesh* score = Object::CreateRectangle("scorebar", corner, length, width, glm::vec3(0, 1, 1));
    AddMeshToList(score);

    // create lives
    // side1/side2 = 4
    float side1 = 36;
    float side2 = 9;
    Mesh* life1 = Object::CreateHeart("life1", corner, side1, side2, glm::vec3(1, 0, 0));
    AddMeshToList(life1);

    Mesh* life2 = Object::CreateHeart("life2", corner, side1, side2, glm::vec3(1, 0, 0));
    AddMeshToList(life2);

    Mesh* life3 = Object::CreateHeart("life3", corner, side1, side2, glm::vec3(1, 0, 0));
    AddMeshToList(life3);
}

void Tema1::CreateGameOver()
{
    glm::vec3 corner = glm::vec3(0, 0, 0);
    Mesh* g = GameOver::G("g", corner, glm::vec3(1, 0, 1));
    AddMeshToList(g);

    Mesh* a = GameOver::A("a", corner, glm::vec3(1, 0, 1));
    AddMeshToList(a);

    Mesh* m = GameOver::M("m", corner, glm::vec3(1, 0, 1));
    AddMeshToList(m);

    Mesh* e = GameOver::E("e", corner, glm::vec3(1, 0, 1));
    AddMeshToList(e);

    Mesh* o = GameOver::O("o", corner, glm::vec3(1, 0, 1));
    AddMeshToList(o);

    Mesh* v = GameOver::V("v", corner, glm::vec3(1, 0, 1));
    AddMeshToList(v);

    Mesh* r = GameOver::R("r", corner, glm::vec3(1, 0, 1));
    AddMeshToList(r);
}

void Tema1::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // initialize the global variables

    // pair: translateYShuriken - translateXShuriken
    shurikenPairs.insert(pair<float, float>(145, ((float)resolution.x * 1.25)));
    shurikenPairs.insert(pair<float, float>(340, ((float)resolution.x * 1.75)));
    shurikenPairs.insert(pair<float, float>(530, ((float)resolution.x * 2.0)));

    shurikenDown.insert(pair<float, bool>(145, false));
    shurikenDown.insert(pair<float, bool>(340, false));
    shurikenDown.insert(pair<float, bool>(530, false));

    shurikenCollision.insert(pair<float, float>(145, 145));
    shurikenCollision.insert(pair<float, float>(340, 340));
    shurikenCollision.insert(pair<float, float>(530, 530));

    // pair: Xballoon - translateYBalloon
    for (int i = 5; i <= 16; i++)
    {
        float x = i * 75.0;
        int randomFactor = rand() % 10 + 2;
        float y = -100.0 * randomFactor;
        balloonPairs.insert(pair<float, float>(x, y));
    }
    //map<float, float>::iterator itr;
    for (map<float, float>::iterator itr = balloonPairs.begin(); itr != balloonPairs.end(); ++itr)
    {
        // pair: XBalllon - downBalloon
        balloonDown.insert(pair<float, bool>(itr->first, false));
        // pair: XBalllon - scaleBalloon
        balloonScale.insert(pair<float, bool>(itr->first, 1));
    }

    // for the arrow & bow movement
    translateX = 0;
    translateY = 0;

    // initialize the scale factors
    scaleX = 1; // gameOver
    scaleY = 1; // gameOver
    scaleBalloon = 1;

    // initialize angularStep(Shuriken rotation)
    angularStep = 0;
    // initialize angleBow
    angleBow = 0;

    power = 0;
    tooBig = 0;

    // create the objects
    CreateObjects();
    CreateGameOver();
}

void Tema1::FrameStart()
{
    // clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::RenderBalloon(float leftCornerX, float translateY, std::string polyline,
    std::string triangle, std::string circle)
{
    float polylineSide = 25;
    float triangleY = 1.70 * polylineSide + translateY;
    float circleY = triangleY + 45;  // scaleY + h_triangle
    float circleX = leftCornerX + 5; // scaleX - side_triangle

    // polyline
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(leftCornerX, translateY);
    RenderMesh2D(meshes[polyline], shaders["VertexColor"], modelMatrix);

    // triangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(leftCornerX, triangleY);
    RenderMesh2D(meshes[triangle], shaders["VertexColor"], modelMatrix);

    // circle
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(circleX, circleY);
    modelMatrix *= Transform::Scale(20, 40);
    RenderMesh2D(meshes[circle], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderShuriken(float leftCornerY, float deltaTimeSeconds, float translateX)
{
    glm::vec3 corner = glm::vec3(0, 0, 0);
    float shurikenLength = 50;

    // compute coordinates of square center
    float x = corner.x + shurikenLength / 2;
    float y = corner.y + shurikenLength / 2;

    // shuriken's translation
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(translateX, leftCornerY);

    // rotate
    angularStep = angularStep + deltaTimeSeconds * 3.0;

    modelMatrix *= Transform::Translate(x, y);
    modelMatrix *= Transform::Rotate(angularStep);
    modelMatrix *= Transform::Translate(-x, -y);

    RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderBow(float leftCornerX, float leftCornerY, float translateY, float deltaTimeSeconds)
{
    // look at the mouse x_x
    if (mousePosX > 150)
    {
        angleBow = -atan2(mousePosY - leftCornerY + translateY, mousePosX - leftCornerX);
    }

    // bow
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(leftCornerX, leftCornerY);
    modelMatrix *= Transform::Translate(leftCornerX - fabs(angleBow) * 18, translateY +
        angleBow * 75);
    modelMatrix *= Transform::Rotate(angleBow);
    RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

    // release
    if (mouseRelease && finally)
    {
        // arrow x and y positions
        x_value = modelMatrix[2][0];
        y_value = modelMatrix[2][1];

        // set to false to be able to throw another arrow in the scene
        finally = false;
        mouseRelease = false;
    }

    // player
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(leftCornerX - 25, leftCornerY);
    modelMatrix *= Transform::Translate(leftCornerX - 25, translateY);
    modelMatrix *= Transform::Scale(35, 80);
    modelMatrix *= Transform::Rotate(angleBow);
    glLineWidth(6);
    RenderMesh2D(meshes["player"], shaders["VertexColor"], modelMatrix);
}

void Tema1::ThroughArrow(float x_value, float y_value, float deltaTimeSeconds)
{
    // set acceleration
    float acc;
    if (pressed_time <= 0.5)
    {
        acc = 0.20;
    }
    else if (pressed_time >= 4.0)
    {
        acc = 2.0;
    }
    else
    {
        acc = pressed_time / 2;
    }

    modelMatrix = glm::mat3(1);

    float lengthArrow = 55;
    // the angle
    angleBow = atan2(mouseReleaseY - y_value, mouseReleaseX - x_value + lengthArrow);
    angleArrow = angleBow;

    // calculate the new translateY and translateX for Arrow
    if (mouseReleaseY <= (float)resolution.y / 2)
    {
        translateYArrow -= (-mouseReleaseY + y_value) * deltaTimeSeconds * acc;
        translateXArrow += (mouseReleaseX - x_value) * deltaTimeSeconds * acc;
    }
    else
    {
        translateYArrow += (mouseReleaseY - y_value) * deltaTimeSeconds * acc;
        translateXArrow += (mouseReleaseX - x_value) * deltaTimeSeconds * acc;
    }

    modelMatrix *= Transform::Translate(x_value, y_value);
    modelMatrix *= Transform::Translate(translateXArrow, translateYArrow);
    modelMatrix *= Transform::Rotate(angleBow);
    RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

    // check if the arrow is off the scene
    if ((modelMatrix[2][0] >= (float)resolution.x || modelMatrix[2][1] >= (float)resolution.y || modelMatrix[2][1] <= 0) && (!press))
    {
        // a new arrow can be thrown
        finally = true;
        pressed_time = 0;
        translateXArrow = -10000;
        translateYArrow = -10000;
    }
    else
    {
        press = false;
        finally = false;
    }
}

void Tema1::RenderPowerBar(float deltaTimeSeconds)
{
    // powerbar
    if (press)
    {
        if (power < 3)
        {
            power += 0.75 * deltaTimeSeconds;
        }

        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform::Translate(20, 20);
        // max power
        if (power < 20)
        {
            modelMatrix *= Transform::Scale(power, 1);
        }

        RenderMesh2D(meshes["powerbar"], shaders["VertexColor"], modelMatrix);

        if (!finally)
        {
            press = false;
            power = 0;
        }
    }
}

void Tema1::RenderLives()
{
    if (dead > 0)
    {
        // first life
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform::Translate(40, (float)resolution.y - 60);
        RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
    }

    if (dead > 1)
    {
        // second life
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform::Translate(90, (float)resolution.y - 60);
        RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
    }

    if (dead > 2)
    {
        //third live
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform::Translate(140, (float)resolution.y - 60);
        RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderGameOver(float deltaTimeSeconds)
{
    // big-small animation
    if ((scaleX < 2) && (tooBig == 0))
    {
        scaleX += deltaTimeSeconds * 0.5;
        scaleY += deltaTimeSeconds * 0.5;
    }
    else if (scaleX >= 2)
    {
        tooBig = 1;
        scaleX -= deltaTimeSeconds * 0.5;
        scaleY -= deltaTimeSeconds * 0.5;
    }
    else if (tooBig == 1)
    {
        scaleX -= deltaTimeSeconds * 0.5;
        scaleY -= deltaTimeSeconds * 0.5;
        if (scaleX <= 1.5)
        {
            tooBig = 0;
        }
    }

    glLineWidth(50);
    // g
    modelMatrix = glm::mat3(1);
    // scale to center
    modelMatrix *= Transform::Translate(230, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-230, -(float)resolution.y / 2.0);

    // to position
    modelMatrix *= Transform::Translate(200, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["g"], shaders["VertexColor"], modelMatrix);

    // a
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(330, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-330, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(300, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["a"], shaders["VertexColor"], modelMatrix);

    // m
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(430, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-430, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(400, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["m"], shaders["VertexColor"], modelMatrix);

    // e
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(530, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-530, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(500, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["e"], shaders["VertexColor"], modelMatrix);

    // o
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(730, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-730, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(700, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["o"], shaders["VertexColor"], modelMatrix);

    // v
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(830, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-830, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(800, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["v"], shaders["VertexColor"], modelMatrix);

    // e
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(930, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-930, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(900, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["e"], shaders["VertexColor"], modelMatrix);

    // r
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(1030, (float)resolution.y / 2.0);
    modelMatrix *= Transform::Scale(scaleX / 2, scaleY / 2);
    modelMatrix *= Transform::Translate(-1030, -(float)resolution.y / 2.0);

    modelMatrix *= Transform::Translate(1000, (float)resolution.y / 2.0 - 30);
    RenderMesh2D(meshes["r"], shaders["VertexColor"], modelMatrix);
}

void Tema1::FatalCollision(float leftCornerYShuriken, float translateXShuriken, float leftCornerXBow, float leftCornerYBow, float translateYBow)
{
    float dx, dy1, dy2, d1, d2;
    // shuriken radius
    float radiusShuriken = shurikenLength * sqrt(2.0) / 2;

    // shuriken position
    float xShuriken = translateXShuriken + shurikenLength / 2.0;
    float yShuriken = leftCornerYShuriken + shurikenLength / 2.0;

    // bow radius
    float radiusBow = 80; //ScaleBowY

    // bow position
    float xBow = leftCornerXBow - 25 + 17.5;      // xBow + scaleBowX / 2
    float yBow1 = leftCornerYBow + translateYBow; // + scaleY / 2
    float yBow2 = leftCornerYBow + translateYBow;

    dx = xShuriken - xBow;
    dy1 = yShuriken - yBow1;
    dy2 = yShuriken - yBow2;
    d1 = sqrt(dx * dx + dy1 * dy1);
    d2 = sqrt(dx * dx + dy2 * dy2);
    if (d1 < (radiusShuriken + radiusBow) || d2 < (radiusShuriken + radiusBow))
    {
        collisionShurikenBow = true;
        dead--;
        restart = false;
    }
}

bool Tema1::CollisionArrowShuriken(float leftCornerYShuriken, float translateXShuriken,
    float x_value, float y_value, int id)
{
    float dx, dy, d;

    // shuriken radius
    float radiusShuriken = shurikenLength * sqrt(2.0) / 2;

    // shuriken position
    float xShuriken = translateXShuriken + shurikenLength / 2.0;
    float yShuriken = leftCornerYShuriken + shurikenLength / 2.0;

    // arrow radius
    float radiusArrow = 0;

    // arrowhead positions
    float ip = arrowLine + arrowSide / 2.0;
    float catX = cos(angleArrow) * ip;
    float catY = sin(angleArrow) * ip;

    // arrow position
    float xArrow = x_value + translateXArrow + catX;
    float yArrow = y_value + translateYArrow + catY;

    dx = xShuriken - xArrow;
    dy = yShuriken - yArrow;
    d = sqrt(dx * dx + dy * dy);
    if (d < radiusShuriken + radiusArrow)
    {
        shurikenDown[leftCornerYShuriken] = true;
        return true;
    }

    return false;
}

bool Tema1::CollisionArrowBalloon(float leftCornerXBalloon, float translateYBalloon,
    float x_value, float y_value)
{
    float dx, dy, d;

    float polylineSide = 25;
    float triangleY = 1.70 * polylineSide + translateYBalloon;
    float circleY = triangleY + 45;         // scaleYBalloon + h_triangle
    float circleX = leftCornerXBalloon + 5; // scaleX / 2 - side_triangle

    float radiusBalloon = 40; // scaleYBalloon

    // shuriken position
    float xBalloon = circleX; // scaleXBalloon / 2 + side_triangle
    float yBalloon = circleY; // scaleYBalloon

    // arrow radius
    float radiusArrow = 0;

    // arrowhead positions
    float ip = arrowLine + arrowSide / 2.0;
    float catX = cos(angleArrow) * ip;
    float catY = sin(angleArrow) * ip;

    // bow position
    float xArrow = x_value + translateXArrow + catX;
    float yArrow = y_value + translateYArrow + catY;

    dx = xBalloon - xArrow;
    dy = yBalloon - yArrow;
    d = sqrt(dx * dx + dy * dy);
    if (d < radiusBalloon + radiusArrow)
    {
        balloonDown[leftCornerXBalloon] = true;

        return true;
    }

    return false;
}

void Tema1::RenderBalloonDown(float leftCornerX, float translateY, std::string polyline,
    std::string triangle, std::string circle)
{
    scaleBalloon = balloonScale[leftCornerX];
    float polylineSide = 25;
    float triangleY = 1.70 * polylineSide + translateY - (1.0 / scaleBalloon) * 10;
    float circleY = triangleY + 45 - (1 / (scaleBalloon * 0.5));
    float circleX = leftCornerX + 5;

    // polyline
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(leftCornerX, translateY);
    RenderMesh2D(meshes[polyline], shaders["VertexColor"], modelMatrix);

    // circle
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(circleX, circleY);
    modelMatrix *= Transform::Scale(20, 40);
    modelMatrix *= Transform::Scale(scaleBalloon, scaleBalloon);
    RenderMesh2D(meshes[circle], shaders["VertexColor"], modelMatrix);
}

void Tema1::Shurikens(float deltaTimeSeconds)
{
    map<float, bool>::iterator itr;
    // for each shuriken
    for (itr = shurikenDown.begin(); itr != shurikenDown.end(); ++itr)
    {
        if (!(itr->second))
        {
            if (shurikenPairs[itr->first] > -50)
            {
                // translate X
                shurikenPairs[itr->first] -= deltaTimeSeconds * 90;
                RenderShuriken(itr->first, deltaTimeSeconds, shurikenPairs[itr->first]);
                // check collision between shuriken and player
                FatalCollision(itr->first, shurikenPairs[itr->first], 50, (float)resolution.y / 2, translateY);
                bool isCollision;
                // check collision between shuriken and arrow
                isCollision = CollisionArrowShuriken(itr->first, shurikenPairs[itr->first], x_value, y_value, 1);
                if (isCollision && scaleScore <= 70)
                {
                    scaleScore += deltaTimeSeconds * 100;
                }
            }
            else
            {
                // render the shuriken again
                int randomFactor = rand() % 5 + 3;
                shurikenPairs[itr->first] = (float)resolution.x + (float)randomFactor * 100;
            }
        }
        // if one of them was hit
        else
        {
            shurikenCollision[itr->first] -= deltaTimeSeconds * 150;
            // translate shuriken down
            RenderShuriken(shurikenCollision[itr->first], deltaTimeSeconds, shurikenPairs[itr->first]);
            // if the shuriken is out, reset everything
            if (shurikenCollision[itr->first] < -50)
            {
                shurikenDown[itr->first] = false;
                shurikenCollision[itr->first] = itr->first;
                int randomFactor = rand() % 8 + 3;
                shurikenPairs[itr->first] = (float)resolution.x + (float)randomFactor * 100;
            }
        }
    }
}

void Tema1::Ballons(float deltaTimeSeconds)
{
    map<float, bool>::iterator itr;
    // for each balloon
    for (itr = balloonDown.begin(); itr != balloonDown.end(); ++itr)
    {
        if (!(itr->second))
        {
            if (balloonPairs.find(itr->first) != balloonPairs.end())
            {
                if (balloonPairs[itr->first] <= (float)resolution.y)
                {
                    // Y translate
                    balloonPairs[itr->first] += deltaTimeSeconds * 75;
                    bool isCollision;
                    // yellow balloons
                    if (itr->first == 525 || itr->first == 750 || itr->first == 975)
                    {
                        RenderBalloon(itr->first, balloonPairs[itr->first], "polylineYellow", "triangleYellow", "circleYellow");
                        // check collision between arow and balloon
                        isCollision = CollisionArrowBalloon(itr->first, balloonPairs[itr->first], x_value, y_value);
                        if (isCollision && scaleScore >= 1)
                        {
                            scaleScore -= deltaTimeSeconds * 100;
                        }
                    }
                    // red balloons
                    else
                    {
                        RenderBalloon(itr->first, balloonPairs[itr->first], "polylineRed", "triangleRed", "circleRed");
                        // check collision between arow and balloon
                        isCollision = CollisionArrowBalloon(itr->first, balloonPairs[itr->first], x_value, y_value);
                        if (isCollision && scaleScore <= 70)
                        {
                            scaleScore += deltaTimeSeconds * 100;
                        }
                    }
                }
                // render the balloon again
                else
                {
                    int randomFactor = rand() % 7 + 1;
                    balloonPairs[itr->first] = -110 * randomFactor;
                }
            }
        }
        // if one of them was hit
        else
        {
            if (balloonPairs.find(itr->first) != balloonPairs.end())
            {
                balloonPairs[itr->first] -= deltaTimeSeconds * 150;
                balloonScale[itr->first] -= deltaTimeSeconds * 0.1;
                // yellow balloons
                if (itr->first == 525 || itr->first == 750 || itr->first == 975)
                {
                    RenderBalloonDown(itr->first, balloonPairs[itr->first], "polylineYellow", "triangleYellow", "circleYellow");
                }
                // red balloons
                else
                {
                    RenderBalloonDown(itr->first, balloonPairs[itr->first], "polylineRed", "triangleRed", "circleRed");
                }
                // reset everything if the balloon is out
                if (balloonPairs[itr->first] < -100)
                {
                    balloonDown[itr->first] = false;
                    int randomFactor = rand() % 7 + 1;
                    balloonPairs[itr->first] = -110 * randomFactor;
                    balloonScale[itr->first] = 1;
                }
            }
        }
    }
}

void Tema1::RenderScoreBar(float deltaTimeSeconds)
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform::Translate(20, resolution.y - 110);
    modelMatrix *= Transform::Scale(scaleScore, 1);

    RenderMesh2D(meshes["scorebar"], shaders["VertexColor"], modelMatrix);
}

void Tema1::Update(float deltaTimeSeconds)
{
    // game over
    if (dead == 0)
    {
        if (!restart)
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            RenderGameOver(deltaTimeSeconds);
        }
        // press SPACE to restart the game
        else
        {
            restart = true;
            dead = 3;
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            scaleScore = 1;
        }
    }
    else
    {
        // if the player was hit reload the scene
        if (collisionShurikenBow)
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // reset the shurikens values
            for (map<float, bool>::iterator itr = shurikenDown.begin(); itr != shurikenDown.end(); ++itr)
            {
                shurikenDown[itr->first] = false;
                shurikenCollision[itr->first] = itr->first;
                int randomFactor = rand() % 10 + 4;
                shurikenPairs[itr->first] = (float)resolution.x + 100 * randomFactor;
            }

            // reset the balloons values
            for (map<float, float>::iterator itr = balloonPairs.begin(); itr != balloonPairs.end(); ++itr)
            {
                int randomFactor = rand() % 10 + 2;
                float y = -100.0 * randomFactor;
                balloonPairs[itr->first] = y;
                balloonDown[itr->first] = false;
                balloonScale[itr->first] = 1;
            }

            // reset the variables for the bow & arrow movement
            translateX = 0;
            translateY = 0;

            // reset the angles
            angleBow = 0;    // bow
            angularStep = 0; // shuriken

            power = 0;
            finally = true;
            press = false;
            pressed_time = 0;
            collisionShurikenBow = false;
        }

        // throw the arrow only to the right
        if (mouseReleaseX >= 150)
        {
            // if the arrow left the scene
            if (!finally)
            {
                ThroughArrow(x_value, y_value, deltaTimeSeconds);
            }
        }
        else
        {
            finally = true;
        }

        // render the objects
        RenderBow(50, (float)resolution.y / 2, translateY, deltaTimeSeconds);
        RenderPowerBar(deltaTimeSeconds);
        RenderScoreBar(deltaTimeSeconds);
        RenderLives();
        Shurikens(deltaTimeSeconds);
        Ballons(deltaTimeSeconds);
    }
}

void Tema1::FrameEnd()
{
    DrawCoordinatSystem();
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // move the bow with W, S, also set the limit
    if (window->KeyHold(GLFW_KEY_W) && ((float)resolution.y / 2 + translateY <= (float)resolution.y - 200))
    {
        translateY += deltaTime * 100;
    }
    if (window->KeyHold(GLFW_KEY_S) && -((float)resolution.y / 2 + translateY - 150 >= 0))
    {
        translateY -= deltaTime * 100;
    }

    // restart the game when it's over
    if (window->KeyHold(GLFW_KEY_SPACE) && dead == 0)
    {
        restart = true;
    }
}

void Tema1::OnKeyPress(int key, int mods)
{
    // add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mousePosX = mouseX;
    mousePosY = mouseY;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // add mouse button press event
    if (finally)
    {
        glGetInteger64v(GL_TIMESTAMP, &start_time);
        press = true;
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // add mouse button release event
    if (finally && press)
    {
        mouseRelease = true;
        // to mathematical coordinates
        mouseReleaseX = mouseX;
        mouseReleaseY = 720 - mouseY;
        // resets the values
        translateXArrow = 0;
        translateYArrow = 0;
        x_value = 0;
        y_value = 0;
        if (press)
        {
            glGetInteger64v(GL_TIMESTAMP, &end_time);
            pressed_time = (end_time - start_time) / (1000000000.0);
        }
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
