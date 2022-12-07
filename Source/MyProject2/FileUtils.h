#pragma once

class FFileUtils
{
public:
	static std::string ReadNextValue(const std::string& Text, int& Position)
	{
		std::string Result;
		for (; Position < Text.size(); ++Position)
		{
			if (Text[Position] == ',')
			{
				++Position;
				return Result;
			}
			Result += Text[Position];
		}
		return Result;
	}
};
