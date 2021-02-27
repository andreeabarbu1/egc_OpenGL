#include "Object.h"

#include <Core/Engine.h>

Mesh *Object::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, float side, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(0, (-1) * side / 5, 0), color),				  //0
			VertexFormat(corner + glm::vec3(length, (-1) * side / 5, 0), color),		  //1
			VertexFormat(corner + glm::vec3(length, (-1) * (side + side / 5), 0), color), //2
			VertexFormat(corner + glm::vec3(length + 3 / 2 * side, 0, 0), color),		  //3
			VertexFormat(corner + glm::vec3(length, side + side / 5, 0), color),		  //4
			VertexFormat(corner + glm::vec3(length, side / 5, 0), color),				  //5
			VertexFormat(corner + glm::vec3(0, side / 5, 0), color)						  //6
		};

	std::vector<unsigned short> indices = {	
		0, 1, 6,
		5, 1, 6,
		1, 2, 3,
		1, 3, 5,
		5, 4, 3,
	};

	Mesh* arrow = new Mesh(name);
	arrow->InitFromData(vertices, indices);
	return arrow;
}

Mesh *Object::CreatePlayer(std::string name, glm::vec3 leftBottomCorner, float segments, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(corner, color)); // center

	float PI = 3.1415926f;
	float start = segments * 3 / 8;
	float end = segments * 5 / 4;

	for (float i = start; i < end; i++)
	{
		float theta = 2.0 * PI * float(i) / float(segments); //get the current angle

		float x = cosf(theta); //calculate the x component
		float y = sinf(theta); //calculate the y component

		vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
	}

	// line
	vertices.push_back(VertexFormat(corner, color));
	vertices.push_back(VertexFormat(corner + glm::vec3(0, -1, 0), color));

	for (float i = start + 2; i <= end; i++)
	{
		indices.push_back(i);
		indices.push_back(i - 1);
	}

	//add the line
	indices.push_back(0);
	indices.push_back(-1);

	Mesh *player = new Mesh(name);
	player->SetDrawMode(GL_LINE_STRIP);
	player->InitFromData(vertices, indices);
	return player;
}

Mesh *Object::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),									   // 0
			VertexFormat(corner + glm::vec3(0, length / 2, 0), color),		   // 1
			VertexFormat(corner + glm::vec3(0, length, 0), color),			   // 2
			VertexFormat(corner + glm::vec3(length / 2, length, 0), color),	   // 3
			VertexFormat(corner + glm::vec3(length, length, 0), color),		   // 4
			VertexFormat(corner + glm::vec3(length, length / 2, 0), color),	   // 5
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			   // 6
			VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),		   // 7
			VertexFormat(corner + glm::vec3(length / 2, length / 2, 0), color) // 8 - center
		};

	std::vector<unsigned short> indices = {
		0, 8, 1,
		2, 8, 3,
		4, 8, 5,
		6, 8, 7};

	// create mesh
	Mesh *shuriken = new Mesh(name);
	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

Mesh *Object::CreatePolyline(std::string name, glm::vec3 leftBottomCorner, float side, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float triangleY = 1.70 * side;
	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(side / 2, 0, 0), color),		   // 0
			VertexFormat(corner + glm::vec3(0, side / 2, 0), color),		   // 1
			VertexFormat(corner + glm::vec3(side / 2, side, 0), color),		   // 2
			VertexFormat(corner + glm::vec3(0, 1.5 * side, 0), color),		   // 3
			VertexFormat(corner + glm::vec3(side / 5.0, triangleY, 0), color), // 4
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 4};

	// create polyline
	Mesh *polyline = new Mesh(name);
	polyline->SetDrawMode(GL_LINE_STRIP);
	polyline->InitFromData(vertices, indices);
	return polyline;
}

Mesh *Object::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float side, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),									   // 0
			VertexFormat(corner + glm::vec3(side, 0, 0), color),			   // 1
			VertexFormat(corner + glm::vec3(side / 2, 0.75 * side, 0), color), // 2
		};

	std::vector<unsigned short> indices = {0, 1, 2};

	Mesh *triangle = new Mesh(name);
	triangle->SetDrawMode(GL_TRIANGLES);
	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh *Object::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float triangles, glm::vec3 color)
{

	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(corner, color)); // center

	float PI = 3.1415926f;

	for (float i = 0; i < triangles; i++)
	{
		float theta = 2.0 * PI * float(i) / float(triangles); // get the current angle

		float x = cosf(theta); // calculate the x component
		float y = sinf(theta); // calculate the y component

		vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
	}

	for (float i = 0; i <= triangles; i++)
	{
		indices.push_back(0);
		indices.push_back(i - 1);
		indices.push_back(i);
	}

	indices.push_back(0);
	indices.push_back(triangles);
	indices.push_back(1);

	Mesh *circle = new Mesh(name);
	circle->SetDrawMode(GL_TRIANGLES);
	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh *Object::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),							   // 0
			VertexFormat(corner + glm::vec3(length, 0, 0), color),	   // 1
			VertexFormat(corner + glm::vec3(length, width, 0), color), // 2
			VertexFormat(corner + glm::vec3(0, width, 0), color)	   // 3
		};

	std::vector<unsigned short> indices = {
		0, 1, 2, 
		0, 2, 3
	};

	Mesh *rectangle = new Mesh(name);
	rectangle->InitFromData(vertices, indices);
	rectangle->SetDrawMode(GL_TRIANGLES);
	return rectangle;
}

Mesh *Object::CreateHeart(std::string name, glm::vec3 leftBottomCorner, float side1, float side2, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

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
		8, 9, 1};

	Mesh *heart = new Mesh(name);
	heart->InitFromData(vertices, indices);
	heart->SetDrawMode(GL_TRIANGLES);
	return heart;
}
