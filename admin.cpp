#include "admin.h"
#include "ui_admin.h"
#include "admin_users.h"

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    Admin_users *w2 = new Admin_users();
     w2->setWindowTitle("Ведение справочника пользователей");
     w2->show();
     close();
}
