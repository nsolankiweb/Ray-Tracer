#pragma once
#include "Shape.h"
#include <cmath>


class Sphere :
	public Shape
{
public:
	Sphere();
	Sphere(glm::vec3 p, float r, glm::vec3 a, glm::vec3 d, 
			glm::vec3 s, glm::vec3 m, float ns);
	float intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1);
	glm::vec3 getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1); 
	glm::vec3 getnormal(glm::vec3 point) { return glm::normalize(point - position); };
	~Sphere();

private:
	glm::vec3 position; 
	float radius; 

};
