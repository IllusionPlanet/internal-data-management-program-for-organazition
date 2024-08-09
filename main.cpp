#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include "mainwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //连接的MYSQL的数据库驱动
        db.setHostName("rm-bp1oo27t8762xhlob0o.mysql.rds.aliyuncs.com");         //主机名
        db.setPort(3306);                    //端口
        db.setDatabaseName("site_cn_75db");          //数据库名
        db.setUserName("lab_1968484204");              //用户名
        db.setPassword("7aca4804c5eb_#@Aa");            //密码
        db.open();
    MainWidget w;
    w.show();
    return app.exec();
}
