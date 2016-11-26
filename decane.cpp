#include "decane.h"
#include "ui_decane.h"

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
