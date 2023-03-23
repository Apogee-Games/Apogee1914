#include "Administration/Instances/Ideology.h"

void UIdeology::Init(FIdeologyDescription* IdeologyDescription)
{
	Tag = IdeologyDescription->Tag;
	Name = IdeologyDescription->IdeologyName;
	Color = IdeologyDescription->Color;
}

const FName& UIdeology::GetTag() const
{
	return Tag;
}

const FText& UIdeology::GetName() const
{
	return Name;
}

const FColor& UIdeology::GetColor() const
{
	return Color;
}
