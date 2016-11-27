#include "admin_users.h"
#include "ui_admin_users.h"
#include "admin_addus.h"
#include "admin_delus.h"
#include "QSqlQueryModel"

Admin_users::Admin_users(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_users)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM \"Users\"");
    ui->tableView->setModel(model);
}

Admin_users::~Admin_users()
{
    delete ui;
}

void Admin_users::on_pushButton_clicked()
{
    Admin_addus *w2 = new Admin_addus();
     w2->setWindowTitle("Добавить пользователя");
     w2->show();
     close();
}

void Admin_users::on_pushButton_2_clicked()
{
    Admin_delus *w3 = new Admin_delus();
     w3->setWindowTitle("Удалить пользователя");
     w3->show();
     close();
}