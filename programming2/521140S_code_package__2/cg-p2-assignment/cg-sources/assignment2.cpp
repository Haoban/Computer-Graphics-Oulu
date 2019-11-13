/**
* \brief Example Scene 2 implementation
* \file
*/
#include <cassert>
#include "assignment2.h"

/**
 * \brief Create cube with texture coordinates and face indices.
 */
void Assignment2::createFlag()
{
	flag.clear();
	flagIndices.clear();
	
	float gridSize = 0.2f;
	int n = 0;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			flag.push_back(Vertex(gridSize * x, gridSize * y, 0.0f, x / 10.0f, y / 5.0f));
			flag.push_back(Vertex(gridSize * (x + 1), gridSize * y, 0.0f, (x + 1) / 10.0f, y / 5.0f));
			flag.push_back(Vertex(gridSize * (x + 1), gridSize * (y + 1), 0.0f, (x + 1) / 10.0f, (y + 1) / 5.0f));
			flag.push_back(Vertex(gridSize * x, gridSize * (y + 1), 0.0f, x / 10.0f, (y + 1) / 5.0f));

			flagIndices.push_back(n); flagIndices.push_back(n + 1); flagIndices.push_back(n + 2);
			flagIndices.push_back(n); flagIndices.push_back(n + 2); flagIndices.push_back(n + 3);

			n += 4;
		}
	}
}


void Assignment2::createPole()
{
	pole.clear();
	poleIndices.clear();

	pole.push_back(VertexColor(-0.2f, -2.0f, 0.0f, 1.0f, 1.0f, 0.5f));
	pole.push_back(VertexColor(0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 0.5f));
	pole.push_back(VertexColor(0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f));
	pole.push_back(VertexColor(-0.2f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f));

	poleIndices.push_back(0); poleIndices.push_back(1); poleIndices.push_back(2);

	poleIndices.push_back(0); poleIndices.push_back(2); poleIndices.push_back(3);
	/*vertex
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			pole.push_back(VertexColor(gridSize * x, gridSize * y, 0.0f, x / 10.0f, y / 5.0f, (x + y) / 15.0f));

			n += 4;
		}
	}
	*/
}

Assignment2::Assignment2() :
	flagTexture(0)
{
	// These must be defined by the OpenGL (or through GLEW) for this example to work..
	assert(glUseProgram != 0);
	assert(glClearColor != 0);
	assert(glEnable != 0);
	assert(glDepthFunc != 0);
	assert(glDisableVertexAttribArray != 0);
	assert(glDeleteBuffers != 0);
	assert(glDeleteVertexArrays != 0);
	assert(glGenVertexArrays != 0);
	assert(glBindVertexArray != 0);
	assert(glGenBuffers != 0);
	assert(glBindBuffer != 0);
	assert(glBufferData != 0);
	assert(glVertexAttribPointer != 0);
}

Assignment2::~Assignment2()
{
	// Clean up everything
	glUseProgram(0); // Shader state
	glDisableVertexAttribArray(shaderProgram.getPositionAttribLocation()); // VBO state
	glDisableVertexAttribArray(shaderProgram.getTexture0AttribLocation());
	glDeleteBuffers(1, &ibo); // Allocated index data
	glDeleteBuffers(1, &vbo); // Allocated vertex data
	glDeleteVertexArrays(1, &vao); // Allocated object data


	//Add information about pole
	glUseProgram(0); // Shader state
	glDisableVertexAttribArray(shaderProgram2.getPositionAttribLocation()); // VBO state
	glDisableVertexAttribArray(shaderProgram2.getTexture0AttribLocation());
	glDeleteBuffers(1, &ibp); // Allocated index data
	glDeleteBuffers(1, &vbp); // Allocated vertex data
	glDeleteVertexArrays(1, &vap); // Allocated object data

	if (flagTexture)
		delete flagTexture;
}

bool Assignment2::init()
{
	// Load shader program used in this example
	if (!shaderProgram.load("data/flag.vs", "data/flag.fs"))
		return false;

	// Create cube geometry
	createFlag();

	// Load cube texture
	flagTexture = new Texture("data/flag-texture.png");
	/*
	// Add a transparent horizontal line
	for (unsigned int x = 0; x < flagTexture->getWidth(); ++x)
		flagTexture->setPixel(x, 150, 0, 255, 0, 0);
	flagTexture->updateGLTexture();
	*/
	// Something failed?
	if (flagTexture->getTextureId() == 0)
		return false;
	std::cout << "Loaded flag texture as texture " << flagTexture->getTextureId() << std::endl;

	// Use shader program to render everything
	glUseProgram(shaderProgram.getShaderProgram());

	// Get uniform location for the shader's texture sampler
	GLint uniform_flagShader_texture = glGetUniformLocation(shaderProgram.getShaderProgram(), "texture0");

	if (uniform_flagShader_texture < 0)
	{
		std::cerr << "Unable to locate uniform variable texture0 from the shader" << std::endl;
		return false;
	}
	std::cout << "texture0 uniform id: " << uniform_flagShader_texture << std::endl;

	// Welect what texture unit is used for
	usedTextureUnit = 0;
	glUniform1i(uniform_flagShader_texture, usedTextureUnit);

	//Initialize clear color for glClear()
	glClearColor(0.2f, 0.3f, 0.1f, 1.f);

	// Enable blending (slower but necessary for partially transparent objects)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Allocate and assign a Vertex Array Object to our handle
	glGenVertexArrays(1, &vao);

	// Bind our Vertex Array Object as the currently used object
	// VAO will hold the state of our IBO and VBO below. Also any
	// settings selected for these buffer objects will be part of the VAO state as well.
	glBindVertexArray(vao);

	// Create Index Buffer Object
	glGenBuffers(1, &ibo);

	// Bind our Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		
	// Store our index values in Index Buffer Object
	// GL_STATIC_DRAW means that we don't expect this buffer to change (It's a hint that it can be stored on GPU)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, flagIndices.size() * sizeof(GLushort), &flagIndices[0], GL_STATIC_DRAW);

	

	// Allocate and assign One Vertex Buffer Object to our handle
	glGenBuffers(1, &vbo);

	// Bind our VBO as being the active buffer and storing vertex attributes (coordinates + colors)
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Copy the vertex data from tetrahedron to our buffer
	// 12 * sizeof(GLfloat) is the size of the tetrahedrom array, since it contains 12 Vertex values
	// GL_STATIC_DRAW means that we don't expect this buffer to change (It's a hint that it can be stored on GPU)
	glBufferData(GL_ARRAY_BUFFER, flag.size() * sizeof (struct Vertex), &flag[0], GL_STATIC_DRAW);

	// Note: The following attribute indexes must match what is defined in shader (in shaderprogram.cpp) for glBindAttribLocation() calls!

	// Specify that our coordinate data is going into attribute index 0 (shaderProgram.getPositionAttribLocation()), and contains three doubles per vertex
	// Note stride = sizeof ( struct Vertex ) and pointer = ( const GLvoid* ) 0
	glVertexAttribPointer(shaderProgram.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof (struct Vertex), (const GLvoid*)offsetof(struct Vertex, position));

	// Enable attribute index 0 as being used
	glEnableVertexAttribArray(shaderProgram.getPositionAttribLocation());

	// Specify that our color data is going into attribute index 1 (shaderProgram.getColorAttribLocation()), and contains three floats per vertex
	// Note stride = sizeof ( struct Vertex ) and pointer = ( const GLvoid* ) ( 3 * sizeof ( GLdouble ) ) i.e. the size (in bytes)
	// occupied by the first attribute (position)
	glVertexAttribPointer(shaderProgram.getTexture0AttribLocation(), 2, GL_FLOAT, GL_FALSE, sizeof (struct Vertex), (const GLvoid*)offsetof(struct Vertex, uv));

	// Enable attribute index 1 as being used
	glEnableVertexAttribArray(shaderProgram.getTexture0AttribLocation()); // Bind our second VBO as being the active buffer and storing vertex attributes (colors)

	//********************************************************pole***********************************************************//

	createPole();

	if (!shaderProgram2.load("data/pole.vs", "data/pole.fs"))
		return false;

	glGenVertexArrays(1, &vap);

	glBindVertexArray(vap);

	glGenBuffers(1, &ibp);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibp);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, poleIndices.size() * sizeof(GLushort), &poleIndices[0], GL_STATIC_DRAW);
	// Allocate and assign One Vertex Buffer Object to our handle
	glGenBuffers(1, &vbp);

	glBindBuffer(GL_ARRAY_BUFFER, vbp);

	glBufferData(GL_ARRAY_BUFFER, pole.size() * sizeof(struct VertexColor), &pole[0], GL_STATIC_DRAW);

	glVertexAttribPointer(shaderProgram2.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexColor), (const GLvoid*)offsetof(struct VertexColor, position));

	glEnableVertexAttribArray(shaderProgram2.getPositionAttribLocation());

	glVertexAttribPointer(shaderProgram2.getColorAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexColor), (const GLvoid*)offsetof(struct VertexColor, color));

	glEnableVertexAttribArray(shaderProgram2.getColorAttribLocation()); // Bind our second VBO as being the active buffer and storing vertex attributes (colors)

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//********************************************************pole***********************************************************//



	// Reset object rotation
	rotation = 0;

	// Our generated VAO is now ready and enabled for use
	// We could disable by calling glBindVertexArray(0) if we want to work with multiple objects and not use created VAO at the moment.

	// Set up our view matrix that determines camera position in the scene
	// glm::lookAt replaces old GLU library functionality for creating a projection matrix
	viewMat = glm::lookAt(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return true;
}

void Assignment2::resize(GLsizei width, GLsizei height)
{
	// Update OpenGL viewport to match window system's window size
	glViewport(0, 0, width, height);

	// Set up projection matrix and model matrix etc.
	float fovy = 45.0f;
	projectionMat = glm::perspective(fovy, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

void Assignment2::update(float timestep)
{
	// Rotate object
	rotation += glm::two_pi<float>() * 0.1f * timestep;
	Uint32 nowTime = SDL_GetTicks();
	glUniform1f(glGetUniformLocation(shaderProgram.getShaderProgram(), "time"), nowTime*0.01f);
	switch (transfer)
	{
	case 'o':
		modelMat = glm::rotate(glm::mat4(), rotation, glm::vec3(0.0, 1.0, 0.0)); // Rotate object around y-axis
		viewMat = glm::lookAt(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'a': 
		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		break;
	case 'd':
		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case 'w':
		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		break;
	case 's':
		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		break;
	case 'e':
		viewMat = glm::lookAt(glm::vec3(-5.0f, 1.5f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		break;
	case 'r':
		viewMat = glm::lookAt(glm::vec3(5.0f, 1.5f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	}

}

// Render view
void Assignment2::render()
{
	// Clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// Calculate model transformation


	//********************************************************pole***********************************************************//
	glUseProgram(shaderProgram2.getShaderProgram());

	// Precalculate transformation matrix for the shader and use it
	mvpMat = projectionMat * viewMat * modelMat;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram2.getShaderProgram(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(mvpMat));

	//float colors[4] = { 1.0, 0.0 ,0.0, 1.0 };
	//glUniform4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "NewColor"), 1, colors);
	glBindVertexArray(vap);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(poleIndices.size()), GL_UNSIGNED_SHORT, 0);
	//********************************************************pole***********************************************************//


	// Select correct shader program for this object (we never selected anything else to replace that state after init())
	glUseProgram(shaderProgram.getShaderProgram());

	// Precalculate transformation matrix for the shader and use it
	mvpMat = projectionMat * viewMat * modelMat;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(mvpMat));

	//OutputDebugPrintf("Time is %f\n", times);



	// Turn on texture mapping on texture unit 0 and select our texture
	// It is redundant to set the same values all the time but texture settings are included here for clarity
	// glUniform1i(uniform_cubeShader_texture, usedTextureUnit); <- In init code
	glActiveTexture(GL_TEXTURE0 + usedTextureUnit); // Other textures are GL_TEXTURE0 + i (where i is the texture unit index up to GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)
	glBindTexture(GL_TEXTURE_2D, flagTexture->getTextureId());

	// For drawing the cube it needs to be bound using (we never bound anything else to replace that state after init())
	
	glBindVertexArray(vao);
	

	// Count is the number of elements in the array that will form triangles. It is not the number of triangles defined by the array.
	// When VBOs are in use and GL_ELEMENT_ARRAY_BUFFER is bound, the last parameter (pointer to data) is interpreted as an offset within IBO instead of
	// actual program memory address.
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(flagIndices.size()), GL_UNSIGNED_SHORT, 0);

}

bool Assignment2::handleEvent(const SDL_Event &e)
{
        // Put any event handling code here.
        // Window-resizing is handled in event loop already.
	SDL_Event event;
	event = e;
	char key;
	while (SDL_PollEvent(&event)) {
		switch (e.type)
		{
			// Program window closed etc.
			// Keyboard key pressed down (scancode is the physical key on keyboard, keycode is the symbolic key meaning)
		case SDL_KEYDOWN:
			key = e.key.keysym.sym;
			switch (key)
			{
			case 'a':
				// left translation
				transfer = 'a';
				OutputDebugPrintf("The A key was pressed!\n");
				break;
			case 'd':
				// right translation
				transfer = 'd';
				break;
			case 'w':
				// front move
				transfer = 'w';
				break;
			case 's':
				// back move
				transfer = 's';
				break;
			case 'e':
				// rotate the camera left
				transfer = 'e';
				break;
			case 'r':
				// rotate the camera left
				transfer = 'r';
				break;
			case 'o':
				// back move
				transfer = 'o';
				break;
			case SDL_QUIT:
				exit(0);
				return false;
			}
		}

	}
	// Return false if you want to stop the program
	return true;
}

