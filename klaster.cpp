#include "klaster.h"
#include "ui_klaster.h"
#include "prepare.h"
#include "decane.h"
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
#include <QSqltablemodel>

QList<QCheckBox *> lest;

template<typename T>
void f(T s)
{
    qDebug()<<s;
}

klaster::klaster(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::klaster)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Настройка кластеризации");
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
    test();
}

klaster::~klaster()
{
    delete ui;
}

void klaster::clear_labels(){
    QList<QLabel *> labels = ui->groupBox_2->findChildren<QLabel *>();
    for (int i=0;i<labels.count();i++){
        delete labels.at(i);
    }
}

void klaster::test(){
    //    qDebug()<<"???";
    QList<QCheckBox *> diff;
    QList<QCheckBox *> after;

    after = ui->groupBox->findChildren<QCheckBox *>();
    QString s;
    QStringList list;
    for (int i=0;i<after.count();i++){
        if (after.at(i)->checkState()==Qt::Checked)
        {list.append("'"+after.at(i)->text()+"'");}
    }
    s = list.join("),(");
    QString group_sel = QString("SELECT DISTINCT"
                                " task.\"studGroupName\", "
                                " tes.\"testName\" "
                                " FROM \"Task\" AS task, \"Test\" tes "
                                " WHERE tes.\"testID\" = task.\"testID\" AND "
                                " task.\"studGroupName\" IN (SELECT stg.\"studGroupName\" "
                                " FROM \"StudGroup\" stg, \"Decane\" d "
                                " WHERE (d.\"facultyName\" = stg.\"facultyName\" AND "
                                " d.\"decaneName\" = '%1')) "
                                " GROUP BY task.\"studGroupName\", tes.\"testName\" ").arg(FIO);

    QString countfilters = QString("SELECT %1 cof").arg(list.count());
    f(countfilters);
    QString groups_fil = QString("(%1)").arg(s);
    //    qDebug()<<groups_fil;
    QString filters = QString (" SELECT * FROM "
                               " (VALUES %1) "
                               " AS gr_fil(gr_fil) ").arg(groups_fil);

    QString req_body = QString("SELECT q.\"testName\" "
                               " FROM q, filters_group, count_filters "
                               " WHERE q.\"studGroupName\" IN (filters_group.gr_fil) "
                               " GROUP BY q.\"testName\", cof "
                               " HAVING count(q.\"studGroupName\") = count_filters.cof ");

    QString req = QString(" WITH q AS (%1), "
                          " count_filters AS (%2), "
                          " filters_group AS (%3) "
                          " %4 ").arg(group_sel, countfilters, filters, req_body);
    QSqlQuery query (req);
    QVBoxLayout *l = new QVBoxLayout();
    ui->groupBox_2->setLayout(l);
    diff = ui->groupBox_2->findChildren<QCheckBox *>();

    for (int i=0;i<diff.count();i++)
        delete diff.at(i);

    int counter = 0;

    while ( query.next() ){
        QCheckBox * box = new QCheckBox(query.value(0).toString());
        box->setChecked(false);
        ui->groupBox_2->layout()->addWidget(box);

        counter++;
    }

    f(QString("Counter: %1").arg(counter));

    if (counter == 0)
    {
        if (list.count() != 0){
            QLabel * label = new QLabel("У выбранных групп нет общих предметов");
            clear_labels();
            ui->groupBox_2->layout()->addWidget(label);
        }
        else {
            QLabel * label = new QLabel("Выберите хотя бы одну группу");
            clear_labels();
            ui->groupBox_2->layout()->addWidget(label);
        }
    }
    else {
        clear_labels();
    }
}

QStringList groups;
QStringList disciples;

void clearstlst(QStringList lst){
    if (lst.count()!=0)
        lst.clear();
}

void klaster::on_pushButton_clicked()
{

    clearstlst(groups);
    clearstlst(disciples);
    foreach (QCheckBox *box, ui->groupBox->findChildren<QCheckBox *>()) {
        if (box->checkState()==Qt::Checked)
            groups.append(box->text());
    }
    foreach (QCheckBox *box, ui->groupBox_2->findChildren<QCheckBox *>()) {
        if (box->checkState()==Qt::Checked)
            disciples.append(box->text());
    }
    prepare *p = new prepare();
    p->show();
    close();
}

void klaster::on_toolButton_clicked()
{
    Decane *d = new Decane();
    d->show();
    close();
}
