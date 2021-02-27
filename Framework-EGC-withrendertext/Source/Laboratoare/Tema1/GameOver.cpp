#include "GameOver.h"
#include <Core/Engine.h>

Mesh *GameOver::G(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //0
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//1
			VertexFormat(corner + glm::vec3(0, 0, 0), color),				//2
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			//3
			VertexFormat(corner + glm::vec3(length, length, 0), color),		//4
			VertexFormat(corner + glm::vec3(length / 2, length, 0), color), //5
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 4, 5};

	Mesh *g = new Mesh(name);
	g->SetDrawMode(GL_LINE_STRIP);
	g->InitFromData(vertices, indices);
	return g;
}

Mesh *GameOver::A(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(0, 0, 0), color),				//0
			VertexFormat(corner + glm::vec3(0, length, 0), color),			//1
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//2
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //3
			VertexFormat(corner + glm::vec3(length, length, 0), color),		//4
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			//5
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 4, 5, 4, 1};

	Mesh *a = new Mesh(name);
	a->SetDrawMode(GL_LINE_STRIP);
	a->InitFromData(vertices, indices);
	return a;
}

Mesh *GameOver::M(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(0, 0, 0), color),				//0
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//1
			VertexFormat(corner + glm::vec3(length / 2, length, 0), color), //2
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //3
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			//3
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 4};

	Mesh *m = new Mesh(name);
	m->SetDrawMode(GL_LINE_STRIP);
	m->InitFromData(vertices, indices);
	return m;
}

Mesh *GameOver::E(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //0
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//1
			VertexFormat(corner + glm::vec3(0, length, 0), color),			//2
			VertexFormat(corner + glm::vec3(length, length, 0), color),		//3
			VertexFormat(corner + glm::vec3(0, 0, 0), color),				//4
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			//5
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 2, 4, 5};

	Mesh *e = new Mesh(name);
	e->SetDrawMode(GL_LINE_STRIP);
	e->InitFromData(vertices, indices);
	return e;
}

Mesh *GameOver::O(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(0, 0, 0), color),				//0
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//1
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //2
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			//3
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 0};

	Mesh *o = new Mesh(name);
	o->SetDrawMode(GL_LINE_STRIP);
	o->InitFromData(vertices, indices);
	return o;
}

Mesh *GameOver::V(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//0
			VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),		//1
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //2
		};

	std::vector<unsigned short> indices = {0, 1, 2};

	Mesh *v = new Mesh(name);
	v->SetDrawMode(GL_LINE_STRIP);
	v->InitFromData(vertices, indices);
	return v;
}

Mesh *GameOver::R(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	float length = 60;

	std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner + glm::vec3(0, 0, 0), color),				//0
			VertexFormat(corner + glm::vec3(0, length * 2, 0), color),		//1
			VertexFormat(corner + glm::vec3(length, length * 2, 0), color), //2
			VertexFormat(corner + glm::vec3(length, length, 0), color),		//3
			VertexFormat(corner + glm::vec3(0, length, 0), color),			//4
			VertexFormat(corner + glm::vec3(length, 0, 0), color),			//5
		};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 4, 5};

	Mesh *r = new Mesh(name);
	r->SetDrawMode(GL_LINE_STRIP);
	r->InitFromData(vertices, indices);
	return r;
}
