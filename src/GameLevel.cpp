#include <algorithm> // std::clamp
#include <fstream> // std::ifstream

#include "GameLevel.h"
#include "Window.h"

GameLevel::GameLevel(std::string_view file) {
	std::ifstream ifs{file.data()};
	if (!ifs) throw std::runtime_error{"Error: GameLevel: Unable to load level!"};

	int tilesX{}; 
	int tilesY{};
	ifs >> tilesX >> tilesY;

	tilesX = std::clamp(tilesX, 3, 15);
	tilesY = std::clamp(tilesY, 2, 10);
	
	const glm::vec2 tileSz{Window::WIDTH / tilesX , 50};

	int tileHardness{};
	for (int i{}; i < tilesX; ++i) {
		for (int j{}; j < tilesY; ++j) {
			ifs >> tileHardness;

			// hardness == 0 is air 
			if (tileHardness <= 0) continue;
			tileHardness = std::clamp(tilesX, 1, 5);

			const auto tilePosX{(tileSz.x / 2) + tileSz.x * i};
			const auto tilePosY{(tileSz.y / 2) + tileSz.y * j};

			_tiles.push_back({ {tilePosX, tilePosY}, tileSz, {} });
		}
	}
}

void GameLevel::draw(Renderer& renderer) const {
	for (const auto& tile : _tiles)
		renderer.draw(tile);
}
