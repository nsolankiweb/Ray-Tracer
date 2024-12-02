#include "Camera.h"
#include <iostream>
#include <cmath>
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(int widthRes, int heightRes, glm::vec3 e, 
				glm::vec3 la, glm::vec3 u, float fy, float fd) :
				eye(e), lookat(la), up(u), fovy(fy), focaldis(fd)
{
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	renderedImage = new float[widthRes * heightRes * 3];
}

void Camera::TakePicture(Scene *scene)
{	
	
	memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);

	//int index = (j * widthRes + i) * 3 + k;
	// i width, j height k color
			glm::vec3 viewdir = glm::normalize(lookat - eye); 
			glm::vec3 Ic = eye + focaldis * viewdir; 
			
			glm::vec3 a = eye - lookat; 
			glm::vec3 w = glm::normalize(a); 
			glm::vec3 u = glm::normalize(glm::cross(up, w));
			glm::vec3 v = glm::cross(w, u); 

			float ly = 2.0f * focaldis * glm::tan(glm::radians(fovy / 2.0f)); 


			float Pw = ly / (float)heightRes; 

			float lx = ly * ((float)widthRes / (float)heightRes);

			glm::vec3 o = Ic - (lx / 2.0f) * u - (ly / 2.0f) * v; 


	for (int i = 0; i < widthRes; i++) {
  		for (int j = 0; j < heightRes; j++) {

			glm::vec3 color = glm::vec3(0.0, 0.0, 0.0); 

			// //compute primary ray

			glm::vec3 Pc = o + (i + 0.5f) * Pw * u + (j + 0.5f) * Pw * v; 
	
			glm::vec3 direction = glm::normalize(Pc - eye); 


			//compute ray color (function)
			color = ComputeRayColor(eye, direction, 0.0f, MAXFLOAT, scene, 0); 

			for(int k = 0; k < 3; k++) {
				int index = (j * widthRes + i) * 3 + k;
				renderedImage[index] = color[k];
				
			}

  		}
	}
	
}

glm::vec3 Camera::ComputeRayColor(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1, Scene* scene, int count) {
	/*
	if (scene->Hit(ray, t0, t1, rec)) then
    	color c = ambient
    	for each light
    		if (not scene->Hit(sray, ε, tlight, srec)) then
        		c = c + diffuse & specular
    	return c
	else
    	return background color black
	*/
	if(count == 4) {
		return glm::vec3(0.0, 0.0, 0.0);
	}

	Shape* rec1;
	Shape* rec2;  
	glm::vec3 color = glm::vec3(0.0, 0.0, 0.0); 

	
	if(scene->hit(rayorigin, raydir, t0, t1, &rec1)) {
		
		
		color = rec1->ka; 

		glm::vec3 P = rec1->getpoint(rayorigin, raydir, t0, t1);
		glm::vec3 N = rec1->getnormal(P); 
		glm::vec3 E = normalize(rayorigin - P); 

		for(int i = 0; i < scene->lights.size(); i++) {
			glm::vec3 sdir = glm::normalize(scene->lights[i]->position - P);
			float lightdis = glm::distance(scene->lights[i]->position, P);

			if(!scene->hit(P, sdir, 0.0001f, lightdis, &rec2)) {
				
				glm::vec3 L = glm::normalize(scene->lights[i]->position - P); 
				glm::vec3 R = glm::normalize(2.0f * glm::dot(L, N) * N - L); 
				float m1 = glm::dot(L, N); 
				float m2 = glm::dot(R, E); 

				
				color += scene->lights[i]->color * (rec1->kd * std::max(0.0f, m1) + rec1->ks * glm::pow(std::max(0.0f, m2), rec1->n));
				//std::cout << "hit" << std::endl; 
		 	}
			
		}

		glm::vec3 V = glm::normalize(rayorigin - P); 
		glm::vec3 R = glm::normalize(2.0f * glm::dot(V, N) * N - V);
		color += rec1->km * ComputeRayColor(P, R, 0.0001, MAXFLOAT, scene, (count + 1));
		return color; 
	}

	return color; 
}
