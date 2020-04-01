#include "CoordinateConverter.h"

sf::Vector2f CoordinateConverter::GL_TO_PIXEL(sf::Vector2f t_glPos)
{
	float xPos = (t_glPos.x + CAMERA_Z_VALUE) * SCREEN_WIDTH / static_cast<float>(CAMERA_Z_VALUE * 2);
	float yPos = (t_glPos.y + CAMERA_Z_VALUE) * SCREEN_HEIGHT / static_cast<float>(CAMERA_Z_VALUE * 2);

	return { xPos, yPos };
}

///////////////////////////////////////////////////////////////

sf::Vector2f CoordinateConverter::PIXEL_TO_GL(sf::Vector2f t_pixelPos)
{
	float xPos = (t_pixelPos.x / (SCREEN_WIDTH / static_cast<float>(CAMERA_Z_VALUE * 2))) + CAMERA_Z_VALUE;
	float yPos = (t_pixelPos.y / (SCREEN_HEIGHT / static_cast<float>(CAMERA_Z_VALUE * 2))) + CAMERA_Z_VALUE;

	return { xPos, yPos };
}