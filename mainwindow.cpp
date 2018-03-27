#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口菜单和工具栏
    QMenu *fileMenu = ui->menuBar->addMenu(tr("文件(&F)"));
    QAction *actionFile = fileMenu->addAction(QIcon(":/image/images/xiuxian-icon.png"),tr("人员查找(&S)"));
    actionFile->setShortcut(QKeySequence("Ctrl+O"));//设置快捷方式
    ui->mainToolBar->addAction(actionFile);//在工具栏添加动作


    m_tableview = new MainTableView(this);
    ui->verticalLayout->addWidget(m_tableview);

    QString exePath = QCoreApplication::applicationDirPath();//可执行文件路径
    qDebug()<<exePath;
    accdb = new AccessDB();
    if(accdb->connectDB("mysql"))
    {
        m_tableModel = new QSqlTableModel(this,accdb->getSqlDB());
        m_tableModel->setTable("person");//("A0120170809162223");
        m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//编辑策略，所有改变直到调用submitAll()或revertAll()函数
        m_tableModel->select();

        //设置表格式
        m_tableview->setModel(m_tableModel);
        //m_tableview->SetHead(accdb);
        //设置表头名称
        if(accdb->queryDB("select * from A0120130414102455_S"))//A0120170809162223_S"))
        {
            int count = 0;
            while(accdb->getQuery()->next())
            {
                m_tableModel->setHeaderData(count,Qt::Horizontal,accdb->getQuery()->value(4).toString());//设置表头名称
                count++;
            }
        }
        //对第6列（姓名）升序排序
        m_tableModel->setSort(6, Qt::AscendingOrder);
        m_tableModel->select();
    }
    //人员基本信息表的右键菜单
    connect(m_tableview, SIGNAL(customContextMenuRequested(const QPoint)),
            this, SLOT(on_m_tableView_customContextMenuRequested(const QPoint)));//this是datatable所在窗口
    //表头右键菜单
    connect(m_tableview->horizontalHeader(),SIGNAL(customContextMenuRequested(const QPoint)),
            this, SLOT(on_headerView_customContextMenuRequested(const QPoint)));//this是datatable所在窗口
    //connect(ui->searchBtn,SIGNAL(clicked()),this,SLOT(on_searchBtn_clicked()));
}

MainWindow::~MainWindow()
{
    accdb->closeDB();
    delete ui;
}

MainTableView* MainWindow::getTableView()
{
    return m_tableview;
}

QSqlTableModel *MainWindow::getTableModel()
{
    return m_tableModel;
}

AccessDB *MainWindow::getAccessDB()
{
    return accdb;
}

void MainWindow::on_m_tableView_customContextMenuRequested(const QPoint &pos)
{
    if(tableViewMenu)//保证同时只存在一个menu，及时释放内存
    {
        delete tableViewMenu;
        tableViewMenu = NULL;
    }
    tableViewMenu = new QMenu(this->m_tableview);

    QAction *actionOpenArchives = tableViewMenu->addAction(QIcon(":/image/images/xiuxian-icon.png"),tr("档案目录(&O)"));
    QAction *actionPersonnelInfo = tableViewMenu->addAction(tr("人员信息(&I)"));

    connect(actionOpenArchives, SIGNAL(triggered(bool)), this, SLOT(on_showArchivesDlg()));
     /*connect(descendSortAction, SIGNAL(triggered(bool)), this, SLOT(sort_descend()));
    connect(filterAction, SIGNAL(triggered(bool)), this, SLOT(show_filter_dlg()));
    connect(reshowAction, SIGNAL(triggered(bool)), this, SLOT(reshow_data()));*/
    tableViewMenu->exec(QCursor::pos());//在当前鼠标位置显示
}

void MainWindow::on_headerView_customContextMenuRequested(const QPoint &pos)
{
    if(headerViewMenu)//保证同时只存在一个menu，及时释放内存
    {
        delete headerViewMenu;
        headerViewMenu = NULL;
    }
    headerViewMenu = new QMenu(m_tableview->horizontalHeader());

    QAction *actionOpenArchives = headerViewMenu->addAction(QIcon(":/image/images/xiuxian-icon.png"),tr("属性(&O)"));
    QAction *descendSortAction = headerViewMenu->addAction(tr("隐藏(&I)"));

    headerViewMenu->exec(QCursor::pos());//在当前鼠标位置显示
}

void MainWindow::on_showArchivesDlg()
{
    //QMessageBox::information(NULL,"档案目录","档案目录");
    //获得鼠标右键选择行的人员PID
    QModelIndex index = m_tableview->currentIndex();
    QString pid = m_tableModel->record(index.row()).value("fpid").toString();

    ArchivesDlg *archivesDlg = new ArchivesDlg(this,pid);
    archivesDlg->show();
}

void MainWindow::on_searchBtn_clicked()
{
    if(searchDlg)
    {
        delete searchDlg;
        searchDlg = NULL;
    }
    searchDlg = new SearchDlg(this);
    searchDlg->show();
}

void MainWindow::on_personnelBasicInfo_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//转到人员基本信息表
}

void MainWindow::on_infoSearchBtn_clicked()
{
    ui->stackedWidget1->setCurrentIndex(0);
}

void MainWindow::on_photoBtn_clicked()
{
    ui->stackedWidget1->setCurrentIndex(1);
}

void MainWindow::on_workBtn_clicked()
{
    ui->stackedWidget1->setCurrentIndex(2);
}

void MainWindow::on_storeBtn_clicked()
{
    ui->stackedWidget1->setCurrentIndex(3);
}

void MainWindow::on_databaseBtn_clicked()
{
    ui->stackedWidget1->setCurrentIndex(4);
}
