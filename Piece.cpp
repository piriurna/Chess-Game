#include "Piece.h"

Piece::Piece(sf::Texture& texture, int position) {
	loadSprite(texture);
	this->position = position
};

void Piece::loadSprite(const sf::Texture& texture) {
	this->pieceSprite.setTexture(texture);
}

sf::Sprite Piece::getSprite()
{
	return pieceSprite;
}

int Piece::getPosition() {
	return position;
}

sf::Vector2f Piece::getPositionVector() {
	int y = position / 8;
	int x = (position % 8) - 1;
	//when getting the module of the number it returns the position starting with 1, and 0 when it's the 8th file
	if (x < 0) x = 7;

	return sf::Vector2f(x, y);
}

void Piece::setPosition(int newPosition)
{
	this->position = newPosition;
}

bool Piece::equals(Piece& other) {
	return position == other.getPosition();
}