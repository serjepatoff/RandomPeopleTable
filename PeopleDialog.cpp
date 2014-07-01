#include "PeopleDialog.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QCoreApplication>
#include <QMenu>

PeopleDialog::PeopleDialog(QWidget *parent) : QDialog(parent) {
    createLayouts();
    initHeader("<h1>Random pseudo-people table</h1>");
    initDataSource();
    initTable();
    initFooter();
    fillLayouts();
    connectSignalsToSlots();
}

void PeopleDialog::createLayouts() {
	mVLayout = new QVBoxLayout(this);
	mBottomBtnLayout = new QHBoxLayout(this);
}

void PeopleDialog::initHeader(const QString &headerText ) {
	mTopLabel = new QLabel(this);
    mTopLabel->setText(headerText);
}

void PeopleDialog::initDataSource() {
	QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
	QString storLoc = QCoreApplication::applicationDirPath();
    dbase.setDatabaseName(storLoc + "/people_db.sqlite");
    if (!dbase.open()) {
        QMessageBox::information(this, "Error", "Couldn't open database!");
        return;
    }
	mDataModel = new PeopleDataModel(this, dbase);
}

void PeopleDialog::initTable() {
	mTableView = new PeopleTableView(this);
	mTableView->setModel(mDataModel);
	mTableView->setContextMenuPolicy(Qt::CustomContextMenu);
	
	mTableView->setSelectionMode(QTableView::MultiSelection);
	mTableView->setSelectionBehavior(QTableView::SelectRows);
	mTableView->verticalHeader()->hide();
	sortByColumn(0);
}

void PeopleDialog::initFooter() {
	mB1 = new QPushButton(this);
    mB2 = new QPushButton(this);
    mB3 = new QPushButton(this);
    mB1->setText("Button1");
    mB2->setText("Button2");
    mB3->setText("Button3");
}


void PeopleDialog::fillLayouts() {
	mBottomBtnLayout->addWidget(mB1);
    mBottomBtnLayout->addWidget(mB2);
    mBottomBtnLayout->addWidget(mB3);
    mVLayout->addWidget(mTopLabel);
    mVLayout->addWidget(mTableView);
    mVLayout->addLayout(mBottomBtnLayout);
}

void PeopleDialog::connectSignalsToSlots() {
	connect(this, SIGNAL(finished(int)), this, SLOT(finished(int)));
	QHeaderView *horizHeader = mTableView->horizontalHeader();
	connect(horizHeader, SIGNAL(sectionClicked(int)), this, SLOT(sectionClicked(int)));
	connect(mTableView, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuRequested(QPoint)));
}

void PeopleDialog::finished(int result) {
}

void PeopleDialog::sortByColumn(int col) {
	mDataModel->sortByColumn(col);
	mTableView->sortByColumn(col, mDataModel->getCurrentSortOrder());
	mTableView->resizeColumnsToContents();
}

void PeopleDialog::sectionClicked(int section) {
	this->sortByColumn(section);	
}

void PeopleDialog::resizeEvent(QResizeEvent *event) {
	mTableView->resizeColumnsToContents();
}

void PeopleDialog::customMenuRequested(QPoint pos) {
	QModelIndex idx = mTableView->indexAt(pos);
    QMenu *menu = new QMenu(this);

    QAction *deleteRowAction = new QAction("Delete row", this);
    QAction *addRowAction = new QAction("Add row", this);
    connect( deleteRowAction, SIGNAL(triggered()), this, SLOT(deleteCurrentRows()) );
    connect( addRowAction, SIGNAL(triggered()), this, SLOT(addRow()) );

    menu->addAction(deleteRowAction);
    menu->addAction(addRowAction);
    menu->popup(mTableView->viewport()->mapToGlobal(pos));
}

void PeopleDialog::deleteCurrentRows() {
	QModelIndexList il = mTableView->selectionModel()->selectedRows();

	for ( int i=0; i<il.length(); ++i ) {
		int row = il.at(i).row();
		mDataModel->removeRows(row, 1);
	}
	
    mDataModel->select();
}

void PeopleDialog::addRow() {

}