#define GLEW_STATIC
#define TINYOBJLOADER_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <iostream>
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "BVH.h"
#include "tiny_obj_loader.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
GLFWwindow *window;

std::vector<Shape*> shapes;
std::vector<Light*> lights;

void ClearFrameBuffer()
{
	memset(&frameBuffer, 0, WINDOW_HEIGHT * WINDOW_WIDTH * 3 * sizeof(float));
}

void Display()
{	
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
}

// This function is based from Homework 3 in CSCE441
void LoadModel(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals)
{
	// Taken from Shinjiro Sueda with slight modification
	std::string meshName = "../obj/bunny.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if (!rc) {
		std::cerr << errStr << std::endl;
	}
	else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					vertices.push_back(glm::vec3(attrib.vertices[3 * idx.vertex_index + 0],
												 attrib.vertices[3 * idx.vertex_index + 1],
												 attrib.vertices[3 * idx.vertex_index + 2]));

					if (!attrib.normals.empty()) {
						normals.push_back(glm::vec3(attrib.normals[3 * idx.normal_index + 0],
													attrib.normals[3 * idx.normal_index + 1],
													attrib.normals[3 * idx.normal_index + 2]));
					}
				}
				index_offset += fv;
			}
		}
	}
}

// This function is based from Homework 3 in CSCE441
void CreateTriangleVector(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<Triangle> &t)
{
	for (int i = 0; i < vertices.size() / 3; i++)
	{
		Triangle myTriangle(vertices[i * 3 + 0], vertices[i * 3 + 1], vertices[i * 3 + 2], 
								normals[i * 3 + 0], normals[i * 3 + 1], normals[i * 3 + 2]);
		t.push_back(myTriangle);
	}
}

void Init()
{

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment6 - <Nandni Solanki>", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ClearFrameBuffer();

	
	
	Camera camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0, 0.0, 7.0), glm::vec3(0.0, 0.0, 0.0), 
							glm::vec3(0.0, 1.0, 0.0), 45.0f, 1.0f);
	std::vector<Shape*> s; 
	std::vector<Light*> l; 

	Sphere s1(glm::vec3(-1.0, -0.7, 3.0), 0.3, glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.2, 1.0, 0.2), 
				glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 100.0); 
	s.push_back(&s1);
	Sphere s2(glm::vec3(1.0, -0.5, 3.0), 0.5, glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, 1.0), 
				glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 10.0); 
	s.push_back(&s2);
	Sphere s3(glm::vec3(-1.0, 0.0, -0.0), 1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 
				glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 0.0); 
	s.push_back(&s3);
	Sphere s4(glm::vec3(1.0, 0.0, -1.0), 1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 
				glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.8, 0.8, 0.8), 0.0); 
	s.push_back(&s4);
	Plane p2(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.1, 0.1, 0.1), 
				glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0.0); 
	s.push_back(&p2);
	Plane p1(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.1, 0.1, 0.1), 
				glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0.0); 
	s.push_back(&p1);


	Light l1(glm::vec3(0.0, 3.0, -2.0), glm::vec3(0.2, 0.2, 0.2));
	Light l2(glm::vec3(-2.0, 1.0, 4.0), glm::vec3(0.5, 0.5, 0.5));
	l.push_back(&l1);
	l.push_back(&l2); 
	
	std::vector<Shape*> sv;

	std::vector<glm::vec3> v; 
	std::vector<glm::vec3> n;

	std::vector<Triangle> t; 



	LoadModel(v, n); 
	CreateTriangleVector(v, n, t); 
	
	
	
	//t.erase((t.begin() + 2), t.end()); 
	
 
	BVH b(t, glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 0.5), 
					glm::vec3(0.0, 0.0, 0.0), 100.0f);
	
	
	

	sv.push_back(&b); 
	
	std::string flag; 
	std::cout << "Please input the scene flag (1 for spheres, 2 for bunny): "; 
	std::cin >> flag; 
	
	Scene scene;

	
	if(flag == "1") {
		scene = Scene(s, l);
	} else {
		scene = Scene(sv, l);
	}
	auto start = std::chrono::high_resolution_clock::now();
	camera.TakePicture(&scene);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Time passed (ms): " << duration.count() << std::endl;
	
	float *renderedImage = camera.GetRenderedImage();
	memcpy(frameBuffer, renderedImage, sizeof(float) * WINDOW_HEIGHT * WINDOW_WIDTH * 3);
}


int main()
{	
	Init();
	while ( glfwWindowShouldClose(window) == 0) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}