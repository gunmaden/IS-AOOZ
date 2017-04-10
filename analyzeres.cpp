#include "analyzeres.h"
#include "ui_analyzeres.h"

AnalyzeRes::AnalyzeRes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeRes)
{
    ui->setupUi(this);
}

AnalyzeRes::~AnalyzeRes()
{
    delete ui;
}
