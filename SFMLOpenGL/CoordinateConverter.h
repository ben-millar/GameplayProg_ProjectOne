#ifndef COORDINATE_H
#define COORDINATE_H

#include <SFML\Graphics.hpp>

class CoordinateConverter
{
public:
	/// <summary>
	/// @brief Convert GL coordinates to cartesian pixel coordinates
	/// </summary>
	/// <param name="t_glPos">Position in GL space</param>
	/// <returns>Position in SFML pixel space</returns>
	static sf::Vector2f GL_TO_PIXEL(sf::Vector2f t_glPos);

	/// <summary>
	/// @brief Convert pixel coordinates to GL space coordinates
	/// </summary>
	/// <param name="t_pixelPos">Position in SFML pixel space</param>
	/// <returns>Position in GL space</returns>
	static sf::Vector2f PIXEL_TO_GL(sf::Vector2f t_pixelPos);

private:

	const static int SCREEN_WIDTH{ 800 };
	const static int SCREEN_HEIGHT{ 600 };
	constexpr static float ASPECT_RATIO{ 4 / 3.0f };
	const static int Z_VALUE{ 20 };
};

#endif // !COORDINATE_H