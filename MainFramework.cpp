//
// Created by rw on 2022/12/13.
//

#include "MainFramework.hpp"
#include "QHeaderView"
#include "qDebug"

namespace rw{

MainFramework::MainFramework():mDisplayWidget(nullptr)
{
	InitScreenSize();
	this->setWindowTitle("QMmkvReader");
	this->setMouseTracking(true);

	mBaseLayout = new QGridLayout(this);
	mDisplayWidget = new QMTableWidget();
	mDisplayWidget->setParent(this);
	mDisplayWidget->setColumnCount(3);

	mDisplayWidget->setHorizontalHeaderLabels({"Name","Type","Value"});
	mDisplayWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mDisplayWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	mBaseLayout->addWidget(mDisplayWidget);
}

MainFramework::~MainFramework()
{
}

void MainFramework::InitScreenSize()
{
	GetSystemScreenSize();
	this->setFixedSize(mScreenSize*0.85);
}
void MainFramework::GetSystemScreenSize()
{
	QList <QScreen*> screens = QGuiApplication::screens();
	for(int i =0; i< screens.count(); i++){
		mScreenSize = screens.at(0)->size();
	}
}

}

