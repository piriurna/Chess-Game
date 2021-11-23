#include "Board.h"

Board::Board(int nRows, int nColumns, int tileSize) {
	this->nRows = nRows;
	this->nColumns = nColumns;
	this->tileSize = tileSize;
};


void Board::printBoard(sf::RenderWindow& window, sf::Color darkTileColor, sf::Color lightTileColor) {
	setTileSize(window.getSize().x / nRows);

	for (int rank = 0; rank < nRows; rank++) {
		for (int file = 0; file < nColumns; file++) {
			bool blackTile = (rank + file) % 2 == 0;
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			tile.setFillColor(blackTile ? darkTileColor : lightTileColor);
			tile.setPosition(file * tileSize, rank * tileSize);
			window.draw(tile);
		}
	}
};

void Board::printPieces(sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& pieces)
{
	for (int i = 0; i < pieces.size(); i++) {
		Piece &currentPiece = *pieces.at(i);
		if (!currentPiece.getIsAlive()) continue;
		sf::Sprite sprite = currentPiece.getSprite();


		int x = currentPiece.getPosition() % 8;
		int y = currentPiece.getPosition() / 8;
		sprite.setPosition(x * tileSize, y * tileSize);
		sprite.setScale(0.43, 0.43);
		window.draw(sprite);
	}
};

typedef int Coordinate[2];
struct Bounds {
	Coordinate XBounds;
	Coordinate YBounds;
};

Piece* Board::getPieceInPosition(int x, int y, std::vector<std::unique_ptr<Piece>>& pieces) {
	for (int pIndex = 0; pIndex < pieces.size(); pIndex++) {
		Piece& currentPiece = *pieces.at(pIndex);
		Bounds pieceBounds = Bounds{
			{ (currentPiece.getPosition() % 8) * tileSize, (currentPiece.getPosition() % 8) * tileSize + tileSize }, //X BOUNDS
			{ (currentPiece.getPosition() / 8) * tileSize, (currentPiece.getPosition() / 8) * tileSize + tileSize } //Y BOUNDS
		};

		if (x > pieceBounds.XBounds[0] && x < pieceBounds.XBounds[1] &&
			y> pieceBounds.YBounds[0] && y < pieceBounds.YBounds[1] &&
			currentPiece.getIsAlive()) {
			printf("Selected piece: "); currentPiece.sayMyName();
			printf("\n");
			return &currentPiece;
		}
	}

	return nullptr;
}

int Board::getTileForCoordinate(int x, int y) {
	int tile = (y / tileSize) * nColumns + (x / tileSize);
	return tile;
}

void Board::highlightPosibleMoves(Piece& piece , std::vector<std::unique_ptr<Piece>>* pieceList, sf::RenderWindow* window) {
	piece.calcPossibleMoves(*pieceList);
	std::vector<Piece::PossibleMove> cleanPossibleMoves = piece.getCleanPossibleMoves(*pieceList);
	for (int moveIndex = 0; moveIndex < cleanPossibleMoves.size(); moveIndex++) {
		bool hasIntersected = false;
		Piece::PossibleMove possibleMove = cleanPossibleMoves.at(moveIndex);
		
		if (possibleMove.moveType == Piece::MoveType::CAPTURE) {
			sf::RectangleShape captureHighlight(sf::Vector2f(tileSize, tileSize));
			captureHighlight.setFillColor(sf::Color::Red);
			captureHighlight.setPosition(possibleMove.XCoord * tileSize, possibleMove.YCoord * tileSize);
			(*window).draw(captureHighlight);
		}
		else if (possibleMove.moveType == Piece::MoveType::CASTLE) {
			sf::RectangleShape castleHighlight(sf::Vector2f(tileSize, tileSize));
			castleHighlight.setFillColor(sf::Color::Green);
			castleHighlight.setPosition(possibleMove.XCoord * tileSize, possibleMove.YCoord * tileSize);
			(*window).draw(castleHighlight);
		}
		else if (possibleMove.moveType == Piece::MoveType::EN_PASSANT) {
			sf::RectangleShape enPassantHighlight(sf::Vector2f(tileSize, tileSize));
			enPassantHighlight.setFillColor(sf::Color::Magenta);
			enPassantHighlight.setPosition(possibleMove.XCoord * tileSize, possibleMove.YCoord * tileSize);
			(*window).draw(enPassantHighlight);
		}
		else {
			sf::RectangleShape moveHighlight(sf::Vector2f(tileSize, tileSize));
			moveHighlight.setFillColor(sf::Color::Blue);
			moveHighlight.setPosition(possibleMove.XCoord * tileSize, possibleMove.YCoord * tileSize);
			(*window).draw(moveHighlight);
		}
	}
	
	
}

//-- GETTERS AND SETTERS

int Board::getNRows() {
	return Board::nRows;
};

void Board::setNRows(int other) {
	this->nRows = other;
};

int Board::getNColumns() {
	return Board::nColumns;
};

void Board::setNColumns(int other) {
	this->nRows = other;
};

int Board::getTileSize()
{
	return this->tileSize;
};

void Board::setTileSize(int newTileSize)
{
	this->tileSize = newTileSize;
};
