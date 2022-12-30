#pragma once

class FCountry
{
public:
	FCountry()
	{
	}

	FCountry(const FString& Tag, const FColor& Color): Tag(Tag), Color(Color)
	{
	}


	FString GetTag() const
	{
		return Tag;
	}

	FColor GetColor() const
	{
		return Color;
	}
	
private:
	FString Tag;
	FColor Color;
};
