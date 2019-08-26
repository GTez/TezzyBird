#include <vector>
#include "Globals.hpp"
#include "Main.hpp"
#include "Game.hpp"


int main()
{
	printf("Entering main() \n");
	sf::Clock m_clock;
	Game* m_game = nullptr;
	m_game = new Game();
	if (m_game != nullptr)
	{
		m_game->init();
		#ifdef SFML_SYSTEM_WINDOWS
			__windowsHelper.setIcon(window.getSystemHandle());
		#endif
		m_game->spawnPipe();
		while (m_game->GetRenderWindow()->isOpen())
		{
			sf::Time dt = m_clock.restart();
			m_game->inputHandler();
			// printf("The current Gamestate is : %i", );
			if (m_game->GetGameState() == 1) {
				m_game->mainLoopUpdate(dt.asSeconds());
			}
			m_game->GetRenderWindow()->clear();
			m_game->draw();
			m_game->GetRenderWindow()->display();
		}
	}
	return 0;
}

