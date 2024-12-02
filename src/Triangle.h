#pragma once
#include "Shape.h"
#include <cmath>


class Triangle :
	public Shape
{
public:
	Triangle();
	Triangle(glm::vec3 v_1, glm::vec3 v_2, glm::vec3 v_3, 
                glm::vec3 n_1, glm::vec3 n_2, glm::vec3 n_3);
	float intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1);
	glm::vec3 getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1); 
	glm::vec3 getnormal(glm::vec3 point);
    float computeAverage(int i);
	~Triangle();

    glm::vec3 v0;
    glm::vec3 v1;  
    glm::vec3 v2; 

private:

    glm::vec3 n0;
    glm::vec3 n1;  
    glm::vec3 n2; 

    float alpha; 
    float beta; 
    float gamma; 
};
