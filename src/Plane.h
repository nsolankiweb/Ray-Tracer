#pragma once
#include "Shape.h"
#include <cmath>
class Plane :
	public Shape
{
public:
	Plane();
	Plane(glm::vec3 c, glm::vec3 n, glm::vec3 a, glm::vec3 d, 
			glm::vec3 s, glm::vec3 m, float ns);
	~Plane();
	float intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1);
	glm::vec3 getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1);
	glm::vec3 getnormal(glm::vec3 point) {return normal; };

private:
	glm::vec3 center;
	glm::vec3 normal;

};
