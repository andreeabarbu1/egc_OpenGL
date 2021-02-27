#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace GameOver
{
	Mesh *G(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *A(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *M(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *E(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *O(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *V(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *E(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh *R(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
} // namespace GameOver