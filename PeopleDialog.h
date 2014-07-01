#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "PeopleDataModel.h"
#include "PeopleTableView.h"

class PeopleDialog : public QDialog {
    Q_OBJECT

private:
	QLabel *mTopLabel;
	QPushButton *mB1;
	QPushButton *mB2;
	QPushButton *mB3;
	PeopleTableView *mTableView;
	QVBoxLayout *mVLayout;
	QHBoxLayout *mBottomBtnLayout;
	PeopleDataModel *mDataModel;

private:
	void initHeader(const QString &headerText );
	void initTable();
	void initFooter();
	void createLayouts();
	void fillLayouts();
	void initDataSource();
	void connectSignalsToSlots();
	void sortByColumn( int col );

public:
    PeopleDialog(QWidget *parent = 0);

public slots:
	void finished(int result);
	void sectionClicked(int section);
	void customMenuRequested(QPoint pos);
	void deleteCurrentRows();
	void addRow();

protected:
	virtual void resizeEvent(QResizeEvent *event);
};