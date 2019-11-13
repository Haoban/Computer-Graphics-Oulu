
#ifndef ASSIGNMENT_3_H_
#define ASSIGNMENT_3_H_

#include <vector>                       // Standard vector template
#include <GL/glew.h>                    // OpenGL extension wrangler library
#include <SDL.h>                        // libSDL functionality
#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <glm/gtc/type_ptr.hpp>         // Needed for glm::value_ptr(x). You can use &x[0] instead of that.
#include "scene.h"                      // Abstract scene class
#include "shaderprogram.h"              // For shader management
#include "texture.h"
#include <stack>
/**
* \brief Draws a vertex-colored tetrahedron
*/
class assignment3 : public Scene
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;

		Vertex(const glm::vec3 &position_ = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3 &normal_ = glm::vec3(0.0f, 0.0f, 0.0f)) :
			position(position_),
			normal(normal_)
		{
		}
	};

	glm::mat4 projectionMat;
	glm::mat4 viewMat;
	glm::mat4 modelMat;
	float rotation = 0; // Current rotation position
	std::stack<glm::mat4> glm_ModelViewMatrix;

	// Vertex Array Object, Vertex Buffer Object and Index Buffer Object handlers
	glm::mat4 mvpMat_p1;
	GLuint vao_p1, vbo_p1, ibo_p1;
	ShaderProgram shaderProgram_p1;
	std::vector<Vertex> sphere_p1;
	std::vector<GLushort> sphereIndices_p1;

	glm::mat4 mvpMat_p2;
	GLuint vao_p2, vbo_p2, ibo_p2;
	ShaderProgram shaderProgram_p2;
	std::vector<Vertex> sphere_p2;
	std::vector<GLushort> sphereIndices_p2;

	glm::mat4 mvpMat_p3;
	GLuint vao_p3, vbo_p3, ibo_p3;
	ShaderProgram shaderProgram_p3;
	std::vector<Vertex> sphere_p3;
	std::vector<GLushort> sphereIndices_p3;


	glm::vec3 scale = glm::vec3(0.4, 0.4, 0.4);
	void createIcosahedron(std::vector<Vertex> &tetrahedron, std::vector<GLushort> &tetrahedronIndices) const;
	void createSphere(std::vector<Vertex> &sphere, std::vector<GLushort> &sphereIndices, int numTesselations) const;
	bool change_action;
	float mouse_upward_x, mouse_upward_y;
	float mouse_downward_x, mouse_downward_y;
	float x_move = 0, y_move = 0;


public:
	assignment3();
	virtual ~assignment3();

	// Initialize scene
	virtual bool init();

	// Called on window resize
	virtual void resize(GLsizei width, GLsizei height);

	// Update scene
	virtual void update(float timestep);

	// Render view
	virtual void render();

	// Handle SDL event
	virtual bool handleEvent(const SDL_Event &e);
};

#endif
