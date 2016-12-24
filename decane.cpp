#include "decane.h"
#include "ui_decane.h"
#include "dynamic.h"
#include "klaster.h"

Decane::Decane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Decane)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Окно работы Декана");
}

Decane::~Decane()
{
    delete ui;
}

void Decane::on_pushButton_5_clicked()
{
    close();
}

void Decane::on_pushButton_clicked()
{
    klaster *k = new klaster();
    k->show();
    close();
}

void Decane::on_pushButton_2_clicked()
{
    dynamic *d = new dynamic();
    d->show();
    close();
}
