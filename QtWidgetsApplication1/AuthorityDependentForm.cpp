#include "AuthorityDependentForm.h"
#include "AuthorityManagerFactory.h"
#include <algorithm>

void AuthorityDependentForm::onAuthorityChanged(AuthorityLevel authorityLevel)
{
	qDebug() << "onAuthorityChanged(), authorityLevel: " << static_cast<int>(authorityLevel);

	if (!mIsAuthorityDependentWidgetsInitialized)
	{
		mAuthorityDependentWidgets = getAuthorityDependentWidgets();
		mAuthorityLevelVisibleWidgets = getAuthorityLevelVisibleWidgets();
		mIsAuthorityDependentWidgetsInitialized = true;
	}
	
	if ((mAuthorityDependentWidgets.empty()) || (mAuthorityLevelVisibleWidgets.empty()))
	{
		return;
	}

	unordered_set<QWidget*> visibleWidgets;
	auto foundPos(mAuthorityLevelVisibleWidgets.find(authorityLevel));
	if (mAuthorityLevelVisibleWidgets.end() != foundPos)
	{
		visibleWidgets = foundPos->second;
	}
	for_each(mAuthorityDependentWidgets.cbegin(), mAuthorityDependentWidgets.cend(),
		[&](const auto val)
		{
			if (nullptr == val)
			{
				return;
			}

			val->setVisible((visibleWidgets.end() != visibleWidgets.find(val)));
		});

}

void AuthorityDependentForm::showEvent(QShowEvent* event)
{
	if (!mIsAuthorityChangeSubscribed)
	{
		const auto manager(AuthorityManagerFactory::getManager());
		if (nullptr != manager)
		{
			manager->subscribeToAuthorityChange(this, SLOT(onAuthorityChanged(AuthorityLevel)));
		}

		mIsAuthorityChangeSubscribed = true;
	}

	if (!mIsFormUpdatedAtStart)
	{
		const auto manager(AuthorityManagerFactory::getManager());
		if (nullptr != manager)
		{
			onAuthorityChanged(manager->getCurrentAuthority());
			mIsFormUpdatedAtStart = true;
		}
	}

}

void AuthorityDependentForm::hideEvent(QHideEvent* event)
{
	if (mIsAuthorityChangeSubscribed)
	{
		const auto manager(AuthorityManagerFactory::getManager());
		if (nullptr != manager)
		{
			manager->unsubscribeToAutorityChange(this, SLOT(onAuthorityChanged(AuthorityLevel)));
		}

		mIsAuthorityChangeSubscribed = false;
	}

	mIsFormUpdatedAtStart = false;
}