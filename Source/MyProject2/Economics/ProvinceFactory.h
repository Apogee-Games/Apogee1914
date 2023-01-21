#pragma once
#include "Description/FactoryDescription.h"
#include "ProvinceFactory.generated.h"

UCLASS()
class MYPROJECT2_API UProvinceFactory : public UObject
{
	GENERATED_BODY()
public:
	UProvinceFactory();

	void Init(const FFactoryDescription*);

	void Produce();
	
protected:
	
	const FFactoryDescription* FactoryDescription{};
	int32 Labours{};
	
private:
}; 