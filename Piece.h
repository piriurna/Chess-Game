#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class Team {
	WHITE, BLACK
};

class Piece {
public:
	enum class Type { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

	enum class MoveType { NORMAL, CASTLE, EN_PASSANT, INIT, CAPTURE, PROMOTION };

	struct PossibleMove {
		int XCoord, YCoord;
		MoveType moveType;
	};

	struct MoveOffset {
		int DX, DY;
		MoveType moveType;
	};

	enum class Direction {
		UP, DOWN, LEFT, RIGHT, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT
	};

	struct Intersection {
		Piece* intersectedPiece;
		Direction intersectionDirection;
	};

	struct ActualPosition {
		int X, Y;
	};

	struct Move {
		int from, to;
		MoveType moveType;
	};

	void loadSprite(const sf::Texture& texture);
	sf::Sprite getSprite();

	bool equals(Piece& other);

	std::vector<Piece::PossibleMove> getPossibleMoves();

	//This instead of being virtual it can actually calculate in piece, seeing that it only needs to check if it's in bounds
	virtual void calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) = 0;


	virtual std::vector<Piece::PossibleMove> getPossibleMovesForList(std::vector <Piece::MoveOffset> moveOffsets, std::vector<std::unique_ptr<Piece>>& pieces);

	virtual std::vector<Piece::PossibleMove> getCleanPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);

	virtual void sayMyName() = 0;

	bool pushMove(int newPosition, std::vector<std::unique_ptr<Piece>>& pieces);


	bool intersectsWith(Piece* other);

	int getPosition();
	sf::Vector2f getPositionVector();
	void setPosition(int newPosition);

	void setHasMoved(bool);
	bool getHasMoved() const;

	void killPiece();
	bool getIsAlive() const;


	Team getTeam() const;

	Type getType() const;

	std::vector<Move> getMovesList() const;

	Move getMoveAt(int position);

	Piece::Move* getLastMove();


	//TODO: I'd like to make an static abstract function that where called in GAME so when i needed to create a piece from fen i just needed to send the piece string and depending the string i'd return the corresponding piece type object
	//idk if that's even possible though
	 
	//virtual Piece getpieceFromString(std::string type) = 0;

protected:
	sf::Sprite pieceSprite;
	int position;
	Type type;
	Team team;
	std::vector<PossibleMove> possibleMoves;

	bool isAlive = true;
	bool hasMoved = false;

	std::vector<Move> movesList;
};


