#include "AuthorityManagerImplementation.h"
#include <QThread>

shared_ptr<AuthorityManagerImplementation> AuthorityManagerImplementation::mInstance = nullptr;

void AuthorityManagerImplementation::authorizeImplementation(const QString& password)
{
	qDebug() << "autorize(), calculate authority level...";
	QThread::sleep(3);
	qDebug() << "autorize(), current thread id = " << QThread::currentThreadId() << ", password = " << password;

	if ("111" == password)
	{
		mAuthorityLevel = AuthorityLevel::eTechnic;
	}
	else if ("222" == password)
	{
		mAuthorityLevel = AuthorityLevel::eEngeener;
	}
	else
	{
		mAuthorityLevel = AuthorityLevel::eOperator;
	}
	emit authorityChanged(mAuthorityLevel);
}