#pragma once
#include <SFML/Graphics.hpp>;
#include "Piece.h";

class TextureManager {



private:
	sf::Texture whitePawnTexture;
	sf::Texture whiteBishopTexture;
	sf::Texture whiteKnightTexture;
	sf::Texture whiteRookTexture;
	sf::Texture whiteQueenTexture;
	sf::Texture whiteKingTexture;

	sf::Texture blackPawnTexture;
	sf::Texture blackBishopTexture;
	sf::Texture blackKnightTexture;
	sf::Texture blackRookTexture;
	sf::Texture blackQueenTexture;
	sf::Texture blackKingTexture;



	void initialize();
    enum : int { NUM_OF_PIECES = 6 };
    enum : int { NUM_OF_COLORS = 2 };
    typedef sf::Texture* ChessPieceList[NUM_OF_PIECES][NUM_OF_COLORS];
    //holds the chess piece images

    ChessPieceList imageList;

public:
	TextureManager();
	enum PieceDirection : int { UP = 1, DOWN = -1 };

    const sf::Texture* getChessPieceTexture(Piece::Type type, Team color);
};
