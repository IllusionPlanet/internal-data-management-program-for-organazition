#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QButtonGroup>

namespace Ui {
class SelectWidget;
}

class SelectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectWidget(QWidget *parent = nullptr);
    ~SelectWidget();

private:
    Ui::SelectWidget *ui;
    QButtonGroup *chooseButtonGroup;

signals:
    void display(int number);

private slots:
    void on_returnButton_clicked();
    void on_select1Button_clicked();
    void on_select2Button_clicked();
    void on_select3Button_clicked();
};

#endif // SELECTWIDGET_H
