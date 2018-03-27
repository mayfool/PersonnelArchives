#include "archivesdlg.h"
#include "ui_archivesdlg.h"
#include "mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include "archivestablemodel.h"
#include "readonlydelegate.h"

ArchivesDlg::ArchivesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArchivesDlg)
{
    ui->setupUi(this);
}

ArchivesDlg::ArchivesDlg(QWidget *parent, QString pid) :
    QDialog(parent),
    ui(new Ui::ArchivesDlg)
{
    ui->setupUi(this);

    m_parent = parent;
    MainWindow * mainWindow = (MainWindow*) parent;  //获取父窗口指针
    m_accdb = mainWindow->getAccessDB();
    m_pid = pid;

    //设置窗体
    //this->setGeometry(0,0,800,600);
    /*QPalette pal(this->palette());//设置窗体背景颜色
    pal.setColor(QPalette::Background, QColor(169,169,169));//Qt::black); //设置背景
    this->setAutoFillBackground(true);
    this->setPalette(pal);*/
    //this->setStyleSheet("background-color:rgb(169,169,169);");
    //设置布局
    //QHBoxLayout *layout = new QHBoxLayout;
    //layout->setContentsMargins(10,50,10,50);

    //setLayout(layout);
    //设置表格
    //QTableWidget *tableWidget = new QTableWidget(this);
    //ui->tableWidget->resize(800, 1000);  //设置表格
    //ui->tableView->setRowCount(20);     //设置行数
    ArchivesTableModel *tableModel = new ArchivesTableModel(this);
    ui->tableView->setModel(tableModel);

    setTableCol();//设置表格标题,要放在setModel()之后。如果在设置View类的Model之前就调用该方法是不会起作用的
    //设置表格式
    //tableWidget->resize(50,700);
    //tableView->setModel(m_tableModel);
    //tableView->resize(50,700);
}

ArchivesDlg::~ArchivesDlg()
{
    delete ui;
}

QString ArchivesDlg::getPid()
{
    return m_pid;
}

AccessDB *ArchivesDlg::getAccdb()
{
    return m_accdb;
}

void ArchivesDlg::setTableCol()
{
    //ui->tableView->setColumnCount(7);   //设置列数
    ui->tableView->verticalHeader()->setDefaultSectionSize(40);//设置所有行的默认行高
    ui->tableView->setFont(QFont("宋体",14));//所有单元格字体
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中一个目标
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//以行为单位选择
    ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);//材料目录表可编辑，鼠标点击进入编辑状态
    ui->tableView->verticalHeader()->setHidden(true);
    ui->tableView->horizontalHeader()->setHidden(true);

    ui->tableView->horizontalHeader()->resizeSection(0,50);//设置列宽：序号
    ui->tableView->horizontalHeader()->resizeSection(1,550);//材料题名
    ui->tableView->horizontalHeader()->resizeSection(2,60);//年
    ui->tableView->horizontalHeader()->resizeSection(3,35);//月
    ui->tableView->horizontalHeader()->resizeSection(4,35);//日
    ui->tableView->horizontalHeader()->resizeSection(5,35);//页数
    ui->tableView->horizontalHeader()->resizeSection(6,100);//备注


    //tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    //tableWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    //layout->addWidget(tableWidget);

    //tableWidget->setShowGrid(false); //设置不显示格子线
    //tableWidget->setStyleSheet();
    //设置表格第一行


    ui->tableView->setRowHeight(0,60);//设置行高
    ui->tableView->setRowHeight(1,30);//设置行高
    ui->tableView->setRowHeight(2,30);//设置行高
    ui->tableView->setSpan(0,0,1,9);//合并单元格"干 部 人 事 档 案 目 录"
    ui->tableView->setSpan(1,0,2,1);//合并单元格"序号"
    ui->tableView->setSpan(1,1,2,1);//合并单元格"材 料 题 名"
    ui->tableView->setSpan(1,2,1,3);//合并单元格"材料形成时间"
    ui->tableView->setSpan(1,5,2,1);//合并单元格"页数"
    ui->tableView->setSpan(1,6,2,1);//合并单元格"备注"
    //ui->tableView->set
    //ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    //ui->tableView->setItemDelegateForColumn(0, readOnlyDelegate);
    //对材料目录各列设置输入委托
    TitleDelegate *titleDelegate = new TitleDelegate(this);
    ui->tableView->setItemDelegateForColumn(1,titleDelegate);
    YearDelegate *yearDelegate = new YearDelegate(this);
    ui->tableView->setItemDelegateForColumn(2,yearDelegate);
    MonthDelegate *monthDelegate = new MonthDelegate(this);
    ui->tableView->setItemDelegateForColumn(3,monthDelegate);
    DayDelegate *dayDelegate = new DayDelegate(this);
    ui->tableView->setItemDelegateForColumn(4,dayDelegate);
    PageDelegate *pageDelegate = new PageDelegate(this);
    ui->tableView->setItemDelegateForColumn(5,pageDelegate);
    ui->tableView->setItemDelegateForColumn(6,titleDelegate);//对备注也使用材料题名的委托
/*
    item = new QTableWidgetItem("序号");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(1,0,item);


    item = new QTableWidgetItem("材 料 题 名");
    item->setFont(QFont("宋体",18,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(1,1,item);

    item = new QTableWidgetItem("材料形成时间");
    item->setFont(QFont("宋体",14,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(1,2,item);

    item = new QTableWidgetItem("年");
    item->setFont(QFont("宋体",14,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(2,2,item);
    item = new QTableWidgetItem("月");
    item->setFont(QFont("宋体",14,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(2,3,item);
    item = new QTableWidgetItem("日");
    item->setFont(QFont("宋体",14,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(2,4,item);

    ui->tableWidget->setSpan(1,5,2,1);//合并单元格
    item = new QTableWidgetItem("页数");
    item->setFont(QFont("宋体",14,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(1,5,item);

    ui->tableWidget->setSpan(1,6,2,1);//合并单元格
    item = new QTableWidgetItem("备注");
    item->setFont(QFont("宋体",14,QFont::Bold));//设置字体，大小，加粗
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置文字对齐方式
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);//设置单元格不可点击不接受输入
    ui->tableWidget->setItem(1,6,item);
*/

}

