#include "zavcath.h"
#include "ui_zavcath.h"

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
