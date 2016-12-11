#include "prepare.h"
#include "ui_prepare.h"
#include <qDebug>

template<typename T>
void f(T s)
{
    qDebug()<<s;
}

prepare::prepare(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prepare)
{
    ui->setupUi(this);
    this->setWindowTitle("Подготовка к кластеризации");
    f(students);
}

prepare::~prepare()
{
    delete ui;
}
