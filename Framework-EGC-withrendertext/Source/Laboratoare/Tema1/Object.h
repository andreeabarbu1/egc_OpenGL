#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object
{
	Mesh *CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, float side, glm::vec3 color);

	Mesh *CreatePlayer(std::string name, glm::vec3 leftBottomCorner, float segments, glm::vec3 color);

	Mesh *CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);

	Mesh *CreatePolyline(std::string name, glm::vec3 leftBottomCorner, float side, glm::vec3 color);

	Mesh *CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float side, glm::vec3 color);

	Mesh *CreateCircle(std::string name, glm::vec3 leftBottomCorner, float triangles, glm::vec3 color);

	Mesh *CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color);

	Mesh *CreateHeart(std::string name, glm::vec3 leftBottomCorner, float side1, float side2, glm::vec3 color);

} // namespace Object
