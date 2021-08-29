#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Piece.h"

class Board {
private:
	int nRows;
	int nColumns;
	int tileSize;
public:
	Board(int nRows, int nColumns, int tileSize);

	void printBoard(sf::RenderWindow& window, sf::Color darkTileColor, sf::Color lightTileColor);

	//todo: change to a vector of pieces when definition is done
	//Maybe print pieces in a PieceManager instead of the actual board
	void printPieces(sf::RenderWindow& window, std::vector<Piece&>& pieces);


	//--- GETTERS AND SETTERS
	int getNRows();
	void setNRows(int nRows);

	int getNColumns();
	void setNColumns(int nColumns);

	int getTileSize();
	void setTileSize(int newTileSize);

};
