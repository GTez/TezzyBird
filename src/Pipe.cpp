#include "Pipe.hpp"

Pipe::Pipe(std::string textureName, sf::Vector2f position, float spread) :
	m_position(position),
	m_positionTop(sf::Vector2f(position.x, position.y + spread))
	{
		m_texture.loadFromFile(textureName.c_str());
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(m_position);
		m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y /2);
		m_spriteTop.setTexture(m_texture);
		m_spriteTop.scale(sf::Vector2f(1, -1));
		m_spriteTop.setPosition(m_positionTop);
		m_spriteTop.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y /2);
		m_passed = false;
	}
Pipe::~Pipe(){}

void Pipe::update(float dt, float distance){
	m_position.x -= dt * distance;
	m_positionTop.x -= dt * distance;
	// printf("%f %f \n", m_position.x, m_position.y);
	m_sprite.setPosition(m_position);
	m_spriteTop.setPosition(m_positionTop);
}

sf::Sprite Pipe::getSprite() {
	return m_sprite;
}
sf::Sprite Pipe::getTopSprite() {
	return m_spriteTop;
}

sf::Vector2f Pipe::getPosition() {
	return m_position;
}

bool Pipe::GetPassed() {
	return m_passed;
}

void Pipe::SetPassed(bool _passed) {
	m_passed = _passed;
}