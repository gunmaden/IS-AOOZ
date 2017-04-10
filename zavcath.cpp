#include "zavcath.h"
#include "ui_zavcath.h"
#include "analiz.h"

ZavCath::ZavCath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZavCath)
{
    ui->setupUi(this);
}

ZavCath::~ZavCath()
{
    delete ui;
}

void ZavCath::on_pushButton_3_clicked()
{
    close();
}

void ZavCath::on_pushButton_clicked()
{
    Analiz *an = new Analiz();
    // TODO: Написать тайтл
    an->show();
    close();
}
