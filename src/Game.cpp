#include "Game.hpp"
#include "Bird.hpp"
#include "Pipe.hpp"
#include "ScoreBoard.hpp"
#include "Globals.inc"

Game::Game() :  // Colon used for initializing the variable to a null pointer
	m_bird(nullptr),
	m_scoreboard(nullptr),
	window(sf::VideoMode(288, 512), "Tezzy Bird!")
{
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
	birdSplatSoundBuffer.loadFromFile(kBirdSplatSoundPath);
	birdSplatSound.setBuffer(birdSplatSoundBuffer);
	m_bird = new Bird(kStaticBirdImagePath, sf::Vector2f(kBirdSpawnX, kBirdSpawnY), kBirdMass, kGravity, kStamina, kRegenRate);
	m_scoreboard = new ScoreBoard();
	gamestate = starting; // 0 starting 1 playing 2 gameover
	score = 0;
}

Game::~Game()
{
	if (m_bird != nullptr) {
		delete(m_bird); // We delete it because we made a new Bird in the init()
	}
	if (m_scoreboard != nullptr) {
		delete(m_scoreboard);
	}

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
				if (gamestate == gameover || gamestate == starting) {
					resetGame();
 					gamestate = playing;
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
	float _bird_x_pos = m_bird->getPosition().x;
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
			// Update the score
			if (pipe->getPosition().x < _bird_x_pos && pipe->GetPassed() == false) {
				pipe->SetPassed(true);
				score += 5;
				m_scoreboard->SetScore(score);
				// printf("The Game Score is: %i \n", score);
			}
			// Move the pipe
			pipe->update(dt, kScrollRate);
			// Check collisions
			if ( checkCollision(m_bird->getSprite(), pipe->getSprite()) || checkCollision(m_bird->getSprite(), pipe->getTopSprite()) ||
				checkCollision(m_bird->getSprite(), groundSpriteOne) || checkCollision(m_bird->getSprite(), groundSpriteTwo)) {
				birdSplatSound.play();
				gamestate = gameover;
			}
			// Clean up Old Pipes
			if (pipe->getPosition().x < (0 - pipe->getSprite().getTextureRect().width)) {
				// printf("Cleaning up pipe - Total pipes: %lu \n", pipes.size());
				pipes.erase(pipes.begin() + i);
				delete(pipe);
			}
		}
	}
	// Move the ground
	MoveGround(dt, kScrollRate);
}

void Game::spawnPipe() {
	// printf("Spawning a Pipe \n");
	// 550.0f bottom 360.0f top
	float offset = rand() % 190 + 360;
	// printf("Spawning Pipe with offset: %F", offset);
	sf::Vector2f pipeSpawnPos = sf::Vector2f(window.getSize().x + 25, offset);
	const float _spread = 0.0f - ( kPipeOpening + 320.0f ); // 320 is the magic offset for the image
	Pipe* pipe = new Pipe(kPipeImagePath, pipeSpawnPos, _spread);
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
	if (m_bird != nullptr)
	{
		m_bird->reset(sf::Vector2f(kBirdSpawnX, kBirdSpawnY));
	}
	for ( Pipe *pipe : pipes )
	{ // First delete the pipes
		delete(pipe);
	}
	pipes.clear();  // Then clear the Vector
	secSinceLastSpawn = 0.0f;
	spawnPipe();
	// groundSpriteOne.setPosition(sf::Vector2f(144.0f, kGroundHeight));
	// groundSpriteTwo.setPosition(sf::Vector2f(144.0f + groundTexture.getSize().x, kGroundHeight)); // Offset from the original
	score = 0;
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
	// printf("Groud Plane X Loc: %f \n", groundSpriteOne.getPosition().x);
}

int Game::GetGameState()
{
	return gamestate;
}

sf::RenderWindow* Game::GetRenderWindow() {
	return &window;
}