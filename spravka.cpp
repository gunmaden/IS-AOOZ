#include "spravka.h"
#include "ui_spravka.h"
#include "admin.h"

Spravka::Spravka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spravka)
{
    ui->setupUi(this);
    this->setWindowTitle("Справка");
}

Spravka::~Spravka()
{
    delete ui;
}

void Spravka::on_pushButton_clicked()
{
    Admin *w = new Admin();
    w->show();
    close();
}
