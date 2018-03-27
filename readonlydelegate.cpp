#include "readonlydelegate.h"
#include <QDebug>
ReadOnlyDelegate::ReadOnlyDelegate(QObject *parent): QItemDelegate(parent)
{}
QWidget *ReadOnlyDelegate::createEditor(QWidget*parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    return NULL;
}

//利用QLineEdit委托和正则表达式对输入进行限制
//对档案目录中的材料题名列进行输入限制
    TitleDelegate::TitleDelegate(QObject *parent): QItemDelegate(parent)
    { }
    QWidget *TitleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        QLineEdit *editor = new QLineEdit(parent);
        //QRegExp regExp("[0-9]{0,10}");
        //editor->setValidator(new QRegExpValidator(regExp, parent));
        return editor;
    }
    void TitleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::DisplayRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(text);
    }
    void TitleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
    void TitleDelegate::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }

    //对档案目录中的材料时间中“年”进行输入控制
        YearDelegate::YearDelegate(QObject *parent): QItemDelegate(parent)
        { }
        QWidget *YearDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
            const QModelIndex &index) const
        {
            QLineEdit *editor = new QLineEdit(parent);
            //QRegExp regExp("([1-2][0-9][0-9][0-9]){0,1}");
            QRegExp regExp("|[1][8-9][0-9][0-9]|[2][0][0-9][0-9]");//控制输入：空，18**，19**，20**可输入
            editor->setValidator(new QRegExpValidator(regExp, parent));
            //editor->setValidator(new QIntValidator(0, 3000, parent));
            return editor;
        }
        void YearDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
        {
            QString text = index.model()->data(index, Qt::DisplayRole).toString();
            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
            lineEdit->setAlignment(Qt::AlignCenter);//点击输入框时内容局中
            lineEdit->setText(text);
        }
        void YearDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
            const QModelIndex &index) const
        {
            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
            QString text = lineEdit->text();
            model->setData(index, text, Qt::EditRole);
        }
        void YearDelegate::updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option, const QModelIndex &index) const
        {
            editor->setGeometry(option.rect);
        }

    //对档案目录中的材料时间中“月”进行输入控制
MonthDelegate::MonthDelegate(QObject *parent): QItemDelegate(parent)
{ }
QWidget *MonthDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
   const QModelIndex &index) const
{
   QLineEdit *editor = new QLineEdit(parent);

    //QRegExp regExp("[0-9]{0,10}");
    //editor->setValidator(new QRegExpValidator(regExp, parent));
    //editor->setValidator(new QIntValidator(0, 12, parent));
   QRegExp regExp("|0?[0-9]|[1][0-2]");//控制输入：空，*,0*，10，11,12可输入
   editor->setValidator(new QRegExpValidator(regExp, parent));
   return editor;
}
void MonthDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setAlignment(Qt::AlignCenter);//点击输入框时内容局中
    lineEdit->setText(text);
}
void MonthDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
     const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}
void MonthDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
//对档案目录中的材料时间中“日”进行输入控制
DayDelegate::DayDelegate(QObject *parent): QItemDelegate(parent)
{ }
QWidget *DayDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    //editor->setValidator(new QIntValidator(0, 31, parent));
    QRegExp regExp("|0?[0-9]|[1-2][0-9]|30|31");//控制输入：空，*,0*，1*，2*,30,31可输入
    editor->setValidator(new QRegExpValidator(regExp, parent));
    return editor;
}
void DayDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setAlignment(Qt::AlignCenter);//点击输入框时内容局中
    lineEdit->setText(text);
}
void DayDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}
void DayDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

//对档案目录中的页码进行输入控制
PageDelegate::PageDelegate(QObject *parent): QItemDelegate(parent)
{ }
QWidget *PageDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QRegExp regExp("|[0-9]{0,10}");
    editor->setValidator(new QRegExpValidator(regExp, parent));
    //editor->setValidator(new QIntValidator(0, 3000, parent));
    return editor;
}
void PageDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setAlignment(Qt::AlignCenter);//点击输入框时内容局中
    lineEdit->setText(text);
}
void PageDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}
void PageDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
