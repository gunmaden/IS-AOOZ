#include "prepare.h"
#include "ui_prepare.h"
#include "klaster.h"
#include <QtMath>
#include <QDebug>
#include <QSqlDatabase>
#include <QDebug>
#include <QChart>
#include <QChartView>
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
#include <QSqlTableModel>
#include <QScatterSeries>
#include <QMainWindow>
QT_CHARTS_USE_NAMESPACE

int clastersCount;
prepare::prepare(QWidget *parent, int clasterCount) :
    QWidget(parent),
    ui(new Ui::prepare)
{
    ui->setupUi(this);
    clastersCount=clasterCount;
    this->setWindowIcon(QIcon(":/favicon.ico"));
    ui->tableWidget->clear();
    this->setWindowTitle("Подготовка к кластеризации");
    QStringList students = getStudents();
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
            row++;
        }
        column++;
    }
}

void prepare::fillGroupBox(){
    QList<QLabel *> labels = ui->groupBox->findChildren<QLabel *>();
    labels.at(0)->setText(QString("Выбранные группы: %1").arg(groups.join(", ")));
    labels.at(1)->setText(QString("Выбранные дисциплины: %1").arg(disciples.join(", ")));
    labels.at(2)->setText(QString("Количество студентов: %1").arg(getStudents().count()));
}

prepare::~prepare()
{
    delete ui;
}

double dist(double a,double b){
    return pow((a-b),2);
}

double max(QList<double> lst){
    double max = lst.at(0);
    foreach (double val, lst) {
        if (val > max)
            max = val;
    }
    return max;
}

double min(QList<double> lst){
    double min = lst.at(0);
    foreach (double val, lst) {
        if (val < min)
            min = val;
    }
    return min;
}

double av_max(QList< QList <double> > lst){
    double sum = 0;
    foreach (QList <double> l, lst) {
        sum += max(l);
    }
    return sum / lst.count();
}

double av_min(QList< QList <double> > lst){
    double sum = 0;
    foreach (QList <double> l, lst) {
        sum += min(l);
    }
    return sum / lst.count();
}

QList <QList <double> > initClasters(QList<QList <double> > rawData, int count){
    double max,min;
    max = av_max(rawData);
    min = av_min(rawData);
    double d = (max-min)/(count-1);
    QList <double> lst;
    for (int i = 0;i<count;i++)
    {
        lst.append(max-d*i);
    }
    QList <QList <double> > out;
    foreach (QList <double> tuple, rawData) {
        out.append(lst);
    }
    qDebug()<<out;
    return out;
}

QList <QList <double> > iterClaster(QList <QList <double> > rawData, QList <QList <double> > massCenters){
    QList <QList <double> > test;
    for (int mass=0;mass<massCenters.at(0).count();mass++)
    {
        QList <double> massCol;
        for (int i=0;i<rawData.at(0).count();i++){
            double sum = 0;
            for (int col = 0; col<rawData.count();col++){
                sum+=dist(rawData.at(col).at(i),massCenters.at(col).at(mass));
            }
            massCol.append(sqrt(sum));
        }
        test.append(massCol);
    }
    qDebug()<<test;
    return test;
}

QList <QList <int> >  internMatrix (QList <QList <double> > clasterTable){
    QList <QList <int> > intern;
    for (int col=0;col<clasterTable.count();col++)
    {
        QList <int> emp;
        for (int row=0;row<clasterTable.at(0).count();row++)
        {
            emp.append(0);
        }
        intern.append(emp);
    }
    for (int row=0;row<clasterTable.at(0).count();row++){
        QList <double> roww;
        for (int col=0;col<clasterTable.count();col++)
        {
            roww.append(clasterTable.at(col).at(row));
        }
        double mininrow = min(roww);
        for (int col=0;col<clasterTable.count();col++)
        {
            if (mininrow == clasterTable.at(col).at(row)){
                intern[col].replace(row,1);
            }
        }
    }
    qDebug()<<intern;
    return intern;
}

QList < QList <double> > recalcMassCenters(QList <QList <int> >  matrix, QList <QList <double> > rawData){
    QList <QList <double> > out;
    for (int dcol=0;dcol<rawData.count();dcol++)
    {
        QList <double> inner;
        for (int mcol=0;mcol<matrix.count();mcol++)
        {
            int countInner = 0;
            double markSum = 0;
            for (int mrow=0;mrow<matrix.at(mcol).count();mrow++)
            {
                if (matrix.at(mcol).at(mrow)==1)
                {
                    countInner++;
                    markSum+=rawData.at(dcol).at(mrow);
                }
            }
            double result = markSum/countInner;
            inner.append(result);
        }
        out.append(inner);
    }
    qDebug()<<out;
    return out;
}

QList <QList <int> >  clasterize(QList <QList <double> > rawData, int clastersCount){
    QList <QList <double> >  clasters = initClasters(rawData,clastersCount);
    QList <QList <int> > prev, d;
    int counter = 0;
    while(true){
        prev = d;
        QList <QList <double> > t = iterClaster(rawData,clasters);
        d = internMatrix(t);
        if (d==prev){
            break;
        }
        clasters = recalcMassCenters(d,rawData);
        counter++;
    }
    qDebug()<<"Matrix:"<<d;
    qDebug()<<"Iter:"<<counter;
    return d;
}




QList <QList <int> > resulter(QList<QList <double> > rawData, int clastersCount)
{
    QList <QList <int> > finalResult = clasterize(rawData,clastersCount);
    return finalResult;
}


void prepareChart(QList <QList <int> > clastersMatrix, QList <QList <double> > marks){
    QChartView *chartView = new QChartView();
    QChart *chart = new QChart();
    double size = 10.0;

    if (marks.count() == 1)
    {
        marks<<marks.at(0);
    }
    for (int matrix=0; matrix<clastersMatrix.count();matrix++)
    {
        QScatterSeries *series = new QScatterSeries();
        series->setName(QString("Кластер №%1").arg(matrix+1));
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series->setMarkerSize(size);
        for (int row=0;row<clastersMatrix.at(matrix).count();row++)
        {
            if (clastersMatrix.at(matrix).at(row)==1)
            {
                qDebug()<<"("<<marks.at(0).at(row)<<";"<<marks.at(1).at(row)<<")";
                series->append(marks.at(0).at(row), marks.at(1).at(row));
            }
        }
        chart->addSeries(series);

    }
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->setTitle("Результат расчета кластеризации");
    chart->createDefaultAxes();
    chart->axisX()->setMax(110);
    chart->axisX()->setMin(0);
    chart->axisY()->setMax(110);
    chart->axisY()->setMin(0);
    chart->setDropShadowEnabled(false);

    chartView->setChart(chart);
    qDebug()<<"Chart: "<<chart->maximumHeight()<<chart->maximumSize()<<chart->maximumWidth();
    qDebug()<<"ChartView: "<<chartView->maximumHeight()<<chartView->maximumSize()<<chartView->maximumWidth();
    QMainWindow *w = new QMainWindow();
    w->setWindowIcon(QIcon(":/favicon.ico"));
    w->setCentralWidget(chartView);
    w->show();
}



void prepare::on_pushButton_2_clicked()
{

    QList <QList <double> > marks;
    QStringList indexesForDelete;
    for(int row=0; row<ui->tableWidget->rowCount();row++)
    {
        QString fios;
        fios = ui->tableWidget->verticalHeaderItem(row)->text();
        qDebug()<<fios;
        bool flag = false;
        for (int col=0;col<ui->tableWidget->columnCount();col++)
        {
            if (ui->tableWidget->item(row,col)->text().toDouble() != 0)
            {
                flag = true;
                break;
            }
        }
        if (flag==false)
        {
            indexesForDelete.append(fios);
        }
        else {
            QSqlQuery q;
            q.prepare(QString("SELECT avg(t.\"taskMark100\") FROM \"Task\" t WHERE \"studName\"='%1'").arg(fios));
            q.exec();
            q.first();
            double avgMark = q.record().value(0).toDouble();
            for (int col=0;col<ui->tableWidget->columnCount();col++)
            {
                if (ui->tableWidget->item(row,col)->text().toDouble() < 1.0)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(avgMark));
                    ui->tableWidget->setItem(row,col,item);
                }
            }
        }
    }
    foreach (QString i, indexesForDelete) {
        for (int row=0;row<ui->tableWidget->rowCount();row++)
        {
            if (i==ui->tableWidget->verticalHeaderItem(row)->text())
            {
                ui->tableWidget->removeRow(row);
                break;
            }
            ui->tableWidget->repaint();
        }
    }

    for (int col=0;col<ui->tableWidget->columnCount();col++)
    {
        QList <double> marksCols;
        for(int row=0; row<ui->tableWidget->rowCount();row++)
        {
            marksCols<<ui->tableWidget->item(row,col)->text().toDouble();
        }
        marks<<marksCols;
    }
   QList <QList <int> > clastersMatrix = resulter(marks,clastersCount);
   prepareChart(clastersMatrix,marks);
}

void prepare::on_pushButton_clicked()
{
 groups.clear();
 disciples.clear();
 klaster *k = new klaster();
 k->show();
 close();
}
