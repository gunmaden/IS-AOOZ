#include "analyzeres.h"
#include "ui_analyzeres.h"
#include <QtMath>
#include <QDebug>
#include "analiz.h"
#include "ds.h"
#include "vairiety.h"
//#include "operations.cpp"

typedef QList < QList <int> > matrix;

matrix trueMatrix;
QStringList trueTaskIds, trueQuestionIds;
QList <int> sumsColumns, sumsRows, sumsFalseColumns, sumsFalseRows;
QList <QPair <QString, int> > idsMap;
QList <QPair <int, int> > columnsMap, rowsMap;
QMap <int, int> sizes;
int NS;

int count(QList<int> intList)
{
    int sum=0;
    foreach (int item, intList) {
        item>=40?sum++:false;
    }
    return sum;
}

matrix prepareMatrix(matrix m, int row, int col){
    for (int r=0;r<row;r++){
        QList <int> listRow;
        for (int c=0;c<col;c++)
        {
            listRow.append(-100);
        }
        m.append(listRow);
    }
    return m;
}

int neededSize(QMap<int,int> map)
{
    int max_val= map.values().at(0);
    int min_val=map.values().at(0);
    int sum_val=0;
    foreach (int value, map.values())
    {
        value>max_val?max_val=value:false;
        value<min_val?min_val=value:false;
        sum_val+=value;
    }
    if (double(min_val)/double(max_val)<0.85){
        return map.key(max_val);
    }
    else {
        return map.key(min_val);
    }
}

double findSum(QList<double> doubleList){
    double result=0;
    foreach (double val, doubleList) {
       result+=val;
    }
    return result;
}

double avgFromIntList (QList <int> intList, int cond=1) {
    double result=0.0;
    int counter=0;
    foreach (int val, intList) {
        if (val>=cond) {
            counter++;
            result+=val;
        }
    }
    result=result/counter;
    return result;
}


double findSigma (QList<int> intList, double avgVal){
    QList <double> l;
    foreach (double val, intList) {
        l.append(pow(val-avgVal,2.0));
    }
    return sqrt(1.0/double(intList.count())*findSum(l));
}

QList <double> firstPart(QList <double> doubleList, double avgVal, double sigma){
    QList <double> result;
    foreach (double val, doubleList) {
        result.append((val-avgVal)/sigma);
    }
    return result;
}

QList <double> secondPart(QList <int> intList, int count)
{
    QList <double> result;
    foreach (double val, intList) {
        result.append(sqrt(val/(count-val)));
    }
    return result;
}

QList <double> differentiateProbability(QList<double> first, QList<double> second){
    QList <double> result;
    for (int i=0;i<first.count();i++){
        result.append(first.at(i)*second.at(i));
    }
    return result;
}


AnalyzeRes::AnalyzeRes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeRes)
{
//    qDebug()<<marks;
    sizes.clear();
    foreach (QList <int> row, marks) {
        if (!sizes.contains(row.size()))
        {
            sizes[row.size()]=1;
        }
        else {
            sizes[row.size()]++;
        }
    }
    NS = neededSize(sizes);

    for (int i=0;i<marks.size();i++)
    {
        QList <int> row = marks.at(i);
        if (row.size()>NS){
            while (row.size()>NS){
                row.removeLast();
            }
        }
        else {
            while (row.size()<NS){
                row.append(0);
            }
        }
        marks.replace(i,row);
    }

    sumsColumns.clear();
    sumsRows.clear();
    for (int column=0 ; column<NS ; column++){
        int sum=0;
        for (int row=0 ; row < taskIds.size() ; row++ )
        {
            marks.at(row).at(column)>=40?sum++:false;
        }
        sumsColumns.append(sum);
    }

    foreach (QList <int> l, marks) {
        sumsRows.append(count(l));
    }
    columnsMap.clear();
    rowsMap.clear();
    for (int i=0; i < sumsColumns.size(); i++)
    {
        columnsMap.append(qMakePair(sumsColumns.at(i),i));
    }
    idsMap.clear();
    for (int i=0; i < sumsRows.size(); i++)
    {
        rowsMap.append(qMakePair(sumsRows.at(i),i));
        idsMap.append(qMakePair(taskIds.at(i),i));
    }

    std::sort(columnsMap.begin(),columnsMap.end());
    std::reverse(columnsMap.begin(),columnsMap.end());
    std::sort(rowsMap.begin(),rowsMap.end());
    std::reverse(rowsMap.begin(),rowsMap.end());

    trueMatrix.clear();
    trueMatrix = prepareMatrix(trueMatrix, rowsMap.count(), columnsMap.count());
    trueTaskIds.clear();
    trueQuestionIds.clear();
    for (int row=0;row<marks.size();row++)
    {
        trueMatrix.replace(row,marks.at(rowsMap.at(row).second));
        trueTaskIds.append(idsMap.at(rowsMap.at(row).second).first);
    }

    for (int row=0;row<marks.size();row++)
    {
        QList <int> junk = trueMatrix.at(row);
        for (int column=0; column<NS; column++)
        {
            junk.replace(column,trueMatrix.at(row).at(columnsMap.at(column).second));
        }
        trueMatrix.replace(row,junk);
    }

    sumsColumns.clear();
    sumsRows.clear();

    for (int row=0;row<trueMatrix.count();row++)
    {
        sumsRows<<count(trueMatrix.at(row));
    }

    for (int col=0;col<NS; col++){
        QList <int> l;
        foreach (QList <int> list, trueMatrix) {
            l<<list.at(col);
        }
        sumsColumns<<count(l);
    }

    for (int i=0;i<columnsMap.count();i++){
         trueQuestionIds.append(QString("%1 (%2)").arg(i+1).arg(columnsMap.at(i).second+1));
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ //
    ui->setupUi(this);
    ui->tableWidget->setRowCount(trueMatrix.count());
    ui->tableWidget->setColumnCount(NS);
    ui->tableWidget->setVerticalHeaderLabels(trueTaskIds);
    ui->tableWidget_2->setRowCount(trueMatrix.count());
    ui->tableWidget_3->setColumnCount(NS);
    ui->tableWidget->setHorizontalHeaderLabels(trueQuestionIds);
    ui->tableWidget_2->setVerticalHeaderLabels(trueTaskIds);
    ui->tableWidget_3->setHorizontalHeaderLabels(trueQuestionIds);
    for( int row=0; row<trueMatrix.count();row++)
    {
        for (int col=0;col<NS;col++)
        {
            QTableWidgetItem *it = new QTableWidgetItem();
            it->setText(QString("%1").arg(trueMatrix.at(row).at(col)));
            ui->tableWidget->setItem(row,col, it);
        }
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString("%1").arg(sumsRows.at(row)));
        ui->tableWidget_2->setItem(row,0,item);
    }

    for (int col=0;col<NS; col++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString("%1").arg(sumsColumns.at(col)));
            ui->tableWidget_3->setItem(0,col,item);
    }
}

AnalyzeRes::~AnalyzeRes()
{
    delete ui;
}

void AnalyzeRes::on_pushButton_clicked()
{
    vairiety *va = new vairiety();
    va->show();
    close();
}

void AnalyzeRes::on_pushButton_3_clicked()
{
    Analiz *a = new Analiz();
    a->show();
    close();
}

void AnalyzeRes::on_pushButton_2_clicked()
{
    DS * ds = new DS();
    ds->show();
    close();
}
