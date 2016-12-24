#include "adminbd.h"
#include "ui_adminbd.h"
#include "admin.h"

#include "QSqlQueryModel"

AdminBD::AdminBD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminBD)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Просмотр локальной БД");
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM \"Stud\"");
    ui->tableView->setModel(model);

    QSqlQueryModel *model1 = new QSqlQueryModel;
    model1->setQuery("SELECT * FROM \"StudGroup\"");
    ui->tableView_2->setModel(model1);

    QSqlQueryModel *model2 = new QSqlQueryModel;
    model2->setQuery("SELECT * FROM \"Decane\"");
    ui->tableView_3->setModel(model2);

    QSqlQueryModel *model3 = new QSqlQueryModel;
    model3->setQuery("SELECT * FROM \"Faculty\"");
    ui->tableView_4->setModel(model3);

    QSqlQueryModel *model4 = new QSqlQueryModel;
    model4->setQuery("SELECT * FROM \"Test\"");
    ui->tableView_5->setModel(model4);

    QSqlQueryModel *model5 = new QSqlQueryModel;
    model5->setQuery("SELECT * FROM \"Task\"");
    ui->tableView_6->setModel(model5);
}

AdminBD::~AdminBD()
{
    delete ui;
}

void AdminBD::on_pushButton_clicked()
{
    Admin *w4 = new Admin();
     w4->show();
     close();
}
