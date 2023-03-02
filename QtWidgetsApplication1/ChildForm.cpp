#include "ChildForm.h"

ChildForm::ChildForm(QWidget* pwgt) : AuthorityDependentForm(pwgt)
{
	mUI.setupUi(this);
}

vector<QWidget*> ChildForm::getAuthorityDependentWidgets()
{
	return {mUI.label1, mUI.label2, mUI.label3, mUI.label4, mUI.label5, mUI.label6};
}

unordered_map<AuthorityLevel, unordered_set<QWidget*>> ChildForm::getAuthorityLevelVisibleWidgets()
{
	return { {AuthorityLevel::eOperator,  {mUI.label1, mUI.label2}},
			 {AuthorityLevel::eTechnic,   {mUI.label1, mUI.label2, mUI.label3, mUI.label4}},
			 {AuthorityLevel::eEngeener,  {mUI.label1, mUI.label2, mUI.label3, mUI.label4, mUI.label5, mUI.label6}}
	};
}
