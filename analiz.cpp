#include "analiz.h"
#include "ui_analiz.h"

Analiz::Analiz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analiz)
{
    ui->setupUi(this);
}

Analiz::~Analiz()
{
    delete ui;
}
