/**
* \brief Example Scene 2 interface
*/
#ifndef ASSIGNMENT_2_H_
#define ASSIGNMENT_2_H_

#include <vector>                       // Standard vector template
#include <GL/glew.h>                    // OpenGL extension wrangler library
#include <SDL.h>                        // libSDL functionality
#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <glm/gtc/type_ptr.hpp>         // Needed for glm::value_ptr(x). You can use &x[0] instead of that.
#include "scene.h"                      // Abstract scene class
#include "shaderprogram.h"              // For shader management
#include "texture.h"
#include "atlbase.h"
#include "atlstr.h"
#include <ctime>

/**
 * \brief Draws a texture mapped flag
 */
class Assignment2 : public Scene
{
	struct Vertex
	{
		GLfloat position[3];
		GLfloat uv[2]; // Texture coordinates

		Vertex(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0, GLfloat u = 0.0f, GLfloat v = 0.0f)
		{
			position[0] = x;
			position[1] = y;
			position[2] = z;
			uv[0] = u;
			uv[1] = v;
		}
	};

	struct VertexColor
	{
		GLfloat position[3];
		GLfloat color[3]; // Texture coordinates

		VertexColor(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0, GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f)
		{
			position[0] = x;
			position[1] = y;
			position[2] = z;
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}
	};

	ShaderProgram shaderProgram;
	ShaderProgram shaderProgram2;
	glm::mat4 mvpMat;

	glm::mat4 projectionMat;
	glm::mat4 viewMat;
	glm::mat4 modelMat;

	// GLushort indices[num_indices] = {0,1,2,0,3,1};
	// Vertex Array Object, Vertex Buffer Object and Index Buffer Object handlers
	GLuint vao, vbo, ibo;

	////// Vertex Array Object for pole
	GLuint vap, vbp, ibp;

	float rotation; // Current rotation position
	std::vector<Vertex> flag; // Source data for our model
	std::vector<GLushort> flagIndices; // Index values for flag
	std::vector<VertexColor> pole;
	std::vector<GLushort> poleIndices;
	Texture *flagTexture;
	GLuint usedTextureUnit;

	void createFlag();
	void createPole();
public:
	Assignment2();
	virtual ~Assignment2();

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

	char transfer='o';
	float times;
	void OutputDebugPrintf(char* strOutput, ...)
	{
		char strBuffer[4096] = { 0 };
		va_list vlArgs;
		va_start(vlArgs, strOutput);
		_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutput, vlArgs);
		va_end(vlArgs);
		OutputDebugString(CA2W(strBuffer));
	}
};


#endif
