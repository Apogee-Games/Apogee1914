#include "Military/Interfaces/Commandable.h"

void ICommandable::SetCommander(UPerson* ProvidedCommander)
{
	Commander = ProvidedCommander;
}

UPerson* ICommandable::GetCommander()
{
	return Commander;
}
