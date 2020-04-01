#include "CoordinateConverter.h"

sf::Vector2f CoordinateConverter::GL_TO_PIXEL(sf::Vector2f t_glPos)
{
	float xPos = (t_glPos.x + Z_VALUE) * SCREEN_WIDTH / static_cast<float>(Z_VALUE * 2);
	float yPos = (t_glPos.y + Z_VALUE) * SCREEN_HEIGHT / static_cast<float>(Z_VALUE * 2);

	return { xPos, yPos };
}

///////////////////////////////////////////////////////////////

sf::Vector2f CoordinateConverter::PIXEL_TO_GL(sf::Vector2f t_pixelPos)
{
	float xPos = (t_pixelPos.x / (SCREEN_WIDTH / static_cast<float>(Z_VALUE * 2))) + Z_VALUE;
	float yPos = (t_pixelPos.y / (SCREEN_HEIGHT / static_cast<float>(Z_VALUE * 2))) + Z_VALUE;

	return { xPos, yPos };
}