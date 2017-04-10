#include "vairiety.h"
#include "ui_vairiety.h"

vairiety::vairiety(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vairiety)
{
    ui->setupUi(this);
}

vairiety::~vairiety()
{
    delete ui;
}
