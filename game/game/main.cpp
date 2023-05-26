#include <iostream>

#include "game.h"

int main(void)
{
	try {
		Game::init();
	}
	catch (std::exception &e) {
		std::cerr << "Exception occured: "
			  << e.what() << std::endl;
		return(-1);
	}

	try {
		Game::exec();
	}
	catch (std::exception &e) {
		std::cerr << "Exception occured: "
			  << e.what() << std::endl;
		return(-1);
	}

	return(0);
}
