#ifndef TEZZYBIRD_GAME_HPP_
#define TEZZYBIRD_GAME_HPP_

class Bird; // Forward declaring the Bird class for later
class Pipe;
class ScoreBoard;

class Game {
	public:
		Game();
		~Game();

		// Handles rendering the objects to the Render Target
		void draw();

		// Handles the Keyboard and Mouse inputs
		void inputHandler();

		// Handles checking if a pipe should spawn, checking for collisions, and moving all the objects over.
		void mainLoopUpdate(float dt);

		// Spawns a Pipe Pair at a random height
		void spawnPipe();

		// Checks collision between two sf::Sprit objects
		bool checkCollision(sf::Sprite objOne, sf::Sprite objTwo);

		// Resets the game to it's default starting state
		void resetGame();

		// Handles moving the tile map of the ground plane.
		void MoveGround(float dt, float distance);

		// Returns what state the game is in.
		int GetGameState();
		sf::RenderWindow* GetRenderWindow();

	private:
		Bird* m_bird;
		ScoreBoard* m_scoreboard;
		sf::RenderWindow window;
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		sf::Texture gameOverTexture;
		sf::Sprite gameOverSprite;
		sf::Texture messageOverlayTexture;
		sf::Sprite messageOverlaySprite;
		sf::Texture groundTexture;
		sf::Sprite groundSpriteOne;
		sf::Sprite groundSpriteTwo;
		sf::SoundBuffer birdSplatSoundBuffer;
		sf::Sound birdSplatSound;
		std::vector<Pipe*> pipes;
		float secSinceLastSpawn;
		const char* kBackgroundImagePath = "content/textures/background-day.png";
		const char* kGameOvertextImagePath = "content/textures/gameover.png";
		const char* kMessageOverlayImagePath = "content/textures/message.png";
		const char* kGroundImagePath = "content/textures/base.png";
		const char* kPipeImagePath = "content/textures/pipe-green.png";
		const char* kStaticBirdImagePath = "content/textures/redbird-midflap.png";
		const char* kBirdSplatSoundPath = "content/audio/die.ogg";
		enum GameState { starting, playing, gameover };
		GameState gamestate;
		int score;
};

#endif // TEZZYBIRD_GAME_HPP_