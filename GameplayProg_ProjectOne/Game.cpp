#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Taranis", sf::Style::Close },
	m_exitGame{ false }
{
	m_clouds = new Clouds(m_window.getSize().x, 100);
}

///////////////////////////////////////////////////////////////

Game::~Game()
{
	delete m_clouds;
}

///////////////////////////////////////////////////////////////

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // run at 60fps
	srand(static_cast<unsigned>(time(nullptr)));

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

///////////////////////////////////////////////////////////////

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		if (sf::Event::MouseButtonPressed == event.type)
		{
			m_lightning.strike({ event.mouseButton.x, event.mouseButton.y });
		}
	}
}

///////////////////////////////////////////////////////////////

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_lightning.update(t_deltaTime);
	m_clouds->update(t_deltaTime);
}

///////////////////////////////////////////////////////////////

void Game::render()
{
	m_window.clear(sf::Color(32,32,32,255));

	m_window.draw(m_lightning);
	m_window.draw(*m_clouds);

	m_window.display();
}