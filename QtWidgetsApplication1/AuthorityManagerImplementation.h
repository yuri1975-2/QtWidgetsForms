#pragma once

#include <QObject>
#include <memory>
#include <QtConcurrent\QtConcurrent>
#include "IAuthorityManager.h"
#include <QMetaType>

using namespace std;

class AuthorityManagerImplementation : public QObject, public IAuthorityManager
{
	Q_OBJECT

public:
	static shared_ptr<IAuthorityManager> getInstance()
	{
		if (nullptr == mInstance.get())
		{
			mInstance = shared_ptr<AuthorityManagerImplementation>(new AuthorityManagerImplementation());
		}

		return mInstance;
	}

	void authorize(const QString& name) override
	{
		QtConcurrent::run([=]()
			{
				authorizeImplementation(name);
			});
	}

	void authorizeImplementation(const QString&);

	virtual void subscribeToAuthorityChange(QObject* client, const char* handler) const override
	{
		connect(this, SIGNAL(authorityChanged(AuthorityLevel)), client, handler);
	}

	virtual void unsubscribeToAutorityChange(QObject* client, const char* handler) const override
	{
		disconnect(this, SIGNAL(authorityChanged(AuthorityLevel)), client, handler);
	}

	virtual AuthorityLevel getCurrentAuthority() const override
	{
		return mAuthorityLevel;
	}

private:
	AuthorityLevel mAuthorityLevel;
	static shared_ptr<AuthorityManagerImplementation> mInstance;

	AuthorityManagerImplementation() : QObject(), mAuthorityLevel(AuthorityLevel::eOperator)
	{
		qRegisterMetaType<AuthorityLevel>("AuthorityLevel");
	}

signals:
	void authorityChanged(AuthorityLevel);
};