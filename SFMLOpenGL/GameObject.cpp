#include "GameObject.h"

GameObject::GameObject()
{
	sf::Vector2f minPixPos{ CoordinateConverter::GL_TO_PIXEL({ m_xOffset, 10.0f }) };
	sf::Vector2f maxPixPos{ CoordinateConverter::GL_TO_PIXEL({ m_xOffset + 1, 11.0f }) };

	m_boundingBox.min.x = minPixPos.x;
	m_boundingBox.min.y = minPixPos.y;

	m_boundingBox.max.x = maxPixPos.x;
	m_boundingBox.max.y = maxPixPos.y;
}

///////////////////////////////////////////////////////////////

c2AABB GameObject::getBounds()
{
	// Update our bounding box before returning it
	sf::Vector2f minPixPos{ CoordinateConverter::GL_TO_PIXEL({ m_xOffset, 10.0f }) };
	sf::Vector2f maxPixPos{ CoordinateConverter::GL_TO_PIXEL({ m_xOffset + 1, 11.0f }) };

	m_boundingBox.min.x = minPixPos.x;
	m_boundingBox.min.y = minPixPos.y;

	m_boundingBox.max.x = maxPixPos.x;
	m_boundingBox.max.y = maxPixPos.y;

	return m_boundingBox;
}
