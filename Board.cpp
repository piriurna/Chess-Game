#include "Board.h"

Board::Board(int nRows, int nColumns, int tileSize) {
	this->nRows = nRows;
	this->nColumns = nColumns;
	this->tileSize = tileSize;
}


void Board::printBoard(sf::RenderWindow& window, sf::Color darkTileColor, sf::Color lightTileColor) {
	setTileSize(window.getSize().x);

	for (int rank = 0; rank < nRows; rank++) {
		for (int file = 0; file < nColumns; file++) {
			bool blackTile = (rank + file) % 2 == 0;
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			tile.setFillColor(blackTile ? darkTileColor : lightTileColor);
			tile.setPosition(file * tileSize, rank * tileSize);
			window.draw(tile);
		}
	}
}

void Board::printPieces(sf::RenderWindow& window, std::vector<Piece&>& pieces)
{
	for (int i = 0; i < pieces.size(); i++) {
		window.draw(pieces.at(i).getSprite());
	}
}

//-- GETTERS AND SETTERS

int Board::getNRows() {
	return Board::nRows;
}

void Board::setNRows(int other) {
	this->nRows = other;
}

int Board::getNColumns() {
	return Board::nColumns;
}

void Board::setNColumns(int other) {
	this->nRows = other;
}

int Board::getTileSize()
{
	return 0;
}

void Board::setTileSize(int newTileSize)
{
}
