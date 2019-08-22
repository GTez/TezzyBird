class Bird; // Forward declaring the Bird class for later
class Pipe;

class Game {
	public:
		Game();
		~Game();
		void init(sf::RenderWindow &_window);
		void draw(sf::RenderWindow &window);
		void inputHandler(sf::RenderWindow &window);
		void mainLoopUpdate(float dt, sf::RenderWindow &window);
		void spawnPipe(sf::RenderWindow &window);
		bool checkCollision(sf::Sprite objOne, sf::Sprite objTwo);
		void resetGame(sf::RenderWindow &window);
		void movePipe(float dt, float distance);
		int GetGameState();

	private:
		Bird* m_bird;
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		sf::Texture gameOverTexture;
		sf::Sprite gameOverSprite;
		sf::Texture messageOverlayTexture;
		sf::Sprite messageOverlaySprite;
		sf::Texture groundTexture;
		sf::Sprite groundSprite;
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