#include "prepare.h"
#include "ui_prepare.h"
#include "klaster.h"
#include <qDebug>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QCheckBox>
#include <QMessageBox>
#include <QSqlRecord>
#include <QButtonGroup>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QList>
#include <QStringList>
#include <QSqltablemodel>

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
    QStringList students = getStudents();
    f(students);
    QList <QStringList> studResults = getMarks(students);
    prepareTable(students,studResults);
    fillGroupBox();
}

QList <QStringList> prepare::getMarks(QStringList students){
    QList <QStringList> studResults;
    foreach (QString dis, disciples) {
        QStringList lst;
        foreach (QString stud, students) {

            QString req = QString("SELECT round(avg(t.\"taskMark100\")) "
                                  " FROM \"Task\" t "
                                  " JOIN \"Test\" tes "
                                  " ON t.\"testID\"=tes.\"testID\" "
                                  " WHERE t.\"studName\" = '%1' AND tes.\"testName\" = '%2' "
                                  " GROUP BY tes.\"testName\" ").arg(stud,dis);
            QSqlQuery query(req);
            if (query.size()!=0)
                while (query.next()){
                    lst.append(query.value(0).toString());
                }
            else {
                lst.append("0");
            }
        }
        studResults.append(lst);
    }
    return studResults;
}

QStringList prepare::getStudents(){
    QStringList students;
    QStringList list;
    foreach (QString s, groups) {
        list.append(QString("'%1'").arg(s));
    };
    QString getStudReq = QString("SELECT DISTINCT st.\"studNameFirst\" "
                                 " from \"Stud\" st, \"StudGroup\" sg "
                                 " WHERE ("
                                 " st.\"old_studGroupID\"=sg.\"studGroupID\" "
                                 " and sg.\"studGroupName\" in (%1)) ").arg(list.join(","));
    QSqlQuery getStudentsQuery(getStudReq);
    while ( getStudentsQuery.next() ){
        students.append(getStudentsQuery.value(0).toString());
    }
    qSort(students);
    return students;
}

void prepare::prepareTable(QStringList students, QList <QStringList> studResults){
    ui->tableWidget->setRowCount(students.count());
    ui->tableWidget->setColumnCount(disciples.count());
    ui->tableWidget->setHorizontalHeaderLabels(disciples);
    ui->tableWidget->setVerticalHeaderLabels(students);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    fillTable(studResults);
}

void prepare::fillTable(QList<QStringList> lst){
    int column=0;
    foreach (QStringList l, lst) {
        int row=0;
        foreach (QString v, l) {
            QTableWidgetItem *it = new QTableWidgetItem(v);
            ui->tableWidget->setItem(row,column,it);
            f(v);
            row++;
        }
        column++;
    }
}

void prepare::fillGroupBox(){
    QList<QLabel *> labels = ui->groupBox->findChildren<QLabel *>();
    labels.at(0)->setText(QString("Выбранные группы: %1").arg(groups.join(', ')));
    labels.at(1)->setText(QString("Выбранные дисциплины: %1").arg(disciples.join(',')));
    labels.at(2)->setText(QString("Количество студентов: %1").arg(getStudents().count()));
}

prepare::~prepare()
{
    delete ui;
}
