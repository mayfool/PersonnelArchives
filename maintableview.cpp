#include "maintableview.h"

MainTableView::MainTableView(QWidget *parent): QTableView(parent)
{
    this->setSelectionMode(QAbstractItemView::SingleSelection);//只能单行选择。ExtendedSelection可以选中多个目标
    this->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选择
    this->resizeColumnsToContents();//根据内容自动调节列宽
    //表头字体加粗
    QFont font =this->horizontalHeader()->font();
    font.setBold(true);
    this->horizontalHeader()->setFont(font);
    //设置隔行换色
    this->setAlternatingRowColors (true);//隔行换色
    this->setStyleSheet( "QTableView{background-color: rgb(240, 255, 255);"
    "alternate-background-color: rgb(230, 230, 250);}" );

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    this->setSortingEnabled(true);//点击表头排序
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);//启动使用右键菜单，用信号槽策略
    //ui->personBasicInfoTableView->setFont(QFont("Helvetica"));
    QHeaderView *header = this->horizontalHeader();
    header->setStretchLastSection(true);
    header->setSectionsMovable(true);//点击表头可拖动
    header->setContextMenuPolicy(Qt::CustomContextMenu);//重要，启动右键菜单策略
    //SQL查询模型
   /*QSqlQueryModel *model = new QSqlQueryModel(this);
   model->setQuery("select * from A0120170809162223",db);
   model->setHeaderData(0,Qt::Horizontal,tr("ID号"));
   model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
   ui->personBasicInfoTableView->setModel(model);*/

}
/*
MainTableView::SetHead(AccessDB *accdb)
{
    //隐藏,根据orderid对列排序
    if(accdb->queryDB("select * from A0120130414102455_S"))//A0120170809162223_S
    {
        int count = 0;
        while(accdb->getQuery()->next())
        {
            //qDebug()<<accdb->getQuery()->value(3).toString();
            this->setColumnHidden(count,!accdb->getQuery()->value(16).toBool());//隐藏不显示的列
            this->setColumnWidth(count,accdb->getQuery()->value(7).toInt());//设置列宽
            QHeaderView *header = this->horizontalHeader();
            if(!accdb->getQuery()->value(16).toBool())//让显示
                header->moveSection(count,accdb->getQuery()->value(2).toInt());//对列排序
            count++;
        }
    }
}*/

MainTableView::~MainTableView()
{

}
