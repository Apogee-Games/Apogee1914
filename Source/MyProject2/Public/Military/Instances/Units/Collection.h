#pragma once
#include "Unit.h"

template <class T>
class TFMilitaryCollection: public IOwnable
{
public:
	virtual void Init(UMilitaryBranchDescription* ProvidedMilitaryBranch);

	virtual bool Add(T Item) = 0;

	virtual bool Remove(T Item) = 0;

	virtual const TSet<T>& GetAll() const = 0;

	virtual int32 GetSize() const = 0;

	virtual bool Contains(T Item) = 0;

	UMilitaryBranchDescription* GetMilitaryBranch() const;
	
	virtual ~TFMilitaryCollection() = default;
protected:
	UPROPERTY()
	UMilitaryBranchDescription* MilitaryBranch;
};

template <class T>
void TFMilitaryCollection<T>::Init(UMilitaryBranchDescription* ProvidedMilitaryBranch)
{
	MilitaryBranch = ProvidedMilitaryBranch;
}

template <class T>
UMilitaryBranchDescription* TFMilitaryCollection<T>::GetMilitaryBranch() const
{
	return MilitaryBranch;
}
