#include "modifywidget.h"
#include "ui_modifywidget.h"

ModifyWidget::ModifyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyWidget)
{
    ui->setupUi(this);
}

ModifyWidget::~ModifyWidget()
{
    delete ui;
}

void ModifyWidget::on_returnButton_clicked(){
    emit display(0);
}

void ModifyWidget::on_insertPushButton_clicked(){
    QString SN = ui->SNLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString department = ui->departmentLineEdit->text();
    QString dorm = ui->dormLineEdit->text();
    if(ui->SNLineEdit->text() == ""){
        QMessageBox::about(NULL, "提示", "员工号为主键，不能为空！");
    }
    else if(ui->nameLineEdit->text() == ""){
        QMessageBox::about(NULL, "提示", "代号不能为空！");
    }
    else if(ui->departmentLineEdit->text() == ""){
        QMessageBox::about(NULL, "提示", "所属部门不能为空！");
    }
    else if(ui->dormLineEdit->text() == ""){
        QMessageBox::about(NULL, "提示", "宿舍区不能为空！");
    }
    else {
        QSqlQuery q;
        q.exec("INSERT INTO `员工`( `员工号`,`代号`,`部门`,`宿舍区号`) VALUES('"
               + SN + "','" + name + "','" + department + "','" + dorm + "')");
        QMessageBox::about(NULL, "提示", "插入成功！");
    }
}

void ModifyWidget::on_deleteDepartmentPushButton_clicked(){
    QString deleteDepartment = ui->deleteDepartmentLineEdit->text();
    QSqlQuery q1, q2;
    q1.exec("DELETE FROM `部门` WHERE `部门名` = '" + deleteDepartment + "'");
    q2.exec("SELECT COUNT( *) FROM `部门` WHERE `部门名` = '" + deleteDepartment + "'");
    if(q2.first() && ui->deleteDepartmentLineEdit->text() != ""){
        if (q2.value(0).toInt() == 0){
            QMessageBox::about(NULL, "提示", "删除成功！");
        }
        else {
            QMessageBox::about(NULL, "提示", "删除失败！");
        }
    }
    else {
        QMessageBox::about(NULL, "提示", "不能为空！");
    }
}

void ModifyWidget::on_deleteLocationPushButton_clicked(){
    QString deleteLocation = ui->deleteLocationLineEdit->text();
    QSqlQuery q1, q2;
    q1.exec("DELETE FROM `地点` WHERE `地点` = '" + deleteLocation + "'");
    q2.exec("SELECT COUNT( *) FROM `地点` WHERE `地点` = '" + deleteLocation + "'");
    if(q2.first() && ui->deleteLocationLineEdit->text() != ""){
        if (q2.value(0).toInt() == 0){
            QMessageBox::about(NULL, "提示", "删除成功！");
        }
        else {
            QMessageBox::about(NULL, "提示", "删除失败，存在外键参照！");
        }
    }
    else {
        QMessageBox::about(NULL, "提示", "不能为空！");
    }
}
