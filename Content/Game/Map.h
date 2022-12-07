#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Point.h"
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <queue>
#include <iostream>



class Map: public sf::Sprite
{

private:
	Point relativePosition;
	int scale = 1;

	const int MAX_SCALE = 1000;
	const int MIN_SCALE = 1;
	const sf::Color SELECT_COLOR = sf::Color(0, 0, 255, 150);

	std::vector<Point> old;
	sf::Color oldColor;

	sf::Image mapImage;
	sf::Texture mapTexture;
	sf::Image _provinceImage;

	std::vector<Point> moves = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

	std::vector<Point> getPixelsWithSameColorInBorders(int x, int y, sf::Image& image) {
		sf::Color color = image.getPixel(x, y);

		std::queue<Point> queue;
		std::set<Point> visited;
		std::vector<Point> points;

		queue.push({ x, y });

		while (!queue.empty()) {
			Point current = queue.front();
			queue.pop();

			if (visited.count(current)) continue;
			if (image.getPixel(current.x, current.y) != color) continue;

			visited.insert(current);
			points.push_back(current);

			for (auto move : moves) {
				Point to = current + move;
				if (to.x >= 0 && to.y >= 0 && to.x < image.getSize().x && to.y < image.getSize().y) {
					queue.push(to);
				}
			}
		}

		return points;
	}

	int getLocalX(int x) {
		return (x - relativePosition.x) / scale;
	}

	int getLocalY(int y) {
		return (y - relativePosition.y) / scale;
	}

	const int _height = 617;
	const int _width = 1357;
public: 
	
	void moveVertivaly(int offset) {
		if (getPosition().y + offset <= 0 && getPosition().y + offset + mapImage.getSize().y * scale >= _height) {
			relativePosition.y += offset;
			move(0, offset);
		}
	}

	void moveHorizontaly(int offset) {
		if (getPosition().x + offset <= 0 && getPosition().x + offset + mapImage.getSize().x * scale >= _width) {
			relativePosition.x += offset;
			move(offset, 0);
		}
	}

	void addScale(int scaleDelta) {

		scale = std::max(MIN_SCALE, std::min(scale + scaleDelta, MAX_SCALE));		
		setScale(scale, scale);
		

		if (getPosition().y + mapImage.getSize().y * scale < _height) {
			int height = mapImage.getSize().y;
			moveVertivaly(- height * scaleDelta);
		}

		if (getPosition().x + mapImage.getSize().x * scale < _width) {
			int width = mapImage.getSize().x;
			moveHorizontaly(-width * scaleDelta);
		}

		if (scale == 1) {
			setPosition(0, 0);
			relativePosition.x = 0;
			relativePosition.y = 0;
		}
	}

	sf::Color getProvinceColor(int x, int y) {
		return _provinceImage.getPixel(getLocalX(x), getLocalY(y));
	}

	void select(int x, int y) {
		int localX = getLocalX(x), localY = getLocalY(y);

		std::cout << "Input: " << x << " " << y << std::endl;
		std::cout << "Local: " << localX << " " << localY << std::endl;

		sf::Color color = mapImage.getPixel(localX, localY);
		std::cout << "Color: " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << std::endl;

		if (color == sf::Color(255, 255, 255)) return;

		for (auto point : old) {
			mapImage.setPixel(point.x, point.y, oldColor);
		}

		oldColor = mapImage.getPixel(localX, localY);

		old = getPixelsWithSameColorInBorders(localX, localY, mapImage);

		for (auto point : old) {
			mapImage.setPixel(point.x, point.y, SELECT_COLOR);
		}

		if (!mapTexture.loadFromImage(mapImage, sf::IntRect(0, 0, 1357, 617))) {
			std::cout << "Faild" << std::endl;
		}

		setTexture(mapTexture);
	}

	Map(std::string mapImagePath, std::string provinceImageFilepath) : Sprite() {
		relativePosition.x = 0;
		relativePosition.y = 0;

		if (!_provinceImage.loadFromFile(provinceImageFilepath)) {
			std::cout << "Can't load color map" << std::endl;
			exit(1);
		}

		if (!mapImage.loadFromFile(mapImagePath)) {
			std::cout << "Can't load map" << std::endl;
		}

		for (int i = 0; i < mapImage.getSize().x; ++i) {
			for (int j = 0; j < mapImage.getSize().y; ++j) {
				sf::Color color = mapImage.getPixel(i, j);
				color.a = 150;
				mapImage.setPixel(i, j, color);
			}
		}

		if (!mapTexture.loadFromImage(mapImage)) {
			std::cout << "Can't create texture" << std::endl;
		}

		setTexture(mapTexture);
	}
	
};

