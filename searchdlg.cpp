#include "searchdlg.h"
#include "ui_searchdlg.h"
#include <mainwindow.h>


SearchDlg::SearchDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDlg)
{
    ui->setupUi(this);
    m_parent = parent;
    MainWindow * mainWindow = (MainWindow*) parent;  //获取父窗口指针
    tableModel = mainWindow->getTableModel();
    tableView = mainWindow->getTableView();
    accdb = mainWindow->getAccessDB();
    //设置对话框
    this->setWindowTitle(tr("查找"));
    //this->resize(500,300);
    ui->resultLabel->setText(tr(""));
    ui->resultLabel->setStyleSheet("color:red;");
    ui->searchStyleGroupBox->hide();
    ui->selectBtn->setCheckable(true);
    //
    //ui->formLayout->setSpacing(10);
    //ui->formLayout->setContentsMargins(10,10,10,10);

    ui->searchLineEdit->setFocus();
    //填充查找范围列表框

    QStringList strlist;
    for (int i=0;i<tableModel->columnCount();i++)
        if(!mainWindow->getTableView()->isColumnHidden(i))
            strlist.append(tableModel->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
    ui->searchComboBox->addItems(strlist);

}

SearchDlg::~SearchDlg()
{
    delete ui;
}

void SearchDlg::on_cancelBtn_clicked()
{
    this->close();
}

void SearchDlg::on_searchBtn_clicked()
{
    QString strCol = ui->searchComboBox->currentText();//获取选择的查找范围
    ui->resultLabel->setText(tr(""));
    qDebug()<<strCol;
    //获取查找范围是哪一列
    int colCount = 0;//列序号
    for (colCount = 0;colCount<tableModel->columnCount();colCount++)
        if(strCol == tableModel->headerData(colCount,Qt::Horizontal,Qt::DisplayRole).toString())
            break;
    qDebug()<<colCount;
    //
    QString strSearch;//遍历表格
    QString strSearchLE = ui->searchLineEdit->text().trimmed();//用户输入，去除两端空格
    qDebug()<<strSearchLE;
    int rowCount = 0;
    //解决rowCount()只能获取256条的问题
    while(tableModel->canFetchMore())
        tableModel->fetchMore();

    if(ui->locRadioBtn->isChecked())//查找模式选择定位
    {
        tableModel->select();
        for(rowCount = 0;rowCount<tableModel->rowCount();rowCount++)
        {
            //QModelIndex index = ;
            strSearch = tableModel->data(tableModel->index(rowCount,colCount)).toString();//获取单元格数据
            if(strSearch.startsWith(strSearchLE))
                break;
        }
        qDebug()<<strSearch<<rowCount;
        if(rowCount == tableModel->rowCount())//没找到
        {
            tableView->selectRow(0);
            ui->resultLabel->setText(tr("未找到数据！"));
           // tableView->setFocus();
        }
        else//找到了
        {
            tableView->scrollToBottom();
            tableView->selectRow(rowCount);//选择找到的数据
            this->close();
        }
    }
    if(ui->filterRadioBtn->isChecked())//查找模式选择过滤
    {
        tableModel->select();
        QString dataColName;//数据库中表头的名字
        if(accdb->queryDB("select * from A0120170809162223_S"))
        {

            for(int i = 0;i<colCount+1;i++)
                accdb->getQuery()->next();
            dataColName = accdb->getQuery()->value(3).toString();//获取数据库中表头名称
            qDebug()<<dataColName;
        }

        //tableModel->setFilter(QString("A0101 like '%%1%'").arg(strSearchLE));//.arg(dataColName));//.arg(strSearchLE));
        //tableModel->setFilter(QString("A0101 like '%张%'"));//.arg(dataColName));//.arg(dataColName));//.arg(strSearchLE));
        tableModel->setFilter(QString("%1 like '%%2%'").arg(dataColName).arg(strSearchLE));
        tableModel->select();
        if(tableModel->rowCount()!=0)
            this->close();
        else
            ui->resultLabel->setText(tr("未找到数据！"));
    }
}

void SearchDlg::on_selectBtn_toggled(bool checked)//显隐窗口
{
    ui->searchStyleGroupBox->setVisible(checked);
    if(checked)
        ui->selectBtn->setText(tr("选项(&T)<<"));
    else
        ui->selectBtn->setText(tr("选项(&T)>>"));
}
