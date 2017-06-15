#include "zavcath.h"
#include "ui_zavcath.h"
#include "analiz.h"
#include "widget.h"
#include "spravkazavcath.h"
#include "svodanalyz.h"

ZavCath::ZavCath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZavCath)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Окно работы Заведующего кафедрой");
}

ZavCath::~ZavCath()
{
    delete ui;
}

void ZavCath::on_pushButton_3_clicked()
{
    Widget *w = new Widget();
    w->show();
    close();
}

void ZavCath::on_pushButton_clicked()
{
    Analiz *an = new Analiz();
    an->show();

    SvodAnalyz *svod = new SvodAnalyz();
    svod->show();

    close();
}

void ZavCath::on_pushButton_2_clicked()
{
  SpravkaZavCath *s = new SpravkaZavCath();
s->show();
close();
}
