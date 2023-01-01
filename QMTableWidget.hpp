//
// Created by rw on 2022/12/15.
//

#ifndef QMTABLEWIDGET_HPP
#define QMTABLEWIDGET_HPP

#include "QTableWidget"
#include "qDebug"
#include "QEvent"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QDragMoveEvent"
#include "QMimeData"
#include "QList"
#include "QFile"
#include "QFileInfo"
#include "MMKV.h"
#include "QInputDialog"
#include <QComboBox>
#include "QMenu"
#include "QAction"

namespace rw{
	typedef struct{
		int row;
		int column;
	}TablePos;

	class QMTableWidget : public QTableWidget
	{
	public:
		QMTableWidget();
		~QMTableWidget() = default;
	public:
		void SetData(MMKV*);
		bool eventFilter(QObject *obj, QEvent *event) override;
	protected:
		void dragEnterEvent(QDragEnterEvent *event) override;
		void dropEvent(QDropEvent* event) override;
		void dragMoveEvent(QDragMoveEvent *event) override;
		void mousePressEvent(QMouseEvent* event) override;
	public slots:
		void ChangeDataType(int);
	private:
		void init();
		void parseIsString();
		void setItemValue(int,int);
	private:
		MMKV* mMmkv;
		QMap<QObject*, TablePos> mComboBoxs;
		QMenu* mMenu;
		std::vector<std::string> mAllKeys;
	};
}


#endif //QMTABLEWIDGET_HPP
