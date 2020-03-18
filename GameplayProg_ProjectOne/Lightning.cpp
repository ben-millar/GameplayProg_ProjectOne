#include "Lightning.h"

Lightning::Lightning()
{
}

///////////////////////////////////////////////////////////////

void Lightning::strike(sf::Vector2i t_target)
{
	// Directly above the target point with an x-offset of +/- 50px
	sf::Vector2f OriginPos = { static_cast<float>(t_target.x + rand() % 100 - 50), 0.0f };

	// At what point along the line will we 'break'
	std::vector<float> breakPoint;

	// loop for 10-20 times
	for (int i = 0; i < 10 + rand() % 10; i++)
	{
		// random between 0.00f and 1.00f
		breakPoint.push_back((rand() % 100) / 100.0f);
	}

	// Sort in ascending order
	std::sort(breakPoint.begin(), breakPoint.end());

	// Start and end of each line segment
	sf::Vector2f start{ OriginPos };
	sf::Vector2f end;

	for (int i = 0; i < breakPoint.size() - 1; i++)
	{
		// Random x offset +/- 20px, y-value is our break point percentage along the total length
		sf::Vector2f end = { (start.x + rand() % 60) - 30, t_target.y * breakPoint.at(i)};

		m_bolt.append(sf::Vertex(start, sf::Color::Yellow));
		m_bolt.append(sf::Vertex(end, sf::Color::Yellow));

		start = end;
	}


	// Connect the end of the bolt to the strike target
	m_bolt.append(sf::Vertex(start, sf::Color::Yellow));
	m_bolt.append(sf::Vertex(static_cast<sf::Vector2f>(t_target), sf::Color::Yellow));
}

///////////////////////////////////////////////////////////////

void Lightning::update(sf::Time t_dT)
{
}

///////////////////////////////////////////////////////////////

void Lightning::draw(sf::RenderTarget& t_target, sf::RenderStates t_state) const
{
	t_target.draw(m_bolt);
}