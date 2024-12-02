#include "Triangle.h"
#include <iostream>
Triangle::Triangle()
{
}

Triangle::Triangle(glm::vec3 v_1, glm::vec3 v_2, glm::vec3 v_3, 
                glm::vec3 n_1, glm::vec3 n_2, glm::vec3 n_3) : 
            v0(v_1), v1(v_2), v2(v_3), n0(n_1), n1(n_1), n2(n_3)
{
    
}

Triangle::~Triangle()
{
}

float Triangle::intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    glm::vec3 e1 = v1 - v0; 
    glm::vec3 e2 = v2 - v0;
    glm::vec3 s = rayorigin - v0;
    glm::vec3 s1 = glm::cross(raydir, e2);
    glm::vec3 s2 = glm::cross(s, e1);

    glm::vec3 mt = (1.0f / glm::dot(s1, e1)) * glm::vec3(glm::dot(s2, e2), glm::dot(s1, s), glm::dot(s2, raydir));

    float t = mt.x;  
    beta = mt.y; 
    gamma = mt.z; 
    alpha = 1 - beta - gamma; 

    if(t >= t0 && t < t1 && alpha >= 0 && beta >= 0 && gamma >= 0 &&
		alpha < 1 && beta < 1 && gamma < 1) {
        return t; 
    }
    return MAXFLOAT; 
}

glm::vec3 Triangle::getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    float t = this->intersect(rayorigin, raydir, t0, t1); 
    return rayorigin + raydir * t; 
}

glm::vec3 Triangle::getnormal(glm::vec3 point) {
    glm::vec3 normal = alpha * n0 + beta * n1 + gamma * n2; 
    return normal;
}

float Triangle::computeAverage(int i) {
    return (v0[i] + v1[i] + v2[i]) / 3; 
}
