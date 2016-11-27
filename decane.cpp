#include "decane.h"
#include "ui_decane.h"
#include "klaster.h"

Decane::Decane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Decane)
{
    ui->setupUi(this);
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
    k->setWindowTitle("Настройка кластеризации");
    k->show();
    close();
}
