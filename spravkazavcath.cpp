#include "spravkazavcath.h"
#include "ui_spravkazavcath.h"
#include "zavcath.h"

SpravkaZavCath::SpravkaZavCath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpravkaZavCath)
{
    ui->setupUi(this);
}

SpravkaZavCath::~SpravkaZavCath()
{
    delete ui;
}

void SpravkaZavCath::on_pushButton_clicked()
{
    ZavCath *z = new ZavCath();
    z->show();
    close();
}
