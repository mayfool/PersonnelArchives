/*功能说明
文件名称：MainTableView
作    者：马进
联系方式：
创建时间：2017.10.03
目    的：在主界面上显示人员基本信息表
功能描述：
约束条件：
*/
#ifndef MAINTABLEVIEW_H
#define MAINTABLEVIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <accessdb.h>
#include <QHeaderView>
#include <Qt>

class MainTableView : public QTableView
{
public:
    MainTableView(QWidget *parent);
    ~MainTableView();

 //   SetHead(AccessDB *accdb);
};

#endif // MAINTABLEVIEW_H
