#pragma once
#include "People/Instances/Person.h"

class ICommandable
{
public:
	void SetCommander(UPerson* ProvidedCommander);

	UPerson* GetCommander();
private:
	UPROPERTY()
	UPerson* Commander = nullptr;
};
