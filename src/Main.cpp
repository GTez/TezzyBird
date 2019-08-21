#include <vector>
#include "Main.hpp"
#include "Bird.h"
#include "Pipe.h"

// Tuneables
const sf::Vector2f kBirdSpawnPosition = sf::Vector2f(50.0f, 256.0f);
const float kGravity = 15.0f;
const float kBirdMass = 70.0f;
const float kFlapPower = 300.0f;
const float kStamina = 1000.0f;
const float kRegenRate = 1500.0f;
const float kScrollRate = 75.0f;
const float kSpawnRate = 2.5f;
const float kPipeOpening = 150.0f;
const char* kBackgroundImagePath = "content/textures/background-day.png";
const char* kPipeImagePath = "content/textures/pipe-green.png";
const char* kStaticBirdImagePath = "content/textures/redbird-midflap.png";
const char* kGameOvertextImagePath = "content/textures/gameover.png";
const char* kMessageOverlayImagePath = "content/textures/message.png";
const char* kGroundImagePath = "content/textures/base.png";

// Fiunction Prototypes
void init();
void draw();
void inputHandler();
void mainLoopUpdate(float dt);
void spawnPipe();
bool checkCollision(sf::Sprite objOne, sf::Sprite objTwo);
void resetGame();
void movePipe(float dt, float distance);

// Global Object Declerations
sf::RenderWindow window(sf::VideoMode(288, 512), "Tezzy Bird!");
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Texture gameOverTexture;
sf::Sprite gameOverSprite;
sf::Texture messageOverlayTexture;
sf::Sprite messageOverlaySprite;
sf::Texture groundTexture;
sf::Sprite groundSprite;
std::vector<Pipe*> pipes;
Bird bird;
enum GameState { starting, paused, playing, gameover };
GameState gameState;
float secSinceLastSpawn = 0.0f;

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
		if (gameState == playing) {
			mainLoopUpdate(dt.asSeconds());
		}
		window.clear();
		draw();
		window.display();
	}

	return 0;
}

void init() {
	// Function to setup all the objects
	srand((int)time(0));
	gameState = starting;
	backgroundTexture.loadFromFile(kBackgroundImagePath);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	groundTexture.loadFromFile(kGroundImagePath);
	groundTexture.isRepeated();
	groundSprite.setTexture(groundTexture);
	groundSprite.setOrigin(groundTexture.getSize().x / 2, groundTexture.getSize().y / 2);
	groundSprite.setPosition(sf::Vector2f(144.0f, 460.0f));
	gameOverTexture.loadFromFile(kGameOvertextImagePath);
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setOrigin(gameOverTexture.getSize().x / 2, gameOverTexture.getSize().y / 2 );
	gameOverSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().x / 3));
	messageOverlayTexture.loadFromFile(kMessageOverlayImagePath);
	messageOverlaySprite.setTexture(messageOverlayTexture);
	messageOverlaySprite.setOrigin(messageOverlayTexture.getSize().x / 2, messageOverlayTexture.getSize().y / 2);
	messageOverlaySprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().x / 2));
	bird.init(kStaticBirdImagePath, kBirdSpawnPosition, kBirdMass, kGravity, kStamina, kRegenRate);
}

void draw() {
	// Function to handle the drawing of a frame
	window.draw(backgroundSprite);
	for (Pipe *pipe : pipes) {
		window.draw(pipe->getSprite());
		window.draw(pipe->getTopSprite());
	}
	window.draw(groundSprite);
	if (gameState == gameover) {
		window.draw(gameOverSprite);
	}
	if (gameState == starting) {
		window.draw(messageOverlaySprite);
	} else {
		window.draw(bird.getSprite());
	}
}

void inputHandler() {
	sf::Event m_event;
		while (window.pollEvent(m_event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (gameState == gameover || gameState == starting) {
					resetGame();
					gameState = playing;
				} else {
					bird.flap(kFlapPower);
				}
			}
			if (m_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
}

void mainLoopUpdate(float dt) {
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
			if ( checkCollision(bird.getSprite(), pipe->getSprite()) || checkCollision(bird.getSprite(), pipe->getTopSprite()) ) {
				printf("Game Over Man! \n");
				gameState = gameover;
			}
			if (pipe->getPosition().x < (-1.0f * pipe->getSprite().getTextureRect().width)) {
				pipes.erase(pipes.begin() + i);
				delete(pipe);

			}
		}
	}
	movePipe(dt, kScrollRate);
}

void spawnPipe() {
	// printf("Spawning a Pipe \n");
	// 550.0f bottom 360.0f top
	float offset = rand() % 190 + 360;
	// printf("Spawning Pipe with offset: %F", offset);
	sf::Vector2f pipeSpawnPos = sf::Vector2f(window.getSize().x + 25, offset);
	Pipe* pipe = new Pipe();
	pipe->init(kPipeImagePath, pipeSpawnPos, -1.0f * ( kPipeOpening + 320.0f ));
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
	bird.reset(kBirdSpawnPosition);
	for ( Pipe *pipe : pipes ) { // First delete the pipes
		delete(pipe);
	}
	pipes.clear();  // Then clear the Vector
	secSinceLastSpawn = 0.0f;
	spawnPipe();
}

void movePipe(float dt, float distance) {
	// This doesn't work right yet. Don't judge me. :)
	float m_spriteMove = -1 * dt * distance;
	groundSprite.move(m_spriteMove, 0);
}
