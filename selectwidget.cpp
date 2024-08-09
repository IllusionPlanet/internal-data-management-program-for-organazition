#include "selectwidget.h"
#include "ui_selectwidget.h"

SelectWidget::SelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectWidget)
{
    ui->setupUi(this);
    chooseButtonGroup = new QButtonGroup;
    chooseButtonGroup->addButton(ui->workRadioButton, 0);
    chooseButtonGroup->addButton(ui->dormRadioButton, 1);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget_2->setColumnCount(2);
    QStringList headerLables, headerLables2;
    headerLables << tr("获奖时间") << tr("奖励名") << tr("受奖员工代号");
    headerLables2 << tr("类别") << tr("数量");
    ui->tableWidget->setHorizontalHeaderLabels(headerLables);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setHorizontalHeaderLabels(headerLables2);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->setRowCount(0);
}

SelectWidget::~SelectWidget()
{
    delete ui;
}

void SelectWidget::on_returnButton_clicked(){
    emit display(0);
}

void SelectWidget::on_select1Button_clicked(){
    QString equipmentName = ui->S1lineEdit->text();
    if(ui->S1lineEdit->text() == ""){
        QMessageBox::about(NULL, "提示", "不能为空！");
    }
    QSqlQuery q;
    q.exec("SELECT `项目` FROM `部门`JOIN `设备` ON `部门`.部门名 = `设备`.面向部门 WHERE `设备名` = '"
        + equipmentName + "'");
    if(q.first())
        ui->getDepartmentLabel->setText(q.value(0).toString());
}

void SelectWidget::on_select2Button_clicked(){
    ui->tableWidget->clearContents();
    QString departmentName = ui->S2lineEdit->text();
    if(ui->S2lineEdit->text() == ""){
        QMessageBox::about(NULL, "提示", "不能为空！");
    }
    QSqlQuery q;
    int i = 0;
    q.exec("SELECT * FROM `奖励` WHERE `受奖员工代号` IN (SELECT `代号` FROM `员工` WHERE `部门` = '"
           + departmentName + "')");
    if(q.first()){
        do{
            i++;
        }while(q.next());
    }
    ui->tableWidget->setRowCount(i);
    i = 0;
    if(q.first()){
        do{
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(q.value(0).toString()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(q.value(1).toString()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(q.value(2).toString()));
            i++;
        }while(q.next());
    }
}

void SelectWidget::on_select3Button_clicked(){
    ui->tableWidget_2->clearContents();
    int s = chooseButtonGroup->checkedId();
    QSqlQuery q;
    int i = 0;
    switch (s){
    case 0:
        q.exec("SELECT `类别`, COUNT(*) FROM `地点` GROUP BY `类别`");
        break;
    case 1:
        q.exec("SELECT `类别`, COUNT(*) FROM `宿舍区` GROUP BY `类别`");
        break;
    default:
        QMessageBox::about(NULL, "提示", "操作有误！");
    }
    if(q.first()){
        do{
            i++;
        }while(q.next());
    }
    ui->tableWidget_2->setRowCount(i);
    i = 0;
    if(q.first()){
        do{
            ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(q.value(0).toString()));
            ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(QString::number(q.value(1).toInt())));
            i++;
        }while(q.next());
    }
}
