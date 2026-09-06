#include <iostream>

#include "Breakout.h"

int main() {
	try {
		Breakout app{};
		app.run();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::exit(EXIT_SUCCESS);
	}
}