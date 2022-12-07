#pragma once

#include <string>
#include <string.h>
#include <unordered_map>
#include <fstream>
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Image.hpp"
#include "Province.h"
#include <iostream>


class World
{
public:
	World(std::string provinceDescriptionFile) {
		loadProvinces(provinceDescriptionFile);
	}

	const Province& getProvince(sf::Color color) {
		return _provinces[color.toInteger()];
	}


private:
	std::unordered_map<int, Province> _provinces;


	void loadProvinces(const std::string& provinceDescriptionFile) {
		std::fstream file(provinceDescriptionFile, std::ios_base::in);
		std::string tmp;

		while (std::getline(file, tmp)) {
			Province province = parseProvince(tmp);
			_provinces[province.color().toInteger()] = province;
		}

		file.close();
	}

	Province parseProvince(std::string& text) {
		int position = 0;

		sf::Color color;
		color.r = std::stoi(getNextValue(text, position));
		color.g = std::stoi(getNextValue(text, position));
		color.b = std::stoi(getNextValue(text, position));
		
		
		std::string name = getNextValue(text, position);

		sf::Color stateColor;
		stateColor.r = std::stoi(getNextValue(text, position));
		stateColor.g = std::stoi(getNextValue(text, position));
		stateColor.b = std::stoi(getNextValue(text, position));

		return Province(color, name, stateColor);
	}


	std::string getNextValue(std::string& text, int &position) {
		std::string result;
		for (; position < text.size(); ++position) {
			if (text[position] == ',') {
				++position;
				return result;
			}
			result += text[position];
		}
		return result;
	}

};

