#pragma once

#include "AuthorityDependentForm.h"
#include "ui_MainForm.h"
#include <memory>
#include <unordered_map>
#include <string>

using namespace std;

class MainForm : public AuthorityDependentForm
{
	Q_OBJECT

private:
	Ui::MainForm mUI;
	unordered_map<string, shared_ptr<QWidget>> mChildForms;

public:
	MainForm(QWidget* pwgt = nullptr);

protected:
	vector<QWidget*> getAuthorityDependentWidgets() override;
	unordered_map<AuthorityLevel, unordered_set<QWidget*>> getAuthorityLevelVisibleWidgets() override;

	void closeEvent(QCloseEvent* event);

private slots:
	void onLogin();
	void onNewForm();

protected slots:
	void onAuthorityChanged(AuthorityLevel);
};