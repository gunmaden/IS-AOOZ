#include "admin.h"
#include "ui_admin.h"
#include "admin_users.h"
#include "adminbd.h"
#include "widget.h"
#include "spravka.h"
#include "QMessageBox"

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setWindowTitle("Окно работы Администратора");
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    Admin_users *w = new Admin_users();
     w->show();
     close();
}

void Admin::on_pushButton_2_clicked()
{
    AdminBD *w2 = new AdminBD();
    w2->show();
    close();
}

void Admin::on_pushButton_3_clicked()
{

    QMessageBox::information(this, "Инициализация информации", "Нет данных для добавления");
}
void Admin::on_pushButton_4_clicked()
{
    Spravka *w4 = new Spravka();
    w4->show();
    close();
}
void Admin::on_pushButton_5_clicked()
{
    Widget *w5 = new Widget();
    w5->show();
    close();
}
