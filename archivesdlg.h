#ifndef ARCHIVESDLG_H
#define ARCHIVESDLG_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class ArchivesDlg;
}

class ArchivesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ArchivesDlg(QWidget *parent = 0);
    explicit ArchivesDlg(QWidget *parent,QString pid);
    ~ArchivesDlg();
    QString getPid();
    AccessDB* getAccdb();
private:
    void setTableCol();//设置表头
private:
    Ui::ArchivesDlg *ui;
    QWidget *m_parent;
    QString m_pid;
    AccessDB *m_accdb;
};

#endif // ARCHIVESDLG_H
