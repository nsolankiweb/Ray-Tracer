#pragma once
#include <vector>
//#include <cstring>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include <algorithm>
#include <cmath>



class Camera
{
public:
	Camera();
	~Camera();

	Camera(int widthRes, int heightRes, glm::vec3 e, 
				glm::vec3 la, glm::vec3 u, float fy, float fd);

	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };
	glm::vec3 ComputeRayColor(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1, Scene *scene, int count);

private:

	int widthRes;
	int heightRes;
	glm::vec3 eye; 
	glm::vec3 lookat;
	glm::vec3 up;
	float fovy;
	float focaldis;

	float *renderedImage;


};
