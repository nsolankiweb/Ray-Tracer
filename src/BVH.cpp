#include "BVH.h"
#include <iostream>
#include <algorithm>
BVH::BVH()
{
}

BVH::BVH(std::vector<Triangle> tr, glm::vec3 a, glm::vec3 d, 
			glm::vec3 s, glm::vec3 m, float ns) : tris(tr)
            
{   
   
    for(int i = 0; i < tr.size(); i++) {
        index.push_back(i); 
    }

    start = 0; 
    end = tr.size(); 
    level = 0; 
    createBox();
    sortChild(); 
    this->setvar(a, d, s, m, ns);
}

//constructor for children
BVH::BVH(std::vector<Triangle> tr, std::vector<int> i, int s, int e, int l) :
            tris(tr), index(i), start(s), end(e), level(l) {
    createBox(); 
    sortChild(); 
}
 
//create children
void BVH::sortChild() {


    //sort index array 
    bool s; 
    for (int i = start; i < end - 1; i++) {
        s = false;

        for (int j = start; j < end - i - 1; j++) {

            if (tris[j].computeAverage(level) > tris[j + 1].computeAverage(level)) {
                std::swap(index[j], index[j + 1]);
                s= true;
            }
        }
 
        // If no two elements were swapped
        // by inner loop, then break
        if (s == false)
            break;
    }
   


    int next_level; 
    if(level == 2) {
        next_level = 0; 
    } else {
        next_level = level + 1; 
    }

    //create children 
    if(end - start > 3) {
        int mid = start + ((end - start) / 2); 
        child1 = new BVH(tris, index, start, mid, next_level); 
        child2 = new BVH(tris, index, mid, end, next_level);
    }
   
}


void BVH::createBox() {
    mins = glm::vec3(0.0, 0.0, 0.0); 
    maxs = glm::vec3(0.0, 0.0, 0.0); 

    for(int j = start; j < end; j++) {
        int i = index.at(j); 
        mins.x = std::min(std::min(std::min(tris[i].v0.x, tris[i].v1.x), tris[i].v2.x), mins.x); 
        mins.y = std::min(std::min(std::min(tris[i].v0.y, tris[i].v1.y), tris[i].v2.y), mins.y); 
        mins.z = std::min(std::min(std::min(tris[i].v0.z, tris[i].v1.z), tris[i].v2.z), mins.z); 

        maxs.x = std::max(std::max(std::max(tris[i].v0.x, tris[i].v1.x), tris[i].v2.x), maxs.x); 
        maxs.y = std::max(std::max(std::max(tris[i].v0.y, tris[i].v1.y), tris[i].v2.y), maxs.y); 
        maxs.z = std::max(std::max(std::max(tris[i].v0.z, tris[i].v1.z), tris[i].v2.z), maxs.z); 
    }
}

BVH::~BVH()
{
    delete child1;
    delete child2; 
}

float BVH::intersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    //if not bounding box return max float
    //if go throught vector of t
    return Hintersect(rayorigin, raydir, t0, t1, this); 
    
}

float BVH::Hintersect(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1, BVH* node) {
    //if not bounding box return max float
    //if go throught vector of t

    
    //test if box
    float tx1 = (node->mins.x - rayorigin.x) / raydir.x; 
    float ty1 = (node->mins.y - rayorigin.y) / raydir.y; 
    float tz1 = (node->mins.z - rayorigin.z) / raydir.z; 

    float tx2 = (node->maxs.x - rayorigin.x) / raydir.x; 
    float ty2 = (node->maxs.y - rayorigin.y) / raydir.y; 
    float tz2 = (node->maxs.z - rayorigin.z) / raydir.z;

   

    float txmin; 
    float tymin; 
    float tzmin; 

    float txmax; 
    float tymax; 
    float tzmax;

    if (tx1 > tx2) {
        txmax = tx1;
        txmin = tx2; 
    }else {
        txmax = tx2;
        txmin = tx1; 
    }
        
    if (ty1 > ty2) {
        tymax = ty1;
        tymin = ty2; 
    }else {
        tymax = ty2;
        tymin = ty1; 
    }

    if (tz1 > tz2) {
        tzmax = tz1;
        tzmin = tz2; 
    }else {
        tzmax = tz2;
        tzmin = tz1; 
    }

    float tmin = std::max(std::max(txmin, tymin), tzmin); 
    float tmax = std::min(std::min(txmax, tymax), tzmax); 

    if(tmin > tmax || tmax < 0.0f) {
        return MAXFLOAT; 
    }


    //IF LEAF NODE
   
    if(node->child1 == nullptr && node->child2 == nullptr) {
        
        if(tmin >= 0 && tmax >= 0) {
            float minT = MAXFLOAT;  
            for(int i = node->start; i < node->end; i++) {
            
                int in = node->index[i]; 
                
                float t = tris[in].intersect(rayorigin, raydir, t0, t1); 
                
                if(t < minT) {
                    
                    minT = t; 
                    node->w = in; 
                }
            }
            
            return minT; 

        } else {
            return MAXFLOAT; 
        }
    }
    
    
    float hit1 = Hintersect( rayorigin, raydir,  t0,  t1, node->child1);
    float hit2 = Hintersect( rayorigin, raydir, t0,  t1, node->child2);

    if(hit1 < hit2) {
        node->w = node->child1->w;
        intT = &tris[node->w];  
        return hit1; 
    }else {
        node->w = node->child2->w; 
        intT = &tris[node->w]; 
        return hit2; 
    }

    return MAXFLOAT;
}

glm::vec3 BVH::getpoint(glm::vec3 rayorigin, glm::vec3 raydir, float t0, float t1) {
    return intT->getpoint(rayorigin, raydir, t0, t1); 
}

glm::vec3 BVH::getnormal(glm::vec3 point) {
    return intT->getnormal(point); 
} 



