#ifndef SEARCHDLG_H
#define SEARCHDLG_H

#include <QDialog>
#include <maintableview.h>
#include <QSqlTableModel>
#include <accessdb.h>


namespace Ui {
class SearchDlg;
}

class SearchDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDlg(QWidget *parent = 0);
    ~SearchDlg();

private slots:
    void on_cancelBtn_clicked();

    void on_searchBtn_clicked();

    void on_selectBtn_toggled(bool checked);

private:
    Ui::SearchDlg *ui;
    QWidget *m_parent;
    //MainWindow * mainWindow;需要包含头文件，会造成重复包含的问题
    QSqlTableModel* tableModel;
    MainTableView *tableView;
    AccessDB *accdb;
};

#endif // SEARCHDLG_H
