#include <algorithm> // std::clamp
#include <fstream> // std::ifstream
#include <iostream>

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

	const glm::vec2 tileSz{Window::WIDTH / tilesX, Window::HEIGHT / 10};

	int tileStrength{};
	for (int i{}; i < tilesY; ++i) {
		for (int j{}; j < tilesX; ++j) {
			ifs >> tileStrength;

			// hardness == 0 is air 
			if (tileStrength <= 0) continue;
			tileStrength = std::clamp(tileStrength, GameTile::strengthMin, GameTile::strengthMax);

			const glm::vec2 tilePos{tileSz.x / 2 + tileSz.x * j, tileSz.y / 2 + tileSz.y * i};
			GameTile tile{tilePos, tileSz, tileStrength};
			_tiles.push_back(tile);
		}
	}
}

void GameLevel::draw(Renderer& renderer) const {
	for (const auto& tile : _tiles)
		renderer.draw(tile);
}
