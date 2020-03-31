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

#include "Debug.h"
#include "GameObject.h"
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
	/// @brief Handles the update loop, called at 60FPS
	/// </summary>
	/// <param name="t_deltaTime">time in seconds since the last frame</param>
	void update(sf::Time t_deltaTime);

	/// <summary>
	/// @brief Animates our cube across the screen
	/// </summary>
	void moveCube();

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

	Clouds* m_clouds;
	Lightning m_lightning;

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
	const std::string filename = ".//ASSETS//TEXTURES//grid_wip.tga";

	int width;						// Width of texture
	int height;						// Height of texture
	int comp_count;					// Component of texture

	unsigned char* img_data;		// image data

	GameObject m_gameObject[NUM_CUBES];

	// Model View Projection
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 mvp;	

	const float GROUND_POS{ (-10.0f)};
	const float SCREEN_START{ -20.0f };
	const float SCREEN_END{ 20.0f };
	sf::Vector2f m_velocity{ 0.1f,0.0f };

	// SINE CODE

	int m_angle{ 0 };
	float m_sine;

};
#endif