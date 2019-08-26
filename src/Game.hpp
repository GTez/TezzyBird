class Bird; // Forward declaring the Bird class for later
class Pipe;

class Game {
	public:
		Game();
		~Game();
		void init();
		void draw();
		void inputHandler();
		void mainLoopUpdate(float dt);
		void spawnPipe();
		bool checkCollision(sf::Sprite objOne, sf::Sprite objTwo);
		void resetGame();
		void MoveGround(float dt, float distance);
		int GetGameState();
		sf::RenderWindow* GetRenderWindow();

	private:
		Bird* m_bird;
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
		std::vector<Pipe*> pipes;
		float secSinceLastSpawn;
		const char* kBackgroundImagePath = "content/textures/background-day.png";
		const char* kGameOvertextImagePath = "content/textures/gameover.png";
		const char* kMessageOverlayImagePath = "content/textures/message.png";
		const char* kGroundImagePath = "content/textures/base.png";
		const char* kPipeImagePath = "content/textures/pipe-green.png";
		const char* kStaticBirdImagePath = "content/textures/redbird-midflap.png";
		int gamestate;
};