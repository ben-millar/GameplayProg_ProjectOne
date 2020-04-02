#include "GameObject.h"

///////////////////////////////////////////////////////////////

GameObject::GameObject()
{
	// Start our sin generator at a random angle
	m_angle = rand() % 360;
}

///////////////////////////////////////////////////////////////

void GameObject::init()
{
	m_model = glm::translate(glm::mat4(1.0f), glm::vec3{ 0.0f, GROUND_POS, 0.0f });
	m_modelPos = m_model;

	m_offset = { SCREEN_START, 0.0f, 0.0f };
	m_velocity = { 0.1f,0.0f,0.0f };

	m_currentState = State::WALKING;

	m_active = true;
}

///////////////////////////////////////////////////////////////

bool GameObject::update()
{
	updateSine();

	switch (m_currentState)
	{
	case State::WALKING:
		return walk();
		break;
	case State::EXPLODING:
		return explode();
		break;
	default:
		break;
	}
	
	return true;
}

///////////////////////////////////////////////////////////////

c2AABB GameObject::getBounds()
{
	// Update our bounding box before returning it
	sf::Vector2f minPixPos{ CoordinateConverter::GL_TO_PIXEL({ m_offset.x, 13.0f }) };
	sf::Vector2f maxPixPos{ CoordinateConverter::GL_TO_PIXEL({ m_offset.x + 2, 17.0f }) };

	m_boundingBox.min.x = minPixPos.x;
	m_boundingBox.min.y = minPixPos.y;

	m_boundingBox.max.x = maxPixPos.x;
	m_boundingBox.max.y = maxPixPos.y;

	return m_boundingBox;
}

///////////////////////////////////////////////////////////////

#include <iostream>

void GameObject::hit()
{
	std::cout << "I'm hit!" << std::endl;
	
	// Between -0.25 and 0.25
	float xVel = (rand() % 51 - 25) / 100.0f;

	// Between 0.75 and 1.0
	float yVel = (rand() % 25 + 76) / 100.0f;

	// Between 0.1 and 0.35
	float zVel = (rand() % 26 + 10) / 100.0f;

	m_velocity = { xVel, yVel, zVel };

	m_currentState = State::EXPLODING;
}

///////////////////////////////////////////////////////////////

void GameObject::updateSine()
{
	// Increase angle for sine wave
	m_angle += 6;

	// Sine wave generation
	m_sine = sinf(m_angle * (3.14159 / 180.0f));

	// Second sine wave 90 degrees out of phase
	m_sine90off = sinf((m_angle + 90) * (3.14159 / 180.0f));
}

///////////////////////////////////////////////////////////////

bool GameObject::walk()
{
	if (m_offset.x < SCREEN_END)
	{
		m_offset += m_velocity;
	}
	else
	{
		// We've left the screen
		return false;
	}

	m_model = glm::rotate(m_modelPos, (m_sine / 3.0f) - 0.2f, glm::vec3{ 1.0f, 0.0f, 0.0f }); // rotate through the sine value
	m_model = glm::translate(m_model, glm::vec3{ 0.0f, glm::abs(m_sine90off / 2.0f), 0.0f }); // set y-value to abs value of sine

	return true;
}

///////////////////////////////////////////////////////////////

bool GameObject::explode()
{
	m_offset += m_velocity;
	m_velocity.y -= GRAVITY;

	// Return false if below the ground position, plus a buffer of 5
	return (m_offset.y > GROUND_POS - 5.0f);
}

///////////////////////////////////////////////////////////////