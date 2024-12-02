#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light();
	Light(glm::vec3 p, glm::vec3 c);
	~Light();

	glm::vec3 position; 
	glm::vec3 color; 

private:
	
};
