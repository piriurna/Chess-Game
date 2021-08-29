#pragma once
#include <SFML/Graphics.hpp>

class PieceManager {

	sf::Texture whitePawnTexture;
	sf::Texture whiteBishopTexture;
	sf::Texture whiteKnightTexture;
	sf::Texture whiteRookTexture;
	sf::Texture whiteQueenTexture;
	sf::Texture whiteKingTexture;


	void initialize();

private:
    enum : int { NUM_OF_PIECES = 6 };
    enum : int { NUM_OF_COLORS = 2 };
    typedef sf::Sprite ChessPieceList[NUM_OF_PIECES][NUM_OF_COLORS];
    //holds the chess piece images

    static ChessPieceList imageList;
public:
	enum PieceType : int { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
	enum PieceDirection : int { UP = 1, DOWN = -1 };
	enum PieceColor : int { WHITE_PIECE_ID, BLACK_PIECE_ID };

    static const sf::Sprite& getChessPieceImage(PieceType type, PieceColor color);
};
