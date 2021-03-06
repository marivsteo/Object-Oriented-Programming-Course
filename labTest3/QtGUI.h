#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGUI.h"
#include"Controller.h"

class QtGUI : public QMainWindow
{
	Q_OBJECT
private:
	Controller& controller;
public:
	QtGUI(Controller& controller, QWidget* parent = Q_NULLPTR);

private:
	Ui::QtGUI ui;
	void populateList();

private slots:
	//void handleFilterByNameOrCategory();
	void handleShowSymptoms();

};

