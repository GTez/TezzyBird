#include "Game.hpp"
#include "Bird.hpp"
#include "Pipe.hpp"
#include "Globals.hpp"

Game::Game() :  // Colon used for initializing the variable to a null pointer
	m_bird(nullptr),
	window(sf::VideoMode(288, 512), "Tezzy Bird!")
{
	gamestate = 0; // 0 starting 1 playing 2 gameover
}

Game::~Game()
{
	if (m_bird != nullptr)
	{
		delete(m_bird); // We delete it because we made a new Bird in the init()
	}
}

void Game::init() {
	// Function to setup all the objects
	srand((int)time(0));
	secSinceLastSpawn = 0.0;
	backgroundTexture.loadFromFile(kBackgroundImagePath);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	groundTexture.loadFromFile(kGroundImagePath);
	groundTexture.isRepeated();
	groundSpriteOne.setTexture(groundTexture);
	groundSpriteOne.setOrigin(groundTexture.getSize().x / 2, groundTexture.getSize().y / 2);
	groundSpriteOne.setPosition(sf::Vector2f(144.0f, kGroundHeight));
	groundSpriteTwo.setTexture(groundTexture);
	groundSpriteTwo.setOrigin(groundTexture.getSize().x / 2, groundTexture.getSize().y / 2);
	groundSpriteTwo.setPosition(sf::Vector2f(144.0f + groundTexture.getSize().x, kGroundHeight)); // Offset from the original
	gameOverTexture.loadFromFile(kGameOvertextImagePath);
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setOrigin(gameOverTexture.getSize().x / 2, gameOverTexture.getSize().y / 2 );
	gameOverSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().x / 3));
	messageOverlayTexture.loadFromFile(kMessageOverlayImagePath);
	messageOverlaySprite.setTexture(messageOverlayTexture);
	messageOverlaySprite.setOrigin(messageOverlayTexture.getSize().x / 2, messageOverlayTexture.getSize().y / 2);
	messageOverlaySprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().x / 2));
	m_bird = new Bird(kStaticBirdImagePath, sf::Vector2f(kBirdSpawnX, kBirdSpawnY), kBirdMass, kGravity, kStamina, kRegenRate);
}

void Game::draw() {
	// Function to handle the drawing of a frame
	window.draw(backgroundSprite);
	for (Pipe *pipe : pipes) {
		if (pipe != nullptr) {
			window.draw(pipe->getSprite());
			window.draw(pipe->getTopSprite());
		}

	}
	window.draw(groundSpriteOne);
	window.draw(groundSpriteTwo);
	if (gamestate == 2) {
		window.draw(gameOverSprite);
	}
	if (gamestate == 0) {
		window.draw(messageOverlaySprite);
	} else {
		window.draw(m_bird->getSprite());
	}
}

void Game::inputHandler() {
	sf::Event m_event;
		while (window.pollEvent(m_event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (gamestate == 2 || gamestate == 0) {
					resetGame();
 					gamestate = 1;
				} else {
					m_bird->flap(kFlapPower);
				}
			}
			if (m_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
}

void Game::mainLoopUpdate(float dt) {
	// Move the m_bird
	m_bird->update(dt);

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
			if ( checkCollision(m_bird->getSprite(), pipe->getSprite()) ||
				checkCollision(m_bird->getSprite(), pipe->getTopSprite()) ||
				checkCollision(m_bird->getSprite(), groundSpriteOne) ||
			 	checkCollision(m_bird->getSprite(), groundSpriteTwo)) {
				printf("Game Over Man! \n");
				gamestate = 2;
			}
			if (pipe->getPosition().x < (-1.0f * pipe->getSprite().getTextureRect().width)) {
				pipes.erase(pipes.begin() + i);
				delete(pipe);

			}
		}
	}
	MoveGround(dt, kScrollRate);
}

void Game::spawnPipe() {
	// printf("Spawning a Pipe \n");
	// 550.0f bottom 360.0f top
	float offset = rand() % 190 + 360;
	// printf("Spawning Pipe with offset: %F", offset);
	sf::Vector2f pipeSpawnPos = sf::Vector2f(window.getSize().x + 25, offset);
	Pipe* pipe = new Pipe();
	pipe->init(kPipeImagePath, pipeSpawnPos, -1.0f * ( kPipeOpening + 320.0f ));
	pipes.push_back(pipe);
}

bool Game::checkCollision(sf::Sprite objOne, sf::Sprite objTwo) {
	sf::FloatRect collisionBoundsOne = objOne.getGlobalBounds();
	sf::FloatRect collisionBoundsTwo = objTwo.getGlobalBounds();
	if (collisionBoundsOne.intersects(collisionBoundsTwo)) {
		return true;
	}
	return false;
}

void Game::resetGame() {
	if (m_bird != nullptr) {
		m_bird->reset(sf::Vector2f(kBirdSpawnX, kBirdSpawnY));
	}
	for ( Pipe *pipe : pipes ) { // First delete the pipes
		delete(pipe);
	}
	pipes.clear();  // Then clear the Vector
	secSinceLastSpawn = 0.0f;
	spawnPipe();
	groundSpriteOne.setPosition(sf::Vector2f(144.0f, kGroundHeight));
	groundSpriteTwo.setPosition(sf::Vector2f(144.0f + groundTexture.getSize().x, kGroundHeight)); // Offset from the original

}

void Game::MoveGround(float dt, float distance)
{
	float _x_transform = -1 * dt * distance;
	sf::Vector2f _translate = sf::Vector2f(_x_transform, 0);
	if (groundSpriteOne.getGlobalBounds().left < 0 - groundSpriteOne.getLocalBounds().width) {
		groundSpriteOne.setPosition(sf::Vector2f(groundSpriteTwo.getGlobalBounds().left + groundSpriteTwo.getGlobalBounds().width + 144.0f, kGroundHeight));
	} else {
		groundSpriteOne.move(_translate);
	}

	if (groundSpriteTwo.getGlobalBounds().left < 0 - groundSpriteTwo.getLocalBounds().width) {
		groundSpriteTwo.setPosition(sf::Vector2f(groundSpriteOne.getGlobalBounds().left + groundSpriteOne.getGlobalBounds().width + 144.0f, kGroundHeight));
	} else {
		groundSpriteTwo.move(_translate);
	}
	printf("Groud Plane X Loc: %f \n", groundSpriteOne.getPosition().x);
}

int Game::GetGameState()
{
	return gamestate;
}

sf::RenderWindow* Game::GetRenderWindow() {
	return &window;
}