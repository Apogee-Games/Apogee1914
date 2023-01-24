#pragma once
#include "Description/FactoryDescription.h"
#include "Description/FactoryInstanceDescription.h"
#include "ProvinceFactory.generated.h"

UCLASS()
class MYPROJECT2_API UProvinceFactory : public UObject
{
	GENERATED_BODY()
public:
	UProvinceFactory();
	
	UProvinceFactory(const FFactoryInstanceDescription&, const FFactoryDescription*);
	
	void Produce();

	void Init(const FFactoryInstanceDescription&, const FFactoryDescription*);
		
	const FFactoryDescription* GetFactoryDescription() const;

	int32 GetLabours() const;

protected:
	
	const FFactoryDescription* FactoryDescription{};
	int32 Labours{};
	
private:
}; 