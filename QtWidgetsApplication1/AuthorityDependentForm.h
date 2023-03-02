#pragma once

#include<QtWidgets>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "IAuthorityManager.h"

using namespace std;

class AuthorityDependentForm : public QWidget
{
	Q_OBJECT

private:
	bool mIsAuthorityDependentWidgetsInitialized = false;
	vector<QWidget*> mAuthorityDependentWidgets;
	unordered_map<AuthorityLevel, unordered_set<QWidget*>> mAuthorityLevelVisibleWidgets;
	bool mIsAuthorityChangeSubscribed = false;
	bool mIsFormUpdatedAtStart = false;

public:
	AuthorityDependentForm(QWidget* pwgt = nullptr) : QWidget(pwgt) {};
	virtual ~AuthorityDependentForm() {}

protected:
	virtual vector<QWidget*> getAuthorityDependentWidgets()
	{
		return {};
	}
	virtual unordered_map<AuthorityLevel, unordered_set<QWidget*>> getAuthorityLevelVisibleWidgets()
	{
		return {};
	}

protected slots:
	virtual void onAuthorityChanged(AuthorityLevel);

protected:
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);
};