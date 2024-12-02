#pragma once
#include <vector>
#include <limits.h>
#include "Shape.h"
#include "Light.h"


class Scene
{
public:
	Scene();
	Scene(std::vector<Shape*> s, std::vector<Light*> l); // send in shape vector and light vector and set up private variables
	~Scene();
	bool hit(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1, Shape** rec); 
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

private:
	

};
