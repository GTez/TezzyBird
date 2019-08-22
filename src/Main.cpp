#include <vector>
#include "Globals.hpp"
#include "Main.hpp"
#include "Game.hpp"

sf::RenderWindow window(sf::VideoMode(288, 512), "Tezzy Bird!");

int main()
{
	printf("Entering main()");
	sf::Clock m_clock;
	Game* m_game = nullptr;
	m_game = new Game();
	if (m_game != nullptr)
	{
		m_game->init(window);
		#ifdef SFML_SYSTEM_WINDOWS
			__windowsHelper.setIcon(window.getSystemHandle());
		#endif
		m_game->spawnPipe(window);
		while (window.isOpen())
		{
			sf::Time dt = m_clock.restart();
			m_game->inputHandler(window);
			// printf("The current Gamestate is : %i", );
			if (m_game->GetGameState() == 1) {
				m_game->mainLoopUpdate(dt.asSeconds(), window);
			}
			window.clear();
			m_game->draw(window);
			window.display();
		}
	}
	return 0;
}

