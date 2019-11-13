/**
* \brief Example Scene 3 implementation
* \file
*/
#include <cassert>
#include <iostream>
#include "assignment3.h"

void assignment3::createIcosahedron(std::vector<Vertex> &icosahedron, std::vector<GLushort> &icosahedronIndices) const
{
	icosahedron.clear();

	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(-0.26286500f, 0.0000000f, 0.42532500f)), glm::normalize(glm::vec3(-0.26286500f, 0.0000000f, 0.42532500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.26286500f, 0.0000000f, 0.42532500f)), glm::normalize(glm::vec3(0.26286500f, 0.0000000f, 0.42532500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(-0.26286500f, 0.0000000f, -0.42532500f)), glm::normalize(glm::vec3(-0.26286500f, 0.0000000f, -0.42532500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.26286500f, 0.0000000f, -0.42532500f)), glm::normalize(glm::vec3(0.26286500f, 0.0000000f, -0.42532500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.0000000f, 0.42532500f, 0.26286500f)), glm::normalize(glm::vec3(0.0000000f, 0.42532500f, 0.26286500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.0000000f, 0.42532500f, -0.26286500f)), glm::normalize(glm::vec3(0.0000000f, 0.42532500f, -0.26286500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.0000000f, -0.42532500f, 0.26286500f)), glm::normalize(glm::vec3(0.0000000f, -0.42532500f, 0.26286500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.0000000f, -0.42532500f, -0.26286500f)), glm::normalize(glm::vec3(0.0000000f, -0.42532500f, -0.26286500f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.42532500f, 0.26286500f, 0.0000000f)), glm::normalize(glm::vec3(0.42532500f, 0.26286500f, 0.0000000f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(-0.42532500f, 0.26286500f, 0.0000000f)), glm::normalize(glm::vec3(-0.42532500f, 0.26286500f, 0.0000000f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(0.42532500f, -0.26286500f, 0.0000000f)), glm::normalize(glm::vec3(0.42532500f, -0.26286500f, 0.0000000f))));
	icosahedron.push_back(Vertex(glm::normalize(glm::vec3(-0.42532500f, -0.26286500f, 0.0000000f)), glm::normalize(glm::vec3(-0.42532500f, -0.26286500f, 0.0000000f))));

	// Create indices
	icosahedronIndices.push_back(0); icosahedronIndices.push_back(6);  icosahedronIndices.push_back(1);
	icosahedronIndices.push_back(0); icosahedronIndices.push_back(11); icosahedronIndices.push_back(6);
	icosahedronIndices.push_back(1); icosahedronIndices.push_back(4);  icosahedronIndices.push_back(0);
	icosahedronIndices.push_back(1); icosahedronIndices.push_back(8);  icosahedronIndices.push_back(4);
	icosahedronIndices.push_back(1); icosahedronIndices.push_back(10); icosahedronIndices.push_back(8);
	icosahedronIndices.push_back(2); icosahedronIndices.push_back(5);  icosahedronIndices.push_back(3);
	icosahedronIndices.push_back(2); icosahedronIndices.push_back(9);  icosahedronIndices.push_back(5);
	icosahedronIndices.push_back(2); icosahedronIndices.push_back(11); icosahedronIndices.push_back(9);
	icosahedronIndices.push_back(3); icosahedronIndices.push_back(7);  icosahedronIndices.push_back(2);
	icosahedronIndices.push_back(3); icosahedronIndices.push_back(10); icosahedronIndices.push_back(7);
	icosahedronIndices.push_back(4); icosahedronIndices.push_back(8);  icosahedronIndices.push_back(5);
	icosahedronIndices.push_back(4); icosahedronIndices.push_back(9);  icosahedronIndices.push_back(0);
	icosahedronIndices.push_back(5); icosahedronIndices.push_back(8);  icosahedronIndices.push_back(3);
	icosahedronIndices.push_back(5); icosahedronIndices.push_back(9);  icosahedronIndices.push_back(4);
	icosahedronIndices.push_back(6); icosahedronIndices.push_back(10); icosahedronIndices.push_back(1);
	icosahedronIndices.push_back(6); icosahedronIndices.push_back(11); icosahedronIndices.push_back(7);
	icosahedronIndices.push_back(7); icosahedronIndices.push_back(10); icosahedronIndices.push_back(6);
	icosahedronIndices.push_back(7); icosahedronIndices.push_back(11); icosahedronIndices.push_back(2);
	icosahedronIndices.push_back(8); icosahedronIndices.push_back(10); icosahedronIndices.push_back(3);
	icosahedronIndices.push_back(9); icosahedronIndices.push_back(11); icosahedronIndices.push_back(0);
}


void assignment3::createSphere(std::vector<Vertex> &sphere, std::vector<GLushort> &sphereIndices, int numTesselations) const
{
	createIcosahedron(sphere, sphereIndices);

	// Tesselate object numTesselations times until we have a round enough sphere
	for (int tesselation = 0; tesselation < numTesselations; ++tesselation)
	{
		// Get number of triangles at previous tesselation level
		size_t origTriangles = sphereIndices.size() / 3;

		std::cout << "Tesselation " << tesselation + 1 << " with " << origTriangles << " triangles" << std::endl;

		for (size_t t = 0; t < origTriangles; ++t)
		{
			// Get a new center point of the vertices
			size_t tpos = t * 3;

			GLushort v0Index = sphereIndices[tpos];
			GLushort v1Index = sphereIndices[tpos + 1];
			GLushort v2Index = sphereIndices[tpos + 2];
			const Vertex &v0 = sphere[v0Index];
			const Vertex &v1 = sphere[v1Index];
			const Vertex &v2 = sphere[v2Index];

			// Create new vertices
			Vertex v3(glm::normalize(v0.position + v1.position), glm::normalize(v0.position + v1.position));
			Vertex v4(glm::normalize(v1.position + v2.position), glm::normalize(v1.position + v2.position));
			Vertex v5(glm::normalize(v2.position + v0.position), glm::normalize(v2.position + v0.position));

			// Add a new vertex index for the center point
			GLuint v3Index = static_cast<GLuint>(sphere.size());
			sphere.push_back(v3);
			GLuint v4Index = static_cast<GLuint>(sphere.size());
			sphere.push_back(v4);
			GLuint v5Index = static_cast<GLuint>(sphere.size());
			sphere.push_back(v5);

			// Replace original triangle v0, v1, v2 with v0, v3, v5
			sphereIndices[tpos + 1] = v3Index;
			sphereIndices[tpos + 2] = v5Index;

			// Add triangle v3, v1, v4 to the model
			sphereIndices.push_back(v3Index); sphereIndices.push_back(v1Index); sphereIndices.push_back(v4Index);

			// Add triangle v3, v4, v5 to the model
			sphereIndices.push_back(v3Index); sphereIndices.push_back(v4Index); sphereIndices.push_back(v5Index);

			// Add triangle v5, v4, v2 to the model
			sphereIndices.push_back(v5Index); sphereIndices.push_back(v4Index); sphereIndices.push_back(v2Index);
		}
	}

	// Note that some (half) of new vertices are duplicates after tesselation as edges are shared with another triangle!
	std::cout << "Created sphere with " << sphere.size() << " vertices and " << sphereIndices.size() / 3 << " faces" << std::endl;

	// Verify that we don't have too many vertices (over 65535)
	assert(sphere.size() <= (GLushort)-1);
}

/**
* \brief Update mesh shading using Blinn-Phong model.
* We can create Gouraud-shading (vertex-based shading) this way with a point light source
* This ignores set vertex colors and overwrites them with given material colors
*/

assignment3::assignment3()
{
	// These OpenGL functions must be defined by the OpenGL (or through GLEW) for this example to work..
	assert(glBindBuffer != 0);
	assert(glBindVertexArray != 0);
	assert(glBufferData != 0);
	assert(glClear != 0);
	assert(glClearColor != 0);
	assert(glCullFace != 0);
	assert(glDepthFunc != 0);
	assert(glDeleteBuffers != 0);
	assert(glDeleteVertexArrays != 0);
	assert(glDisableVertexAttribArray != 0);
	assert(glDrawArrays != 0);
	assert(glEnable != 0);
	assert(glGenVertexArrays != 0);
	assert(glGenBuffers != 0);
	assert(glUseProgram != 0);
	assert(glUniformMatrix4fv != 0);
	assert(glVertexAttribPointer != 0);
	assert(glViewport != 0);
}

assignment3::~assignment3()
{
	// Clean up everything
	glUseProgram(0); // Shader state
	glDisableVertexAttribArray(shaderProgram_p1.getPositionAttribLocation()); 
	glDisableVertexAttribArray(shaderProgram_p1.getNormalAttribLocation());
	glDisableVertexAttribArray(shaderProgram_p2.getPositionAttribLocation());
	glDisableVertexAttribArray(shaderProgram_p2.getNormalAttribLocation());
	glDisableVertexAttribArray(shaderProgram_p3.getPositionAttribLocation());
	glDisableVertexAttribArray(shaderProgram_p3.getNormalAttribLocation());
	glDeleteBuffers(1, &ibo_p1);
	glDeleteBuffers(1, &vbo_p1);
	glDeleteVertexArrays(1, &vao_p1);
	glDeleteBuffers(1, &ibo_p2);
	glDeleteBuffers(1, &vbo_p2);
	glDeleteVertexArrays(1, &vao_p2);
	glDeleteBuffers(1, &ibo_p3);
	glDeleteBuffers(1, &vbo_p3);
	glDeleteVertexArrays(1, &vao_p3);
}

bool assignment3::init()
{


	//assignment 3: you may uncomment this part when shaders are ready
	if (!shaderProgram_p1.load("data/sample.vs", "data/sample.fs"))
		return false;
	if (!shaderProgram_p1.load("data/p1.vs", "data/p1.fs"))
		return false;
	if (!shaderProgram_p2.load("data/p2.vs", "data/p2.fs"))
		return false;
	if (!shaderProgram_p3.load("data/p3.vs", "data/p3.fs"))
		return false;
    

	// Create object geometry
	int numTesselations = 3;
	createSphere(sphere_p1, sphereIndices_p1, numTesselations);
	createSphere(sphere_p2, sphereIndices_p2, numTesselations);
	createSphere(sphere_p3, sphereIndices_p3, numTesselations);
	// Calculate model transformation

	//Initialize clear color for glClear()
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);

	// Allocate and assign a Vertex Array Object to our handle
	glGenVertexArrays(1, &vao_p1);
	glBindVertexArray(vao_p1);
	glGenBuffers(1, &ibo_p1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_p1);
	glGenBuffers(1, &vbo_p1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_p1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices_p1.size() * sizeof(GLushort), &sphereIndices_p1[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sphere_p1.size() * sizeof(struct Vertex), &sphere_p1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(shaderProgram_p1.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, position));
	glEnableVertexAttribArray(shaderProgram_p1.getPositionAttribLocation());
	glVertexAttribPointer(shaderProgram_p1.getNormalAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, normal));
	glEnableVertexAttribArray(shaderProgram_p1.getNormalAttribLocation());

	glGenVertexArrays(1, &vao_p2);
	glBindVertexArray(vao_p2);
	glGenBuffers(1, &ibo_p2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_p2);
	glGenBuffers(1, &vbo_p2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_p2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices_p2.size() * sizeof(GLushort), &sphereIndices_p2[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sphere_p2.size() * sizeof(struct Vertex), &sphere_p2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(shaderProgram_p2.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, position));
	glEnableVertexAttribArray(shaderProgram_p2.getPositionAttribLocation());
	glVertexAttribPointer(shaderProgram_p2.getNormalAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, normal));
	glEnableVertexAttribArray(shaderProgram_p2.getNormalAttribLocation());

	glGenVertexArrays(1, &vao_p3);
	glBindVertexArray(vao_p3);
	glGenBuffers(1, &ibo_p3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_p3);
	glGenBuffers(1, &vbo_p3);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_p3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices_p3.size() * sizeof(GLushort), &sphereIndices_p3[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sphere_p3.size() * sizeof(struct Vertex), &sphere_p3[0], GL_STATIC_DRAW);
	glVertexAttribPointer(shaderProgram_p3.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, position));
	glEnableVertexAttribArray(shaderProgram_p3.getPositionAttribLocation());
	glVertexAttribPointer(shaderProgram_p3.getNormalAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, normal));
	glEnableVertexAttribArray(shaderProgram_p3.getNormalAttribLocation());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	viewMat = glm::lookAt(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	return true;
}

void assignment3::resize(GLsizei width, GLsizei height)
{
	// Update OpenGL viewport to match window system's window size
	glViewport(0, 0, width, height);
	// Set up projection matrix and model matrix etc.
	float fovy = 45.0f;
	projectionMat = glm::perspective(fovy, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

void assignment3::update(float timestep)
{
	// Rotate object
	rotation += glm::two_pi<float>() * 0.1f * timestep;
}

// Render view
void assignment3::render()
{
	// Clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewMat = glm::lookAt(glm::vec3(0.0f, 1.f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm_ModelViewMatrix.push(glm::mat4());
	glm_ModelViewMatrix.top() = viewMat*glm_ModelViewMatrix.top();
	
	/*
	// Calculate model transformation
	glm::vec4 lightPos(0.0f, 0.0f, 3.0f, 1.0f);
	glm::vec4 object_color(0.1, 0.1, 0.1, 1.0);
	glUniform4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "ObjectColor"), 1, glm::value_ptr(object_color));
	glUseProgram(shaderProgram_p1.getShaderProgram());
	modelMat = glm::rotate(glm::mat4(), rotation, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 mvMat = viewMat * modelMat;
	glm::vec4 lightInViewPos = viewMat * modelMat * lightPos;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "mvmatrix"), 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "pmatrix"), 1, GL_FALSE, glm::value_ptr(projectionMat));
	glUniform4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "lightPosition"), 1, glm::value_ptr(lightInViewPos));
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphereIndices_p1.size()), GL_UNSIGNED_SHORT, 0);
	*/

	// Add the sun
	glm::vec4 lightPos(0.0f, 0.0f, 3.0f, 1.0f);

	glUseProgram(shaderProgram_p1.getShaderProgram());
	glm_ModelViewMatrix.top() = glm::translate(glm_ModelViewMatrix.top(), glm::vec3(x_move*.02, y_move*.02, 0.0));
	glm_ModelViewMatrix.top() = glm::translate(glm_ModelViewMatrix.top(), glm::vec3(0.0, 1.0, 0.0));
	glm_ModelViewMatrix.top() = glm::rotate(glm_ModelViewMatrix.top(), rotation, glm::vec3(0.0, 1.0, 0.0));
	glm_ModelViewMatrix.top() = glm::scale(glm_ModelViewMatrix.top(), glm::vec3(2.0, 2.0, 2.0));
	glm::mat4 mvMat = viewMat * glm_ModelViewMatrix.top();
	glm::vec4 lightInViewPos = viewMat * glm_ModelViewMatrix.top() * lightPos;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "mvmatrix"), 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "pmatrix"), 1, GL_FALSE, glm::value_ptr(projectionMat));
	glUniform4fv(glGetUniformLocation(shaderProgram_p1.getShaderProgram(), "lightPosition"), 1, glm::value_ptr(lightInViewPos));
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphereIndices_p1.size()), GL_UNSIGNED_SHORT, 0);
	
	glm_ModelViewMatrix.push(glm_ModelViewMatrix.top());


	// Add the Earth
	glUseProgram(shaderProgram_p2.getShaderProgram());
	glm_ModelViewMatrix.top() = glm::translate(glm_ModelViewMatrix.top(), glm::vec3(3.0, 0.0, 0.0));
	glm_ModelViewMatrix.top() = glm::rotate(glm_ModelViewMatrix.top(), rotation, glm::vec3(0.0, 0.5, 0.0));
	glm_ModelViewMatrix.top() = glm::scale(glm_ModelViewMatrix.top(), glm::vec3(0.5, 0.5, 0.5));
	mvMat = viewMat * glm_ModelViewMatrix.top();
	viewMat * glm_ModelViewMatrix.top() * lightPos;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p2.getShaderProgram(), "mvmatrix"), 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p2.getShaderProgram(), "pmatrix"), 1, GL_FALSE, glm::value_ptr(projectionMat));
	glUniform4fv(glGetUniformLocation(shaderProgram_p2.getShaderProgram(), "lightPosition"), 1, glm::value_ptr(lightInViewPos));
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphereIndices_p2.size()), GL_UNSIGNED_SHORT, 0);
	glm_ModelViewMatrix.push(glm_ModelViewMatrix.top());
	
	
	// Add the Moon
	glUseProgram(shaderProgram_p3.getShaderProgram());
	glm_ModelViewMatrix.top() = glm::translate(glm_ModelViewMatrix.top(), glm::vec3(2.0, 0.0, 0.0));
	glm_ModelViewMatrix.top() = glm::rotate(glm_ModelViewMatrix.top(), rotation, glm::vec3(0.0, 0.5, 0.0));
	glm_ModelViewMatrix.top() = glm::scale(glm_ModelViewMatrix.top(), glm::vec3(0.3, 0.3, 0.3));
	modelMat = glm::rotate(glm::mat4(), rotation, glm::vec3(0.0, 1.0, 0.0));
	mvMat = viewMat * glm_ModelViewMatrix.top();
	viewMat * glm_ModelViewMatrix.top() * lightPos;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p3.getShaderProgram(), "mvmatrix"), 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_p3.getShaderProgram(), "pmatrix"), 1, GL_FALSE, glm::value_ptr(projectionMat));
	glUniform4fv(glGetUniformLocation(shaderProgram_p3.getShaderProgram(), "lightPosition"), 1, glm::value_ptr(lightInViewPos));
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphereIndices_p3.size()), GL_UNSIGNED_SHORT, 0);
	

}

bool assignment3::handleEvent(const SDL_Event &e)
{
	// Put any event handling code here.
	// Window-resizing is handled in event loop already.
	char key;
	// Sample event handling code. Some of this could be useful in your own scene's handleEvent() function
	switch (e.type)
	{
		// Keyboard key pressed down (scancode is the physical key on keyboard, keycode is the symbolic key meaning)
	case SDL_KEYDOWN:
		break;
		//Mouse button pressed
	case SDL_MOUSEBUTTONDOWN:
		// See https://wiki.libsdl.org/SDL_MouseButtonEvent
		// Note: Mouse wheel has its own event
		{std::cout << "Mouse button down at : " << e.button.x << ", " << e.button.y << " button: ";
		switch (e.button.button)
		{
			case SDL_BUTTON_LEFT:
				mouse_downward_x = e.button.x;
				mouse_downward_y = e.button.y;
				break;
			case SDL_BUTTON_RIGHT:
				break;
			case SDL_BUTTON_MIDDLE:
				break;
			case SDL_BUTTON_X1:
				break;
			case SDL_BUTTON_X2:
				break;
			default:
				std::cout << "Unknown (" << e.button.button << ")";
		}
		}
		break;
	// Mouse button released
	case SDL_MOUSEBUTTONUP:
		mouse_upward_x = e.button.x;
		mouse_upward_y = e.button.y;
		x_move += mouse_upward_x - mouse_downward_x;
		y_move += mouse_downward_y - mouse_upward_y;
		break;
	}
	// Return false if you want to stop the program
	return true;
}

