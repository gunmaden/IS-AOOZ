#include "svodanalyz.h"
#include "ui_svodanalyz.h"
#include "QDebug"
#include <QSqlquery>
#include <QStringBuilder>

SvodAnalyz::SvodAnalyz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SvodAnalyz)
{
    ui->setupUi(this);
   this->setWindowTitle("Краткий отчет по тестам Вашей кафедры");

    QString s = QString("SELECT * from \"AnalyzeRez\" "
                        " where \"Cath\" =  "
                        " (SELECT \"cathedraID\" FROM \"Cathedra\" WHERE \"cathedraFIO\" ~ '%1') ").arg(FIO);
    QSqlQuery q(s);
    QStringList response;
    int i=0;
    while (q.next())
    {
        i++;
        qDebug()<< i;
        response.append(QString("Тест «%1» с надежностью %2,"
                        " количество вопросов %3,"
                        " из которых необходимо редактировать %4"
                        " и рекомендуется к редактированию %5 \n").arg(
                            q.value(1).toString(),
                            q.value(2).toString(),
                            q.value(3).toString(),
                            q.value(4).toString(),
                            q.value(5).toString()));
    }

    qDebug()<<response;
    ui->label->setText(response.join("\n\n"));
}

SvodAnalyz::~SvodAnalyz()
{
    delete ui;
}

void SvodAnalyz::on_pushButton_clicked()
{
    close();
}
