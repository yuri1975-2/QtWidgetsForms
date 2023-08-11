NEEDS TO BE IMPLEMENTED:

Application, containing base and child forms. It is supposed that application can be expandable to include more than one child forms but currently it contains only one child form.

Base form contains:
1) field and button "Login" to enter password which defines mode of application:
    a) arbitrary or absent password-operator mode;
    b) "111"-techic;
    c) "222"-engeener.
2) depending on application mode:
    a) operator mode: "Button1"..."Button2";
    b) technic mode: "Button1"..."Button4";
    c) engeener mode: "Button1"..."Button6".
3) also "New Window" button opening child form.

Child form form contains "Text1"..."Text6" text label in accordance with application mode by analogy with "Button1"..."Button6" at base form.

Calculation of application mode depending on password entered is assumed to take a while, so it could be done in separate thread.



SOLUTION:

IAuthorityManager-interface of manager calculating application mode and notifying about this one change base and child forms;

AuthorityManagerImplementation-implementation of IAuthorityManager;

AuthorityManagerFactory-returns instance of IAuthorityManager implementation;

AuthorityDependentForm-base class both for base and child forms. Incapsulates logic to manage visibility of form controls in dependence of application mode;

ChildForm-implementation of child form;

MainForm-implementation of main form.
