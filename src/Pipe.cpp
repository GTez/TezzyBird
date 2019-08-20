#include "Pipe.h"

Pipe::Pipe(){}
Pipe::~Pipe(){}

void Pipe::init(std::string textureName, sf::Vector2f position){
	m_position = position;
	//printf("%f", m_position.x);
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y /2);
}
void Pipe::update(float dt, float distance){
	m_position.x -= dt * distance;
	// printf("%f %f \n", m_position.x, m_position.y);
	m_sprite.setPosition(m_position);
}

sf::Sprite Pipe::getSprite() {
	return m_sprite;
}

sf::Vector2f Pipe::getPosition() {
	return m_position;
}