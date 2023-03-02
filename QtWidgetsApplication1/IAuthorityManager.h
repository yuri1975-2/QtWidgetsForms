#pragma once
#include <memory>

using namespace std;

enum class AuthorityLevel {eOperator, eTechnic, eEngeener};

class IAuthorityManager
{
public:
	virtual void authorize(const QString&) = 0;
	
	virtual void subscribeToAuthorityChange(QObject*,const char*) const = 0;
	virtual void unsubscribeToAutorityChange(QObject*, const char*) const = 0;
	virtual AuthorityLevel getCurrentAuthority() const = 0;

	virtual ~IAuthorityManager() {}
};