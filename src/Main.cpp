#include "Definitions.h"
#include "Main.hpp"
#include "Bird.h"

// Tuneables
sf::Vector2f BIRD_SPAWN_POS = sf::Vector2f(50, 256);
// const float GRAVITY = 15.0f;
// const float BIRD_MASS = 70.0f;
// const float FLAP_POWER = 300.0f;
// const float STAMINA = 1000.0f;
// const float REGEN_RATE = 1500.0f;
// const float SCROLL_RATE = 1.0f;

// Fiunction Prototypes
void init();
void draw();
void inputHandler();
void update(float dt);

// Global Object Declerations
sf::RenderWindow window(sf::VideoMode(288, 512), "Tezzy Bird!");
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
Bird bird;
bool gameover = true;
int counter = 0;

int main()
{
	sf::Clock clock;
	printf("Hello World!\n");
	init();
	#ifdef SFML_SYSTEM_WINDOWS
		__windowsHelper.setIcon(window.getSystemHandle());
	#endif

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		inputHandler();
		update(dt.asSeconds());
		window.clear();
		draw();
		window.display();
	}

	return 0;
}

void init() {
	// Function to setup all the objects
	backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	bird.init("content/textures/redbird-midflap.png", BIRD_SPAWN_POS, BIRD_MASS, GRAVITY, STAMINA, REGEN_RATE);
}

void draw() {
	// Function to handle the drawing of a frame
	window.draw(backgroundSprite);
	window.draw(bird.getSprite());

}

void inputHandler() {
	sf::Event m_event;
		while (window.pollEvent(m_event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					bird.flap(FLAP_POWER);
			}
			if (m_event.type == sf::Event::Closed)
				window.close();
		}
}

void update(float dt) {
	// Move the bird
	counter++;
	bird.update(dt);

	if (counter > 500) {
		counter = 0;
		printf("Velocity: %f - Stamina: %f \n", bird.getVelocity(), bird.getStamina());
	}
}
