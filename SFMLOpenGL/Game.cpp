#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32 }, "Taranis", sf::Style::Close },
	m_exitGame{ false }
{
	initialise();

	setupBackground();

	setupAudio();

	m_clouds = new Clouds(m_window.getSize().x, 80);

	m_lightningFlash.setSize({ SCREEN_WIDTH + 100.0f, SCREEN_HEIGHT + 100.0f });
	m_lightningFlash.setPosition(-50.0f, -50.0f);
	m_lightningFlash.setFillColor(sf::Color(255,255,255,192));
}

///////////////////////////////////////////////////////////////

Game::~Game()
{
	delete m_clouds;
}

///////////////////////////////////////////////////////////////

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // run at 60fps
	srand(static_cast<unsigned>(time(nullptr)));

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

///////////////////////////////////////////////////////////////

void Game::initialise()
{
	GLint isCompiled = 0;
	GLint isLinked = 0;

	if (!(!glewInit())) { DEBUG_MSG("glewInit() failed"); }

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// Vertex Array Buffer
	glGenBuffers(1, &vbo);		// Generate Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Generate Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	progID = glCreateProgram();

	// compile and link our shaders
	setupShader(GL_VERTEX_SHADER, vsid, "ASSETS\\SHADERS\\vert.shader");
	setupShader(GL_FRAGMENT_SHADER, fsid, "ASSETS\\SHADERS\\frag.shader");

	// Set image data
	// https://github.com/nothings/stb/blob/master/stb_image.h
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to[0]);
	glBindTexture(GL_TEXTURE_2D, to[0]);

	// Wrap around
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind to OpenGL
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,			// 2D Texture Image
		0,						// Mipmapping Level 
		GL_RGBA,				// GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,					// Width
		height,					// Height
		0,						// Border
		GL_RGBA,				// Bitmap
		GL_UNSIGNED_BYTE,		// Specifies Data type of image data
		img_data				// Image Data
	);

	// Projection Matrix 
	projection = glm::perspective(
		45.0f,			// Field of View 45 degrees
		ASPECT_RATIO,	// Aspect ratio
		5.0f,			// Display Range Min : 0.1f unit
		100.0f			// Display Range Max : 100.0f unit
	);

	// Camera Matrix
	view = lookAt(
		glm::vec3(0.0f, 4.0f, CAMERA_Z_VALUE),	// Camera (x,y,z), in World Space
		glm::vec3(0.0f, 0.0f, 0.0f),		// Camera looking at origin
		glm::vec3(0.0f, 0.5f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	glUseProgram(progID);
}

///////////////////////////////////////////////////////////////

void Game::setupShader(GLenum t_type, GLuint& t_shaderID, std::string t_filePath)
{
	std::string src{ loadShader(t_filePath) };

	t_shaderID = compileShader(t_type, src);

	glAttachShader(progID, t_shaderID);
	glLinkProgram(progID);
	glValidateProgram(progID);

	// Delete our shader now that it's linked to the program
	glDeleteShader(t_shaderID);
}

///////////////////////////////////////////////////////////////

std::string Game::loadShader(std::string t_filePath)
try
{
	std::ifstream stream(t_filePath);

	if (stream.is_open())
	{
		std::string line;
		std::stringstream ss;

		while (std::getline(stream, line))
		{
			ss << line << "\n";
		}

		return ss.str();
	}
	else
	{
		std::string msg{ "ERROR: unable to open shader source" };
		throw std::exception(msg.c_str());
	}
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
}

///////////////////////////////////////////////////////////////

GLuint Game::compileShader(GLenum t_type, std::string& t_src)
{
	unsigned int id = glCreateShader(t_type);
	const char* src = t_src.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Query the shader compilation status
	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	// If shader compilation failed
	if (!result)
	{
		// Get the length of our error message
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		// Stack allocate an array matching size of our message
		char* message = (char*)_malloca(length*sizeof(char));

		// Copy the error message into our array
		glGetShaderInfoLog(id, length, &length, message);

		DEBUG_MSG(message);
	}

	return id;
}

///////////////////////////////////////////////////////////////

void Game::setupAudio()
try
{
	if (!m_thunderAmbientMusic.openFromFile("ASSETS\\AUDIO\\thunder.wav"))
	{
		std::string msg{ "Error loading thunder sfx" };
		throw std::exception(msg.c_str());
	}
	else
	{
		m_thunderAmbientMusic.setLoop(true);
		m_thunderAmbientMusic.play();
	}
}
catch (const std::exception& e)
{
	DEBUG_MSG(e.what());
}

///////////////////////////////////////////////////////////////

void Game::setupBackground()
try
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\TEXTURES\\background.png"))
	{
		std::string msg{ "Error loading background texture" };
		throw std::exception(msg.c_str());
	}
	else
	{
		m_backgroundSprite.setTexture(m_backgroundTexture);

		// Overdraw slightly to allow for screenshake
		m_backgroundSprite.setScale(1.1f, 1.1f);
		m_backgroundSprite.setPosition(-20.0f, -20.0f);
	}
}
catch (const std::exception& e)
{
	DEBUG_MSG(e.what());
}

///////////////////////////////////////////////////////////////

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		if (sf::Event::MouseButtonPressed == event.type)
		{
			m_lightning.strike({ event.mouseButton.x, event.mouseButton.y });

			(m_screenShake < 0.25f) ? m_screenShake += 0.5f : m_screenShake = 0.75f;

			checkCollisions(event.mouseButton.x, event.mouseButton.y);

			m_drawFlash = true;
		}
	}
}

///////////////////////////////////////////////////////////////

void Game::checkCollisions(int xPos, int yPos)
{
	c2Circle lightningHit;

	lightningHit.p.x = xPos;
	lightningHit.p.y = yPos;

	lightningHit.r = LIGHTNING_RADIUS;

	for (GameObject* cube : m_objectPool.getActive())
	{
		if (CollisionHandler::isColliding(lightningHit, cube->getBounds()))
		{
			cube->hit();
		}
	}
}

///////////////////////////////////////////////////////////////

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	// Create new cubes
	m_timeSinceLastCube += t_deltaTime;
	if (m_timeSinceLastCube > m_cubeDelay)
	{
		m_objectPool.create();
		m_timeSinceLastCube = sf::Time::Zero;
	}

	// Update our weather effects
	m_lightning.update(t_deltaTime);
	m_clouds->update(t_deltaTime);

	// update our cubes
	for (GameObject* cube : m_objectPool.getActive()) 
	{ 
		// Update returns false if cube off-screen
		if (!cube->update())
		{
			// Do you expect me to talk?
			// No, Mr Cube. I expect you to die.
			m_objectPool.kill(*cube);
		}
	}

	// reduce trauma linearly to zero
	(m_screenShake > 0.0075f) ? m_screenShake -= 0.0075f : m_screenShake = 0.0f;

	shakeScreen();
}

///////////////////////////////////////////////////////////////

void Game::shakeScreen()
{
	sf::View view = m_window.getDefaultView();

	// translational shake
	float offsetX = (rand() % 201 - 100) / 100.0f;
	float offsetY = (rand() % 201 - 100) / 100.0f;

	// easing function along the square of our screenshake variable
	offsetX *= MAX_OFFSET * (m_screenShake * m_screenShake);
	offsetY *= MAX_OFFSET * (m_screenShake * m_screenShake);

	view.move(offsetX, offsetY);

	// rotational shake
	float angleOffset = (rand() % 201 - 100) / 100.0f;

	// easing function along the square of our screenshake variable
	angleOffset *= MAX_ANGLE * (m_screenShake * m_screenShake);

	view.setRotation(angleOffset);

	m_window.setView(view);
}

///////////////////////////////////////////////////////////////

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save OpenGL render state while we run an SFML draw
	m_window.pushGLStates();

	m_window.clear(sf::Color::Black);

	m_window.draw(m_backgroundSprite);
	m_window.draw(m_lightning);
	m_window.draw(*m_clouds);

	if (m_drawFlash)
	{
		m_window.draw(m_lightningFlash);
		
		m_frameCount++;

		if (m_frameCount >= 5)
		{
			m_drawFlash = false;
			m_frameCount = 0;
		}
	}

	// Restore our OpenGL render state
	m_window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	// Draw each cube on-screen
	for (GameObject* cube : m_objectPool.getActive()) { renderCube(*cube); }

	m_window.display();

	// Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

	// Unbind Buffers with 0 (Resets OpenGL States...important step)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset the Shader Program to Use
	glUseProgram(0);

	// Check for OpenGL Error code
	error = glGetError();
	if (error != GL_NO_ERROR) {
		//DEBUG_MSG(error);
	}
}

///////////////////////////////////////////////////////////////

void Game::renderCube(const GameObject& t_gameObject)
{
	// Find variables within the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	if (positionID < 0) { DEBUG_MSG("positionID not found"); }

	colorID = glGetAttribLocation(progID, "sv_color");
	if (colorID < 0) { DEBUG_MSG("colorID not found"); }

	uvID = glGetAttribLocation(progID, "sv_uv");
	if (uvID < 0) { DEBUG_MSG("uvID not found"); }

	textureID = glGetUniformLocation(progID, "f_texture");
	if (textureID < 0) { DEBUG_MSG("textureID not found"); }

	mvpID = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID < 0) { DEBUG_MSG("mvpID not found"); }

	x_offsetID = glGetUniformLocation(progID, "sv_x_offset");
	if (x_offsetID < 0) { DEBUG_MSG("x_offsetID not found"); }

	y_offsetID = glGetUniformLocation(progID, "sv_y_offset");
	if (y_offsetID < 0) { DEBUG_MSG("y_offsetID not found"); }

	z_offsetID = glGetUniformLocation(progID, "sv_z_offset");
	if (z_offsetID < 0) { DEBUG_MSG("z_offsetID not found"); };

	// VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// update MVP with current objects model
	mvp = projection * view * t_gameObject.getModel();

	// Send transformation to shader mvp uniform [0][0] is start of array
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	// Set Active Texture .... 32 GL_TEXTURE0 .... GL_TEXTURE31
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0); // 0 .... 31

	// Set the X, Y and Z offset (this allows for multiple cubes via different shaders)
	// Experiment with these values to change screen positions
	glUniform1f(x_offsetID, t_gameObject.xOffset());
	glUniform1f(y_offsetID, t_gameObject.yOffset());
	glUniform1f(z_offsetID, t_gameObject.zOffset());

	// Set pointers for each parameter (with appropriate starting positions)
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));

	// Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	// Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);
}