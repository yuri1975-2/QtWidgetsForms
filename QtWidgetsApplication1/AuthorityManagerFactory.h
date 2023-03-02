#pragma once
#include "IAuthorityManager.h"
#include "AuthorityManagerImplementation.h"

class AuthorityManagerFactory
{
public:
	static shared_ptr<IAuthorityManager> getManager()
	{
		return AuthorityManagerImplementation::getInstance();
	}
};