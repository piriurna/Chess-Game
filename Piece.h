#pragma once
#include <SFML/Graphics.hpp>

class Piece {
	Piece(sf::Texture& texture, int position);
private:
	sf::Sprite pieceSprite;
	int position;
	int type;
public:
	void loadSprite(const sf::Texture& texture);
	sf::Sprite getSprite();


	int getPosition();
	sf::Vector2f getPositionVector();
	void setPosition(int newPosition);


	bool equals(Piece& other);
};