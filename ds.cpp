#include "ds.h"
#include "ui_ds.h"

DS::DS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DS)
{
    ui->setupUi(this);
}

DS::~DS()
{
    delete ui;
}
