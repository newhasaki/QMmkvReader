#include <QApplication>
#include <QDebug>
#include "MmkvReader.hpp"
#include "MainFramework.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	rw::MainFramework main_framework;
	main_framework.show();
	return QApplication::exec();
}
