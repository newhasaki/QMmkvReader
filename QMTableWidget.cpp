//
// Created by rw on 2022/12/15.
//

#include "QMTableWidget.hpp"
rw::QMTableWidget::QMTableWidget()
{
	this->setMouseTracking(true);
	this->setAcceptDrops(true);
	this->setSelectionMode(QAbstractItemView::SingleSelection);

	mMenu = new QMenu(this);
	QAction* strings_an = mMenu->addAction("all_strings");
	connect(strings_an,&QAction::triggered,this,[=](){
		parseIsString();
	});
}

void rw::QMTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasFormat("text/uri-list")){
		event->accept();
	}
}


void rw::QMTableWidget::dropEvent(QDropEvent *event)
{
	init();

	bool is_ok;
	QString key = QInputDialog::getText(this,tr("密码"),tr("请输入密码:"),QLineEdit::Normal,0,&is_ok);

	QList<QUrl> urls = event->mimeData()->urls();
	if(urls.isEmpty()){
		return;
	}

	QString local_file = urls.first().toLocalFile();
	if(local_file.isEmpty()){
		return;
	}

	QFileInfo info(local_file);
	QString file_path = info.absolutePath();
	std::string root_path = file_path.toStdString();
	MMKV::initializeMMKV(root_path, MMKVLogNone);

	QString file_name = info.fileName();
	std::string std_key = key.toStdString();
	MMKV* mkv = MMKV::mmkvWithID(file_name.toStdString(),MMKV_SINGLE_PROCESS,&std_key,&root_path);
	SetData(mkv);
}
void rw::QMTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
}


void rw::QMTableWidget::SetData(MMKV *Mmkv)
{
	if(Mmkv != nullptr) {
		mMmkv = Mmkv;
		mAllKeys = Mmkv->allKeys();
		this->setRowCount(mAllKeys.size());

		for (int i = 0; i < mAllKeys.size(); i++) {
			QTableWidgetItem *table_widget_item = new QTableWidgetItem(QString::fromStdString(mAllKeys.at(i)));

			this->setItem(i, 0, table_widget_item);
			QComboBox *combo_box = new QComboBox();
			combo_box->addItems({"请选择数据类型", "string", "bool", "float", "int"});
			combo_box->installEventFilter(this);

			mComboBoxs[combo_box] = {i, 1};
			connect(combo_box,
					(void (QComboBox::*)(int))&QComboBox::currentIndexChanged,
					this,
					&QMTableWidget::ChangeDataType);

			this->setCellWidget(i, 1, combo_box);
		}
	}
}

void rw::QMTableWidget::ChangeDataType(int index)
{
	int row = this->currentRow();
	int column = this->currentColumn();

	switch (index) {
		case 1:{
			setItemValue(row,column);
//			QTableWidgetItem * item = this->item(row,column-1);
//			QString item_text = item->text();
//			qDebug() << item_text;
//
//			std::string result;
//			mMmkv->getString(item_text.toStdString(),result);
//			QTableWidgetItem* new_item = new QTableWidgetItem(QString::fromStdString(result));
//			new_item->setToolTip(QString::fromStdString(result));
//			this->setItem(row,column + 1, new_item);
		}
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}
bool rw::QMTableWidget::eventFilter(QObject *obj, QEvent *event)
{
	if(mComboBoxs.contains(obj)){
		if(QEvent::Enter == event->type()){
			TablePos table_pos = mComboBoxs[obj];
			this->setCurrentIndex(this->model()->index(table_pos.row,table_pos.column));
		}
	}

	return QObject::eventFilter(obj, event);
}
void rw::QMTableWidget::init()
{
	mComboBoxs.clear();
	mMmkv = nullptr;
}
void rw::QMTableWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton){
		mMenu->exec(event->globalPos());
	}
	// QAbstractItemView::mousePressEvent(event);
}
void rw::QMTableWidget::parseIsString()
{
//	for(size_t i=0;i<mComboBoxs.size();i++){
//		disconnect(combo_box,
//				   (void (QComboBox::*)(int))&QComboBox::currentIndexChanged,
//				   this,
//				   &QMTableWidget::ChangeDataType);
//	}


	if(mMmkv != nullptr){
//		for(size_t i = 0;i<mAllKeys.size();i++){
//			std::string result;
//			bool is_str = mMmkv->getString(mAllKeys.at(i),result);
//			this->setItem(i,2 ,new QTableWidgetItem(QString::fromStdString(result)));
//		}

		for(auto it :mComboBoxs.keys()){
			disconnect((QComboBox*)it,
					   (void (QComboBox::*)(int))&QComboBox::currentIndexChanged,
					   this,
					   &QMTableWidget::ChangeDataType);

			((QComboBox*)it)->setCurrentIndex(1);
			TablePos tab_pos = mComboBoxs[it];
			setItemValue(tab_pos.row,tab_pos.column);
			connect((QComboBox*)it,
					   (void (QComboBox::*)(int))&QComboBox::currentIndexChanged,
					   this,
					   &QMTableWidget::ChangeDataType);

		}
	}
}
void rw::QMTableWidget::setItemValue(int row, int column)
{
	QTableWidgetItem * item = this->item(row,column-1);
	QString item_text = item->text();
	qDebug() << item_text;

	std::string result;
	mMmkv->getString(item_text.toStdString(),result);
	QTableWidgetItem* new_item = new QTableWidgetItem(QString::fromStdString(result));
	new_item->setToolTip(QString::fromStdString(result));
	this->setItem(row,column + 1, new_item);

}
