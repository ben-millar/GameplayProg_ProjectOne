#include "CoordinateConverter.h"

sf::Vector2f CoordinateConverter::GL_TO_PIXEL(sf::Vector2f t_glPos)
{
	// Normalise to the range 0 - 1
	float xPos = (t_glPos.x + CAMERA_Z_VALUE) / static_cast<float>(CAMERA_Z_VALUE * 2.0f);
	xPos *= SCREEN_WIDTH; // Apply scalar to screen width

	// Normalise to the range 0 - 1
	float yPos = (t_glPos.y + CAMERA_Z_VALUE) / static_cast<float>(CAMERA_Z_VALUE * 2.0f * ASPECT_RATIO);
	yPos *= SCREEN_HEIGHT; // Apply scalar to screen height
	yPos = SCREEN_HEIGHT - yPos; // Flip y-origin from bottom to top

	return { xPos, yPos };
}

///////////////////////////////////////////////////////////////

sf::Vector2f CoordinateConverter::PIXEL_TO_GL(sf::Vector2f t_pixelPos)
{
	float xPos = (t_pixelPos.x / (SCREEN_WIDTH / static_cast<float>(CAMERA_Z_VALUE * 2))) + CAMERA_Z_VALUE;
	float yPos = (t_pixelPos.y / (SCREEN_HEIGHT / static_cast<float>(CAMERA_Z_VALUE * 2))) + CAMERA_Z_VALUE;

	return { xPos, yPos };
}