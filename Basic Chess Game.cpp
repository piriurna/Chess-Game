#include <SFML/Graphics.hpp>;
#include "Board.h"
#include "Player.h"
using namespace sf;

// This is where our game starts from
int main()
{

	int sw = 800;
	int sh = 800;

	int boardSize = sh;
	// Create a video mode object
	VideoMode vm(sw, sh);

	// Create and open a window for the game
	RenderWindow window(vm, "Chess");
	

	Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if(event.type == Event::MouseButtonPressed){
				//TODO: Select the tile or piece. When a piece is already selected move it		
			}
			else if (event.type == Event::Resized) {
				//TODO: recalculate the tile size and sprite sizes
			}
		}
	
	}


	return 0;
};


