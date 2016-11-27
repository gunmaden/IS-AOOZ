#include "klaster.h"
#include "ui_klaster.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QCheckBox>
#include <QMessageBox>
#include <QSqlRecord>
#include <QButtonGroup>
#include <QSqlQueryModel>
#include <QList>

QList<QCheckBox *> lest;

klaster::klaster(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::klaster)
{
    ui->setupUi(this);
    QString s = QString(" SELECT DISTINCT t.\"studGroupName\" "
                        " FROM \"Task\" t "
                        " WHERE t.\"studGroupName\" IN ("
                        " SELECT stg.\"studGroupName\" from \"StudGroup\" stg, \"Decane\" d "
                        " WHERE (d.\"facultyName\" = stg.\"facultyName\" AND d.\"decaneName\" = '%1')) ").arg(FIO);
    QSqlQuery query (s);
    QVBoxLayout *l = new QVBoxLayout();
    while ( query.next() ){
        QCheckBox * box = new QCheckBox(query.value(0).toString());
        box->setChecked(false);
        connect(box,SIGNAL(toggled(bool)),this,SLOT(test()));
        l->addWidget(box);
    }
    ui->groupBox->setLayout(l);
    lest = ui->groupBox->findChildren<QCheckBox *>();
}

klaster::~klaster()
{
    delete ui;
}

void klaster::test(){
    qDebug()<<"???";
    QList<QCheckBox *> diff;
    QList<QCheckBox *> after;

    after = ui->groupBox->findChildren<QCheckBox *>();
    QString s;
    QStringList list;
    for (int i=0;i<after.count();i++){
         if (after.at(i)->checkState()==Qt::Checked)
          {list.append("'"+after.at(i)->text()+"'");}
     }

    s = list.join(',');
    QString req = QString(" SELECT DISTINCT tes.\"testName\""
                          " FROM \"Task\" AS task"
                          " INNER JOIN \"Test\" tes"
                          " ON tes.\"testID\" = task.\"testID\""
                          " WHERE task.\"studGroupName\""
                          " IN (%1) ").arg(s);

    QSqlQuery query (req);
    QVBoxLayout *l = new QVBoxLayout();
    ui->groupBox_2->setLayout(l);
    diff = ui->groupBox_2->findChildren<QCheckBox *>();
    for (int i=0;i<diff.count();i++)
        delete diff.at(i);
    while ( query.next() ){
        QCheckBox * box = new QCheckBox(query.value(0).toString());
        box->setChecked(false);
        ui->groupBox_2->layout()->addWidget(box);
    }

}
