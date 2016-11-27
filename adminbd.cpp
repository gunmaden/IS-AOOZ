#include "adminbd.h"
#include "ui_adminbd.h"

AdminBD::AdminBD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminBD)
{
    ui->setupUi(this);
}

AdminBD::~AdminBD()
{
    delete ui;
}
