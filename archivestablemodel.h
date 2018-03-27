/*功能说明
文件名称：archivestablemodel.h
作    者：马进
联系方式：
创建时间：2017.11.19
目    的：显示目录信息的视图的模型
功能描述：建立一个自定义结构的链表，填充从数据库中读取的目录信息，填充十大分类、空行等
约束条件：
*/
#ifndef ARCHIVESTABLEMODEL_H
#define ARCHIVESTABLEMODEL_H

#include <QAbstractTableModel>
#include <mainwindow.h>

class ArchivesTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ArchivesTableModel(QObject *parent = 0);
    //explicit ArchivesTableModel(QObject *parent,QString pid);
    ~ArchivesTableModel();
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    AccessDB *m_accdb;
    //QSqlQueryModel* m_queryModel;
    QSqlQuery *m_query;
    QString m_pid;
    int m_spaceRow;
    //int m_list[4];
    //QSqlTableModel* m_tableModel;
    //自定义的数据结构，表中一行对应一个数据结构
    struct tableModelStruct
    {
        int style1;//一级分类
        int style2;//二级分类
        int style3;//三级分类
        int fArchives;//数据库中该条目录的序号
        int type;//该行数据的分类，共4种。0：空行; 1：一级分类（十大分类）；2：二级分类；3：目录信息；
        QString fpaid;//数据库中人员编号
        QString archive;//目录名称
        QString remark;//备注
        int year;
        int month;
        int day;
        int page;//页数
    };//结构体，从数据库中读取数据，提供给模型使用
    QList <tableModelStruct*> m_archivesList;
    void setTableModelStructZero(ArchivesTableModel::tableModelStruct *stru);//清空数据结构

};

#endif // ARCHIVESTABLEMODEL_H
