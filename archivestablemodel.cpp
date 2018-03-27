#include "archivestablemodel.h"
#include "mainwindow.h"


ArchivesTableModel::ArchivesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    ArchivesDlg * archivesDlg = (ArchivesDlg*) parent;  //获取父窗口指针
    m_pid = archivesDlg->getPid();
    m_accdb = archivesDlg->getAccdb();
    m_query = m_accdb->getQuery();
    m_spaceRow = 2;//分类后面留2个空行

    //建立一个qlist结构，存储QtableView中显示的数据


    //即使没有目录信息，也要显示十大分类内容
    int count1 = 1;
    m_query->exec("select * from ArchClass where ParentID = 0");
    while(m_query->next())
    {
        tableModelStruct *tbStruct = new tableModelStruct;
        setTableModelStructZero(tbStruct);//清空结构体
        tbStruct->style1 = count1;//一级分类
        tbStruct->style2 = 0;//二级分类
        tbStruct->style3 = 0;//三级分类
        tbStruct->type = 1;//代表是一级分类
        tbStruct->archive = m_query->value(5).toString();//一级分类内容
        m_archivesList.append(tbStruct);
        count1++;
    }

    //插入四类材料的二级分类
    int count2 = 1;
    m_query->exec("select * from ArchClass where ParentID = 4");
    while(m_query->next())
    {
        tableModelStruct *tbStruct = new tableModelStruct;
        setTableModelStructZero(tbStruct);//清空结构体
        tbStruct->style1 = 4;//一级分类
        tbStruct->style2 = count2;//二级分类
        tbStruct->style3 = 0;//三级分类
        tbStruct->type = 2;//代表是二级分类
        tbStruct->archive = m_query->value(5).toString();//二级分类内容
        int i = 0;
        for(i = 0;i<m_archivesList.size();i++)
        {
            if(m_archivesList.at(i)->style1 == 5)
                break;
        }
        m_archivesList.insert(i,tbStruct);
        count2++;
    }

    //插入九类材料的二级分类
    int count3 = 1;
    m_query->exec("select * from ArchClass where ParentID = 9");
    while(m_query->next())
    {
        tableModelStruct *tbStruct = new tableModelStruct;
        setTableModelStructZero(tbStruct);//清空结构体
        tbStruct->style1 = 9;//一级分类
        tbStruct->style2 = count3;//二级分类
        tbStruct->style3 = 0;//三级分类
        tbStruct->type = 2;//代表是二级分类
        tbStruct->archive = m_query->value(5).toString();//二级分类内容
        int i = 0;
        for(i = 0;i<m_archivesList.size();i++)
        {
            if(m_archivesList.at(i)->style1 == 10)
                break;
        }
        m_archivesList.insert(i,tbStruct);
        count3++;
    }
    //在每个数据结构后面加m_spaceRow个空行
    for(int i = m_archivesList.size();i>0;i--)
    {
        if((i != 4)&&(i != 13))//第四大类和九大类后面不加空行
        {
            for(int j = 0;j<m_spaceRow;j++)
            {
                tableModelStruct *tbStructSpace = new tableModelStruct;
                setTableModelStructZero(tbStructSpace);//清空结构体
                m_archivesList.insert(i,tbStructSpace);
            }
        }
    }

    //插入数据库中的目录内容
    m_query->exec(QString("select * from ArchivesInfo where fpaid = %1").arg(m_pid));
    //int count = 0;
    QString date;//日期
    while(m_query->next())
    {
        tableModelStruct *tbStruct = new tableModelStruct;
        setTableModelStructZero(tbStruct);//清空结构体
        tbStruct->fArchives = m_query->value(0).toInt();//数据库中该条目录的序号
        tbStruct->fpaid = m_pid;//数据库中该目录所属的人员编号
        tbStruct->style1 = m_query->value(2).toInt();//一级分类
        tbStruct->style2 = m_query->value(3).toInt();//二级分类
        tbStruct->style3 = m_query->value(4).toInt();//三级分类
        tbStruct->type  = 3;
        tbStruct->archive = m_query->value(5).toString();//目录内容
        tbStruct->remark = m_query->value(12).toString();//备注
        date = m_query->value(6).toString();//分解年月日
        tbStruct->year = date.left(4).toInt();
        tbStruct->month = date.mid(4,2).toInt();
        tbStruct->day = date.right(2).toInt();
        tbStruct->page = m_query->value(8).toInt();//页数
        //遍历链表，找到正确的插入位置
        for(int i = 0;i<m_archivesList.size();i++)
        {
            if((m_archivesList.at(i)->style1 == tbStruct->style1)&&(m_archivesList.at(i)->style2 == tbStruct->style2)&&(m_archivesList.at(i)->style3 == (tbStruct->style3 - 1)))
            {
                m_archivesList.insert(i+1,tbStruct);
                break;
            }
        }
        //count++;
    }

    for(int i = 0;i<m_archivesList.size();i++)
    {
        qDebug()<<m_archivesList.at(i)->archive<<m_archivesList.at(i)->fArchives<<m_archivesList.at(i)->fpaid;
        qDebug()<<m_archivesList.at(i)->year<<m_archivesList.at(i)->month<<m_archivesList.at(i)->day;
        qDebug()<<m_archivesList.at(i)->style1<<m_archivesList.at(i)->style2<<m_archivesList.at(i)->style3;
        qDebug()<<m_archivesList.at(i)->page;

    }
    //qDebug()<<count;
    //给十大分类排序
    for(int i=0;i<m_archivesList.size();++i)
    {
        //qDebug()<<m_archivesList.at(i)[0]<<m_archivesList.at(i)[1]<<m_archivesList.at(i)[2]<<m_archivesList.at(i)[3];
        //std::stable_sort(m_archivesList.begin(),m_archivesList.end());
    }
    //qDebug()<<m_archivesList;
/*    m_queryModel = new QSqlQueryModel(this);
    m_tableModel = new QSqlTableModel(this,accdb->getSqlDB());
    m_tableModel->setTable("ArchivesInfo");
    m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//编辑策略，所有改变直到调用submitAll()或revertAll()函数
    m_tableModel->setFilter("fpaid = 22");//'%%1%'").arg('22'));
    m_tableModel->select();
    */

}

ArchivesTableModel::~ArchivesTableModel()
{
   //accdb->closeDB();
    //m_archivesList.
}

QVariant ArchivesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool ArchivesTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int ArchivesTableModel::rowCount(const QModelIndex &parent) const
{
    //if (!parent.isValid())
    //    return 0;
/*
    int count = 0;
    m_query->exec(QString("select * from ArchivesInfo where fpaid = %1").arg(m_pid));
    //m_query->first();
    while(m_query->next())
    {
        count++;
        qDebug()<<count;
    }
    return count + 39;//表头+10大分类+空行18+m_spaceRow*
    */
    return m_archivesList.size()+3;//表头占3行
}

int ArchivesTableModel::columnCount(const QModelIndex &parent) const
{
    //if (!parent.isValid())
    //    return 0;
    return 7;//共7列
}
//填充单元格内容
QVariant ArchivesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    int nRow = index.row();
    int nColumn = index.column();
   // m_query->exec(QString("select * from ArchivesInfo where fpaid = %1").arg(m_pid));
    //FileRecord record = m_recordList.at(nRow);

    if(nRow == 0)//0行
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",20,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        //case Qt::TextColorRole:
        //    return QColor(Qt::white);setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable)
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "干 部 人 事 档 案 目 录";
        default:
            return QVariant();
        }
    }
    if((nRow == 1)&&(nColumn == 0))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",15,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "序号";
        default:
            return QVariant();
        }
    }
    if((nRow == 1)&&(nColumn == 1))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",18,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "材 料 题 名";
        default:
            return QVariant();
        }
    }
    if((nRow == 1)&&(nColumn == 2))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",14,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "材料形成时间";
        default:
            return QVariant();
        }
    }
    if((nRow == 1)&&(nColumn == 5))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",14,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "页数";
        default:
            return QVariant();
        }
    }
    if((nRow == 1)&&(nColumn == 6))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",14,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "备注";
        default:
            return QVariant();
        }
    }
    if((nRow == 2)&&(nColumn == 2))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",14,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "年";
        default:
            return QVariant();
        }
    }
    if((nRow == 2)&&(nColumn == 3))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",14,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "月";
        default:
            return QVariant();
        }
    }
    if((nRow == 2)&&(nColumn == 4))
    {
        switch (role)
        {
        case Qt::FontRole:
            return QFont("宋体",14,QFont::Bold);
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "日";
        default:
            return QVariant();
        }
    }
    if(nRow > 2)
    {
        switch (role)
        {
        case Qt::FontRole:
            if(m_archivesList.at(nRow-3)->type == 1)//是一级分类
            {
                return QFont("宋体",16,QFont::Bold);
            }
            return QFont("宋体",13);
        case Qt::TextColorRole:
            if(m_archivesList.at(nRow-3)->type == 1)//是一级分类
            {
                return QColor(Qt::red);
            }
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            if(nColumn == 1)//材料题名
                return QVariant(Qt::AlignVCenter);
            if(nColumn == 6)//备注
                return QVariant(Qt::AlignVCenter);
            return QVariant(Qt::AlignHCenter|Qt::AlignVCenter);
        case Qt::DisplayRole:
            if(nColumn == 0)//序号
            {
                if(m_archivesList.at(nRow-3)->type == 1)//是一级分类
                {
                    switch (m_archivesList.at(nRow-3)->style1)
                    {
                    case 1:
                        return "一";
                        //break;
                    case 2:
                        return "二";
                        //break;
                    case 3:
                        return "三";
                        //break;
                    case 4:
                        return "四";
                        //break;
                    case 5:
                        return "五";
                        //break;
                    case 6:
                        return "六";
                        //break;
                    case 7:
                        return "七";
                        //break;
                    case 8:
                        return "八";
                        //break;
                    case 9:
                        return "九";
                        //break;
                    case 10:
                        return "十";
                        //break;
                    default:
                        break;
                    }
                }
                if(m_archivesList.at(nRow-3)->type == 2)//是二级分类,返回4-1,4-2等形式
                {
                    int style1 = m_archivesList.at(nRow-3)->style1;
                    int style2 = m_archivesList.at(nRow-3)->style2;
                    return QString::number(style1,10) + "-" + QString::number(style2,10);
                }
                if(m_archivesList.at(nRow-3)->style3 != 0)
                    return m_archivesList.at(nRow-3)->style3;
            }
            if(nColumn == 1)//材料题名
                return m_archivesList.at(nRow-3)->archive;
            if((nColumn == 2)&&(m_archivesList.at(nRow-3)->year != 0))//年
                return m_archivesList.at(nRow-3)->year;
            if((nColumn == 3)&&(m_archivesList.at(nRow-3)->month != 0))//月
                return m_archivesList.at(nRow-3)->month;
            if((nColumn == 4)&&(m_archivesList.at(nRow-3)->day != 0))//日
                return m_archivesList.at(nRow-3)->day;
            if((nColumn == 5)&&(m_archivesList.at(nRow-3)->page != 0))//页数
                return m_archivesList.at(nRow-3)->page;
            if(nColumn == 6)//备注
                return m_archivesList.at(nRow-3)->remark;

        default:
            return QVariant();
        }
    }
    /*
    FileRecord record = m_recordList.at(nRow);

        switch (role)
        {
        case Qt::TextColorRole:
            return QColor(Qt::white);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::DisplayRole:
        {
            if (nColumn == File_PATH_COLUMN)
                return record.strFilePath;
            return "";
        }
        case Qt::CheckStateRole:
        {
            if (nColumn == CHECK_BOX_COLUMN)
                return record.bChecked ? Qt::Checked : Qt::Unchecked;
        }
        default:
            return QVariant();
        }
    */


    return QVariant();
}

//手动修改表格数据
bool ArchivesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int nRow = index.row();
    int nColumn = index.column();

    if (data(index, role) != value) {
        // FIXME: Implement me!
        //qDebug()<<value;
        //修改表格数据后相应改变结构的值
        if(m_archivesList.at(nRow-3)->type == 3)//是材料目录行
        {
            int farchives = m_archivesList.at(nRow-3)->fArchives;//数据库中此条目录信息的唯一序号

            if(nColumn == 1)//材料题名
            {
                //数据库还没有写入，更新至此
                //m_query->exec(QString("update ArchivesInfo set E01Z111A = '123456' where farchives = '1'"));//.arg('12345'));
                m_archivesList.at(nRow-3)->archive = value.toString();
            }
            if(nColumn == 2)//年
                m_archivesList.at(nRow-3)->year = value.toInt();
            if(nColumn == 3)//月
                m_archivesList.at(nRow-3)->month = value.toInt();
            if(nColumn == 4)//日
                m_archivesList.at(nRow-3)->day = value.toInt();
            if(nColumn == 5)//页数
                m_archivesList.at(nRow-3)->page = value.toInt();
            if(nColumn == 6)//备注
                m_archivesList.at(nRow-3)->remark = value.toString();
        }


        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}
//设置单元格格式
Qt::ItemFlags ArchivesTableModel::flags(const QModelIndex &index) const
{
    int nRow = index.row();
    int nColumn = index.column();
    if (!index.isValid())
        //return Qt::NoItemFlags;
        return Qt::ItemIsEnabled;
    if(nRow <= 2)//前3行不可选不可编辑
        return ((!Qt::ItemIsEditable) & (!Qt::ItemIsSelectable));
    if(m_archivesList.at(nRow-3)->type == 1)//一级分类不可选不可编辑
        return ((!Qt::ItemIsEditable) & (!Qt::ItemIsSelectable));
    if(m_archivesList.at(nRow-3)->type == 2)//二级分类不可选不可编辑
        return ((!Qt::ItemIsEditable) & (!Qt::ItemIsSelectable));
    if(nColumn==0)//序号列不可选不可编辑
        return ((!Qt::ItemIsEditable) & (!Qt::ItemIsSelectable));
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ArchivesTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool ArchivesTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool ArchivesTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool ArchivesTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}
//清空结构数据
void ArchivesTableModel::setTableModelStructZero(ArchivesTableModel::tableModelStruct *stru)
{
    tableModelStruct *tbStruct = stru;
    tbStruct->fArchives = 0;//数据库中该条目录的序号
    tbStruct->fpaid = "";//数据库中该目录所属的人员编号
    tbStruct->style1 = 0;//一级分类
    tbStruct->style2 = 0;//二级分类
    tbStruct->style3 = 0;//三级分类
    tbStruct->type  = 0;
    tbStruct->archive = "";//目录内容;
    tbStruct->remark = "";//备注
    tbStruct->year = 0;
    tbStruct->month = 0;
    tbStruct->day = 0;
    tbStruct->page = 0;//页数
}
