#include "Scene.h"
#include <iostream>
#include <cmath>
Scene::~Scene()
{
}

Scene::Scene(std::vector<Shape*> s, std::vector<Light*> l) : shapes(s), lights(l)
{
}

Scene::Scene()
{

}

bool Scene::hit(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1, Shape** rec) {
    float minT = MAXFLOAT;  
    for(int i = 0; i < shapes.size(); i++) {
        
        float t = shapes[i]->intersect(rayorigin, raydir, t0, t1); 
        
        if(t < minT) {
            //std::cout << "hit" << std::endl; 
            minT = t; 
            
            *rec = shapes[i]; 
        }
    }
    if(minT == MAXFLOAT) {
        return false;
    }
    
    return true; 
}
