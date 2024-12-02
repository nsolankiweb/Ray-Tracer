#pragma once
#include "Shape.h"
#include "Triangle.h"
#include <cmath>
#include <vector>

class BVH :
	public Shape
{
public:
	BVH();
	BVH(std::vector<Triangle> tr, glm::vec3 a, glm::vec3 d, 
			glm::vec3 s, glm::vec3 m, float ns);
	BVH(std::vector<Triangle> tr, std::vector<int> i, int s, int e, int l);
    void createBox(); 
	void sortChild(); 
	float intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1);
	float Hintersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1, BVH* node);
	glm::vec3 getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1); 
	glm::vec3 getnormal(glm::vec3 point);

	~BVH();

	glm::vec3 mins; 
    glm::vec3 maxs; 

	BVH* child1 = nullptr; 
	BVH* child2 = nullptr; 

    std::vector<Triangle> tris; 
	std::vector<int> index; 
    Triangle* intT;
	
	int start = 0; 
	int end = 0; 
	int level = 0;
	int w; 

private:
	//bounding box planes
     
    
	 

};