#include "Plane.h"


Plane::Plane()
{
}

Plane::Plane(glm::vec3 c, glm::vec3 n, glm::vec3 a, glm::vec3 d, 
			glm::vec3 s, glm::vec3 m, float ns) : 
            center(c), normal(n)
{
    this->setvar(a, d, s, m, ns);
}

Plane::~Plane()
{
}

float Plane::intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    float t = glm::dot((center - rayorigin), normal) / glm::dot(raydir, normal); 
    if(t >= t0 && t < t1) {
        return t; 
    }
    return MAXFLOAT; 
}

glm::vec3 Plane::getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    float t = this->intersect(rayorigin, raydir, t0, t1); 
    return rayorigin + raydir * t; 
}


