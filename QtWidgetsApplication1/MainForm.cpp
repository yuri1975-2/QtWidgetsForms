#include <QDebug>
#include "MainForm.h"
#include "AuthorityManagerFactory.h"
#include <QThread>
#include "ChildForm.h"
#include <algorithm>

MainForm::MainForm(QWidget* pwgt) : AuthorityDependentForm(pwgt)
{
	mUI.setupUi(this);

	connect(mUI.btnLogin, SIGNAL(clicked()), this, SLOT(onLogin()));
	connect(mUI.btnNewForm, SIGNAL(clicked()), this, SLOT(onNewForm()));
}

void MainForm::onLogin()
{
	qDebug() << "Login button has been pressed, current thread id: " << QThread::currentThreadId();

	const auto manager(AuthorityManagerFactory::getManager());
	if (nullptr != manager)
	{
		mUI.btnLogin->setEnabled(false);
		manager->authorize(mUI.lineEdit->text());
	}
}

void MainForm::onNewForm()
{
	shared_ptr<QWidget> frm(nullptr);
	auto foundForm(mChildForms.find(ChildForm::staticMetaObject.className()));
	if (mChildForms.end() == foundForm)
	{
		frm = make_shared<ChildForm>();
		mChildForms.insert(make_pair(ChildForm::staticMetaObject.className(), frm));
		qDebug() << "create instance of ChildForm";
	}
	else
	{
		frm = foundForm->second;
	}
	
	if (nullptr != frm)
	{
		frm->move(x() + 1.1 * width(), y());
		frm->show();
	}
}

vector<QWidget*> MainForm::getAuthorityDependentWidgets()
{
	return {mUI.btnButton1, mUI.btnButton2, mUI.btnButton3, mUI.btnButton4, mUI.btnButton5, mUI.btnButton6};
}

unordered_map<AuthorityLevel, unordered_set<QWidget*>> MainForm::getAuthorityLevelVisibleWidgets()
{
	return { {AuthorityLevel::eOperator,  {mUI.btnButton1, mUI.btnButton2}},
			 {AuthorityLevel::eTechnic,   {mUI.btnButton1, mUI.btnButton2, mUI.btnButton3, mUI.btnButton4}},
			 {AuthorityLevel::eEngeener,  {mUI.btnButton1, mUI.btnButton2, mUI.btnButton3, mUI.btnButton4, mUI.btnButton5, mUI.btnButton6}}
	};
}

void MainForm::closeEvent(QCloseEvent* event)
{
	qDebug() << "closeEvent()";

	for_each(mChildForms.cbegin(), mChildForms.cend(),
		[](const auto val)
		{
			if (nullptr != val.second)
			{
				val.second->close();
			}
		});
}

void MainForm::onAuthorityChanged(AuthorityLevel authorityLevel)
{
	AuthorityDependentForm::onAuthorityChanged(authorityLevel);
	mUI.btnLogin->setEnabled(true);
}