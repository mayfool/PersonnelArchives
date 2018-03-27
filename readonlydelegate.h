#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H
#include <QItemDelegate>
#include <QLineEdit>
#include <QComboBox>
//只读委托
class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
};





//利用QLineEdit委托和正则表达式对输入进行限制
//材料题名
class TitleDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    TitleDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
//档案目录中材料形成时间里的年
class YearDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    YearDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
//档案目录中材料形成时间里的月
class MonthDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    MonthDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
//档案目录中材料形成时间里的日
class DayDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    DayDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
//档案目录中页数
class PageDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    PageDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
#endif // READONLYDELEGATE_H
