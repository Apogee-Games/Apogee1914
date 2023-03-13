#pragma once
#include "Unit.h"

template <class T>
class TFCollection
{
public:
	virtual void Init(EMilitaryBranch ProvidedMilitaryBranch);

	virtual bool Add(T Item) = 0;

	virtual bool Remove(T Item) = 0;

	virtual const TArray<T>& GetAll() const = 0;

	virtual int32 GetSize() const = 0;

	EMilitaryBranch GetMilitaryBranch() const;
	
	virtual ~TFCollection() = default;
protected:
	UPROPERTY()
	EMilitaryBranch MilitaryBranch;
};

template <class T>
void TFCollection<T>::Init(EMilitaryBranch ProvidedMilitaryBranch)
{
	MilitaryBranch = ProvidedMilitaryBranch;
}

template <class T>
EMilitaryBranch TFCollection<T>::GetMilitaryBranch() const
{
	return MilitaryBranch;
}
