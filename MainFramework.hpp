//
// Created by rw on 2022/12/13.
//

#ifndef MAINFRAMEWORK_HPP
#define MAINFRAMEWORK_HPP

#include "QWidget"
#include <QGuiApplication>
#include <QScreen>
#include <QTableWidget>
#include <QGridLayout>

#include "QMTableWidget.hpp"
#include "QMap"


namespace rw{

	class MainFramework: public QWidget
	{
	public:
		MainFramework();
		~MainFramework();
	public:
		void SetData(MMKV* Mmkv);
	private:
		void InitScreenSize();
		void GetSystemScreenSize();
		bool ReadFile(const QString& file_name);
	private:
		QSize mScreenSize;
		QMTableWidget* mDisplayWidget;
		QGridLayout* mBaseLayout;
	};
}

#endif //MAINFRAMEWORK_HPP
