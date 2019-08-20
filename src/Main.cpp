#include <vector>
#include "Main.hpp"
#include "Bird.h"
#include "Pipe.h"

// Tuneables
sf::Vector2f BIRD_SPAWN_POS = sf::Vector2f(50.0f, 256.0f);
const float kGravity = 15.0f;
const float kBirdMass = 70.0f;
const float kFlapPower = 300.0f;
const float kStamina = 1000.0f;
const float kRegenRate = 1500.0f;
const float kScrollRate = 75.0f;
const float kSpawnRate = 2.5f;
const char* kBackgroundImagePath = "content/textures/background-day.png";
const char* kPipeImagePath = "content/textures/pipe-green.png";
const char* kStaticBirdImagePath = "content/textures/redbird-midflap.png";

// Fiunction Prototypes
void init();
void draw();
void inputHandler();
void update(float dt);
void spawnPipe();
bool checkCollision(sf::Sprite objOne, sf::Sprite objTwo);
void resetGame();

// Global Object Declerations
sf::RenderWindow window(sf::VideoMode(288, 512), "Tezzy Bird!");
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
std::vector<Pipe*> pipes;
Bird bird;
bool gameover = true;
float secSinceLastSpawn = 0.0f;

// Debug stuff
int counter = 0;

int main()
{
	sf::Clock clock;
	printf("Hello World!\n");
	init();
	#ifdef SFML_SYSTEM_WINDOWS
		__windowsHelper.setIcon(window.getSystemHandle());
	#endif
	spawnPipe();

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		inputHandler();
		if (!gameover) {
			update(dt.asSeconds());
		}
		window.clear();
		draw();
		window.display();
	}

	return 0;
}

void init() {
	// Function to setup all the objects
	backgroundTexture.loadFromFile(kBackgroundImagePath);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	bird.init(kStaticBirdImagePath, BIRD_SPAWN_POS, kBirdMass, kGravity, kStamina, kRegenRate);
}

void draw() {
	// Function to handle the drawing of a frame
	window.draw(backgroundSprite);
	for (Pipe *pipe : pipes) {
		window.draw(pipe->getSprite());
	}
	window.draw(bird.getSprite());

}

void inputHandler() {
	sf::Event m_event;
		while (window.pollEvent(m_event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (gameover) {
					resetGame();
					gameover = false;
				} else {
					bird.flap(kFlapPower);
				}
			}
			if (m_event.type == sf::Event::Closed)
				window.close();
		}
}

void update(float dt) {
	// Move the bird
	counter++;
	// Move the bird
	bird.update(dt);

	// Handle Spawning
	secSinceLastSpawn += dt;
	if (secSinceLastSpawn >= kSpawnRate) {
		spawnPipe();
		secSinceLastSpawn = 0.0f;
	}
	// Handle Collision and Out of bounds stuff
	if (pipes.size() > 0) {
		for ( unsigned int i = 0; i < pipes.size(); i++ ) {
			Pipe* pipe = pipes[i];
			pipe->update(dt, kScrollRate);
			if ( checkCollision(bird.getSprite(), pipe->getSprite())) {
				printf("Game Over Man!");
				gameover = true;
			}
			if (pipe->getPosition().x < (-1.0f * pipe->getSprite().getTextureRect().width)) {
				pipes.erase(pipes.begin() + i);
				delete(pipe);

			}
		}
	}
}

void spawnPipe() {
	// printf("Spawning a Pipe \n");
	sf::Vector2f pipeSpawnPos = sf::Vector2f(window.getSize().x + 25, 400.0f);
	Pipe* pipe = new Pipe();
	pipe->init(kPipeImagePath, pipeSpawnPos);
	pipes.push_back(pipe);
}

bool checkCollision(sf::Sprite objOne, sf::Sprite objTwo) {
	sf::FloatRect collisionBoundsOne = objOne.getGlobalBounds();
	sf::FloatRect collisionBoundsTwo = objTwo.getGlobalBounds();
	if (collisionBoundsOne.intersects(collisionBoundsTwo)) {
		return true;
	}
	return false;
}

void resetGame() {
	bird.setPosition(BIRD_SPAWN_POS);
	bird.reset();
	for ( Pipe *pipe : pipes ) {
		delete(pipe);
	}
	pipes.clear();
	secSinceLastSpawn = 0.0f;
	spawnPipe();
}