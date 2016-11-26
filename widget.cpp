#include "widget.h"
#include "ui_widget.h"
#include <QtSql/QSqlDatabase>
#include<qDebug>
#include<QSqlQuery>
#include <QVariant>
#include<QList>
#include<QMessageBox>
#include <QSqlRecord>
#include<QSqlQueryModel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

QString FIO, IDD;



void Widget::on_pushButton_2_clicked()
{
    close();
}


void Widget::on_pushButton_clicked()
{

    if (ok==false)
    {
      QMessageBox::information(this, "Ошибка!", "Ошибка подключения к базе данных!");
    }

                QString login = ui->lineEdit->text();
                QString parol= ui->lineEdit_2->text();
                QString gr;

                QSqlQuery query;
                QString e = QString("SELECT * FROM auth WHERE \"login\" = '%1'").arg(login);
                query.exec(e);
                qDebug()<<query.value(0);
                if(!query.isActive())
                qDebug()<< "!!! Database Error !!!";
                QString log,ps,ut;

                while (query.next()) {
                 IDD =query.value(0).toString();
                 FIO = query.value(1).toString();
                 log = query.value(2).toString();
                 ps = query.value(3).toString();
                 gr = query.value(4).toString();
                 ut=query.value(5).toString();
                }






}
