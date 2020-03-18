#include "Lightning.h"

Lightning::Lightning()
{
}

///////////////////////////////////////////////////////////////

void Lightning::strike(sf::Vector2i t_target)
{
	// Create a new bolt
	Bolt bolt;

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

		bolt.segments.append(sf::Vertex(start, sf::Color::Yellow));
		bolt.segments.append(sf::Vertex(end, sf::Color::Yellow));

		start = end;
	}


	// Connect the end of the bolt to the strike target
	bolt.segments.append(sf::Vertex(start, sf::Color::Yellow));
	bolt.segments.append(sf::Vertex(static_cast<sf::Vector2f>(t_target), sf::Color::Yellow));

	// Restart clock
	bolt.timeAlive.restart();

	// Add it to our vector
	m_bolts.push_back(bolt);
}

///////////////////////////////////////////////////////////////

void Lightning::update(sf::Time t_dT)
{
	if (!m_bolts.empty())
	{
		for (std::vector<Bolt>::iterator i = m_bolts.begin(); i < m_bolts.end(); i++)
		{
			if (m_bolts[i - m_bolts.begin()].timeAlive.getElapsedTime() > sf::seconds(1.f))
			{
				m_bolts.erase(i);
				break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////

void Lightning::draw(sf::RenderTarget& t_target, sf::RenderStates t_state) const
{
	for (auto& b : m_bolts)
	{
		t_target.draw(b.segments);
	}
}