#include "spravkadecane.h"
#include "ui_spravkadecane.h"
#include "decane.h"
SpravkaDecane::SpravkaDecane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpravkaDecane)
{
    ui->setupUi(this);
}

SpravkaDecane::~SpravkaDecane()
{
    delete ui;
}

void SpravkaDecane::on_pushButton_clicked()
{
    Decane *d = new Decane();
    d->show();
    close();
}
