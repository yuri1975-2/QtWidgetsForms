#pragma once

#include "AuthorityDependentForm.h"
#include "ui_ChildForm.h"

class ChildForm : public AuthorityDependentForm
{
	Q_OBJECT

private:
	Ui::ChildForm mUI;

public:
	ChildForm(QWidget* pwgt = nullptr);
	~ChildForm()
	{
		qDebug() << "call of ChildForm d'tor";
	}

protected:
	vector<QWidget*> getAuthorityDependentWidgets() override;
	unordered_map<AuthorityLevel, unordered_set<QWidget*>> getAuthorityLevelVisibleWidgets() override;
};