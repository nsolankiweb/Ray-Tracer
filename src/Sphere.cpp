#include "Sphere.h"
#include <iostream>
Sphere::Sphere()
{
}

Sphere::Sphere(glm::vec3 p, float r, glm::vec3 a, glm::vec3 d, 
			glm::vec3 s, glm::vec3 m, float ns) : 
            position(p), radius(r)
{
    this->setvar(a, d, s, m, ns);
}

Sphere::~Sphere()
{
}

float Sphere::intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    float a = glm::dot(raydir, raydir); 
    float b = glm::dot((rayorigin - position) * 2.0f, raydir); 
    float c = glm::dot((rayorigin - position), (rayorigin - position)) - (radius * radius); 
    float x = (b * b) - (4 * a * c); 
    
    if(x == 0 && (-b/(2*a)) >= t0 && (-b/(2*a)) < t1) {
        return -b/(2*a);

    } else if (x > 0) {
        float s1 = (-b + sqrt(x)) / (2*a);
        float s2 = (-b - sqrt(x)) / (2*a);
        
        if(s1 < s2 && s1 >= t0 && s1 < t1) {
            return s1;
        } else if(s2 >= t0 && s2 < t1){
            return s2; 
        } else {
            return MAXFLOAT; 
        }
    } else {
        return MAXFLOAT; 
    }

    
}

glm::vec3 Sphere::getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    float t = this->intersect(rayorigin, raydir, t0, t1); 
    return rayorigin + raydir * t; 
}



