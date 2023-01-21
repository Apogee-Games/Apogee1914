#pragma once
#include "Description/FactoryDescription.h"
#include "MyProject2/World/Province.h"
#include "ProvinceFactory.generated.h"

UCLASS()
class MYPROJECT2_API UProvinceFactory : public UObject
{
	GENERATED_BODY()
public:
	UProvinceFactory();

	void Init(const FProvince*, const FFactoryDescription*);

	void Produce();
	
protected:
	
	const FFactoryDescription* FactoryDescription{};
	const FProvince* Province{};
	int32 Labours{};
	
private:
}; 