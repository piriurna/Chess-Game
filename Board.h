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

	void printPieces(sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& pieces);

	Piece* getPieceInPosition(int x, int y, std::vector<std::unique_ptr<Piece>>& pieces);

	int getTileForCoordinate(int x, int y);

	void highlightPosibleMoves(Piece& piece, std::vector<std::unique_ptr<Piece>>* pieceList, sf::RenderWindow* window);

	//--- GETTERS AND SETTERS
	int getNRows();
	void setNRows(int nRows);

	int getNColumns();
	void setNColumns(int nColumns);

	int getTileSize();
	void setTileSize(int newTileSize);

};
