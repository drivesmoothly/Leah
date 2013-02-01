#ifndef SYNCHRONIZER_H_
#define SYNCHRONIZER_H_

class MSyncAccount;

class MSynchronizer
	{
public:
	virtual ~MSynchronizer();

public:
	// New functions

	// Adds a new account to the synchronizer
	virtual void AddAccountL(MSyncAccount& aAccount) = 0;
	// Removes an account from the synchronizer
	virtual void RemoveAccountL(MSyncAccount& aAccount) = 0;

	// Synchronizes all accounts. Supports full conflict resolution.
	virtual void SynchronizeL() = 0;
	// Synchronizes one way, from a given account to all the others.
	virtual void SyncFromL(MSyncAccount& aFrom) = 0;
	// Synchronizes one way, from all the accounts to one given account.
	virtual void SyncToL(MSyncAccount& aTo) = 0;
	};

#include "Synchronizer.inl"

#endif //SYNCHRONIZER_H_
