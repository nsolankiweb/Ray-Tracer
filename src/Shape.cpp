#include "Shape.h"

Shape::Shape(void)
{
}

Shape::~Shape(void)
{
}

void Shape::setvar(glm::vec3 a, glm::vec3 d, glm::vec3 s, glm::vec3 m, float ns) {
    ka = a; 
    kd = d; 
    ks = s; 
    km = m; 
    n = ns; 
}