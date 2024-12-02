#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Shape
{
public:
	Shape(void);
	~Shape(void);
	void setvar(glm::vec3 a, glm::vec3 d, glm::vec3 s, glm::vec3 m, float ns); 
	virtual float intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {return 0.0; }; 
	virtual glm::vec3 getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {return glm::vec3(0.0, 0.0, 0.0); }; 
	virtual glm::vec3 getnormal(glm::vec3 point) {return glm::vec3(0.0, 0.0, 0.0); }; 
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float n; 

private:
	 
};
