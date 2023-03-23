#pragma once
#include "Unit.h"

template <class T>
class TFMilitaryCollection: public IOwnable
{
public:
	virtual void Init(EMilitaryBranch ProvidedMilitaryBranch);

	virtual bool Add(T Item) = 0;

	virtual bool Remove(T Item) = 0;

	virtual const TSet<T>& GetAll() const = 0;

	virtual int32 GetSize() const = 0;

	virtual bool Contains(T Item) = 0;

	EMilitaryBranch GetMilitaryBranch() const;
	
	virtual ~TFMilitaryCollection() = default;
protected:
	UPROPERTY()
	EMilitaryBranch MilitaryBranch;
};

template <class T>
void TFMilitaryCollection<T>::Init(EMilitaryBranch ProvidedMilitaryBranch)
{
	MilitaryBranch = ProvidedMilitaryBranch;
}

template <class T>
EMilitaryBranch TFMilitaryCollection<T>::GetMilitaryBranch() const
{
	return MilitaryBranch;
}
