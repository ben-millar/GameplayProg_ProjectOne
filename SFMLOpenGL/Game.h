#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>

#include "GLOBALS.h"

#include "CollisionHandler.h"
#include "Debug.h"
#include "GameObjectPool.h"
#include "Cube.h"
#include "Clouds.h"
#include "Lightning.h"

class Game
{
public:

	// *** Default Constructor/Destructor ***
	Game();
	~Game();

	// *** Methods ***

	/// <summary>
	/// @brief Main run method, handles calling of all other methods
	/// </summary>
	void run();

private:

	// *** Methods ***

	void initialise();

	void setupShader(GLenum t_type, GLuint& t_shaderID, std::string t_filePath);

	std::string loadShader(std::string t_filePath);

	GLuint compileShader(GLenum t_type, std::string& t_src);

	/// <summary>
	/// @brief Loads our background image in from a file
	/// </summary>
	void setupBackground();

	/// <summary>
	/// @brief Handles all incoming system/SFML events
	/// </summary>
	void processEvents();

	/// <summary>
	/// @brief Checks for collisions between lightning hit and game objects
	/// </summary>
	void checkCollisions(int xPos, int yPos);

	/// <summary>
	/// @brief Handles the update loop, called at 60FPS
	/// </summary>
	/// <param name="t_deltaTime">time in seconds since the last frame</param>
	void update(sf::Time t_deltaTime);

	/// <summary>
	/// @brief Translates and rotates our sf::view based on our screenShake variable
	/// </summary>
	void shakeScreen();

	/// <summary>
	/// @brief Handles the render loop; drawing and flipper framebuffer
	/// </summary>
	void render();

	/// <summary>
	/// @brief Renders a cube on-screen
	/// </summary>
	/// <param name="t_mvp">MVP of cube to draw</param>
	void renderCube(const GameObject& t_gameObject);

	// *** Objects ***
	sf::RenderWindow m_window;

	bool m_exitGame;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::RectangleShape m_lightningFlash;
	int m_frameCount{ 0 };
	bool m_drawFlash{ false };

	// SCREENSHAKE variables
	float m_screenShake{ 0.0f }; // scalar for screenshake, normalised to the range 0-1
	const float MAX_OFFSET = 50.0f; // max translational offset for screenshake
	const float MAX_ANGLE = 5.0f; // max rotational offset for screenshake

	Clouds* m_clouds;
	Lightning m_lightning;

	// How big of a blast zone our lightning hit produces
	const int LIGHTNING_RADIUS{ 80 };

	static const int NUM_CUBES{ 8 };

	// *** OpenGL Variables ***

	GLuint	vsid,		// Vertex Shader ID
			fsid,		// Fragment Shader ID
			progID,		// Program ID
			vao = 0,	// Vertex Array ID
			vbo,		// Vertex Buffer ID
			vib,		// Vertex Index Buffer
			to[1];		// Texture ID
	GLint	positionID,	// Position ID
			colorID,	// Color ID
			textureID,	// Texture ID
			uvID,		// UV ID
			mvpID,		// Model View Projection ID
			x_offsetID, // X offset ID
			y_offsetID,	// Y offset ID
			z_offsetID;	// Z offset ID

	GLenum	error;		// OpenGL Error Code


	//Please see .//Assets//Textures// for more textures
	const std::string filename = ".//ASSETS//TEXTURES//grass.png";

	int width;						// Width of texture
	int height;						// Height of texture
	int comp_count;					// Component of texture

	unsigned char* img_data;		// image data

	GameObjectPool m_objectPool;

	sf::Time m_cubeDelay{ sf::seconds(0.5f) };
	sf::Time m_timeSinceLastCube{ sf::Time::Zero };

	// Model View Projection
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 mvp;	
};
#endif