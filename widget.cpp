#include "widget.h"
#include "ui_widget.h"
#include "admin.h"
#include "decane.h"
#include "zavcath.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQueryModel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Авторизация");
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


                QSqlQuery query;
                QString e = QString("SELECT * FROM \"Users\" WHERE login = '%1'").arg(login);
                query.exec(e);
                qDebug()<<query.value(0);
                if(!query.isActive())
                qDebug()<< "!!! Database Error !!!";
                QString log,ps,ut;

                while (query.next()) {
                 IDD =query.value(0).toString();
                 FIO = query.value(1).toString();
                 ut = query.value(2).toString();
                 log = query.value(3).toString();
                 ps = query.value(4).toString();
                }
                qDebug()<<FIO;

                if (login == log && parol == ps && ut =="1")
                {
                    Decane *w22 = new Decane();
                    w22->show();
                    close();
                 }
                else if (login == log && parol == ps && ut =="2")
                {
                    Admin *w2 = new Admin();
                     w2->setWindowTitle("Окно работы Админа");
                     w2->show();
                     close();

                 }
                else if (login == log && parol == ps && ut =="3")
                {
                    ZavCath *zc = new ZavCath();
                    zc->setWindowTitle("Окно работы зав. кафедрой");
                    zc->show();
                    close();
                }
                else QMessageBox::information(this, "Ошибка!", "Неверный логин или пароль!");
}
