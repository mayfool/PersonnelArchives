#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accessdb.h"
#include <searchdlg.h>
#include <archivesdlg.h>

#include <QMessageBox>
#include <QDebug>
#include <Qtsql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <maintableview.h>
#include <QMenu>
#include <QHeaderView>

namespace Ui {
class MainWindow;
}
class QSqlTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainTableView* getTableView();
    QSqlTableModel* getTableModel();
    AccessDB* getAccessDB();
public slots:
    //人员信息表右键菜单
    void on_m_tableView_customContextMenuRequested(const QPoint &pos);
    //人员信息表表头右键菜单
    void on_headerView_customContextMenuRequested(const QPoint &pos);
    void on_showArchivesDlg();
    void on_searchBtn_clicked();
public:
    QMenu *tableViewMenu = NULL;
    QMenu *headerViewMenu = NULL;

private slots:
    void on_personnelBasicInfo_clicked();

    void on_infoSearchBtn_clicked();

    void on_photoBtn_clicked();

    void on_workBtn_clicked();

    void on_storeBtn_clicked();

    void on_databaseBtn_clicked();

private:
    Ui::MainWindow *ui;
    AccessDB *accdb;
    QSqlTableModel* m_tableModel;
    MainTableView *m_tableview;
    SearchDlg *searchDlg = NULL;
};

#endif // MAINWINDOW_H
