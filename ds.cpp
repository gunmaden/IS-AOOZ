#include "analyzeres.h"
#include "ds.h"
#include "ui_ds.h"
#include <QBarCategoryAxis>
#include <QBarSet>
#include <QDebug>
#include <QLineSeries>
#include <QValueAxis>
#include <QMessageBox>
#include <QtMath>

double findSumDS(QList<double> doubleList){
    double result=0;
    foreach (double val, doubleList) {
       result+=val;
    }
    return result;
}

double avgFromIntListDS (QList <int> intList, int cond=1) {
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

double findSigmaDS (QList<int> intList, double avgVal){
    QList <double> l;
    foreach (double val, intList) {
        l.append(pow(val-avgVal,2.0));
    }
    return sqrt(1.0/double(intList.count())*findSumDS(l));
}

QList <double> firstPartDS(QList <double> doubleList, double avgVal, double sigma){
    QList <double> result;
    foreach (double val, doubleList) {
        result.append((val-avgVal)/sigma);
    }
    return result;
}

QList <double> secondPartDS(QList <int> intList, int count)
{
    QList <double> result;
    foreach (double val, intList) {
        result.append(sqrt(val/(count-val)));
    }
    return result;
}

QList <double> differentiateProbabilityDS(QList<double> first, QList<double> second){
    QList <double> result;
    for (int i=0;i<first.count();i++){
        result.append(first.at(i)*second.at(i));
    }
    return result;
}

DS::DS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DS)
{
    QList<double> avgMarksByQuestion;
    for (int column=0;column<sumsColumns.count();column++)
    {
        double sum=0;
        int counter=0;
        for(int row =0; row<trueMatrix.count();row++) {
            if (trueMatrix.at(row).at(column)>=40)
            {
                sum+=sumsRows.at(row);
                counter++;
            }
        }
        avgMarksByQuestion<<sum/counter;
    }
    const double avgMarksByTest=avgFromIntListDS(sumsRows);;
    QList <double> DS  = differentiateProbabilityDS(firstPartDS(avgMarksByQuestion, avgMarksByTest, findSigmaDS(sumsRows,avgMarksByTest)),secondPartDS(sumsColumns,sumsRows.count()));

    // ---------------------------------------------------------------------------- //

       ui->setupUi(this);
       this->setWindowIcon(QIcon(":/favicon.ico"));
       this->setWindowTitle("Дифференциирующая способность заданий теста");
       ui->tableWidget->setColumnCount(trueQuestionIds.count());
       ui->tableWidget->setHorizontalHeaderLabels(trueQuestionIds);
       qDebug()<<DS;
       double countRed = 0;
       double countYellow = 0;
       QStringList indexes;
       QStringList indYel;
       for (int i=0; i<trueQuestionIds.count(); i++)
       {
           QTableWidgetItem *it = new QTableWidgetItem();
           it->setText(QString("%1").arg(DS.at(i)));

           if (DS.at(i)<0) {
               it->setBackgroundColor(Qt::red);
               countRed++;
               indexes.append(QString("%1").arg(i+1));
           }
           else if(DS.at(i)<0.3) {
               it->setBackgroundColor(Qt::yellow);
               countYellow ++;
               indYel.append(QString("%1").arg(i+1));
           }
           else if (DS.at(i)>=0.3) it->setBackgroundColor(Qt::green);
           ui->tableWidget->setItem(0,i, it);
       }
       if (indexes.count()==0)
       ui->label->setText(QString("Вопросы дифференцирующая способность которых больше <font color=green><b>0.3</b></font> могут быть использованы в тесте.<br>"
                                  "Количество вопросов рекомендованных к редактированию составляет <b>%1</b> из <b>%2</b>.<br>"
                                  "Доля рекомендованных к редактированию вопросов составила <b>%3</b>.<br>"
                                  "Для повышения качества оценки знаний студентов рекомендованы к редактированию вопросы № <font color=orange><b>%4</b></font>.").arg(countRed+countYellow).arg(trueQuestionIds.count()).arg((countRed+countYellow)/trueQuestionIds.count()).arg(indYel.join(", ")));
      else if (indYel.count()==0)
           ui->label->setText(QString("Вопросы дифференцирующая способность которых больше <font color=green><b>0.3</b></font> могут быть использованы в тесте.<br>"
                                      "Количество вопросов рекомендованных к редактированию составляет <b>%1</b> из <b>%2</b>.<br>"
                                      "Доля рекомендованных к редактированию вопросов составила <b>%3</b>.<br>"
                                      "Для повышения качества оценки знаний студентов обязательному редактированию подлежат вопросы № <font color=red><b>%4</b></font>.<br>").arg(countRed+countYellow).arg(trueQuestionIds.count()).arg((countRed+countYellow)/trueQuestionIds.count()).arg(indexes.join(", ")));
      else
           ui->label->setText(QString("Вопросы дифференцирующая способность которых больше <font color=green><b>0.3</b></font> могут быть использованы в тесте.<br>"
                                      "Количество вопросов рекомендованных к редактированию составляет <b>%1</b> из <b>%2</b>.<br>"
                                      "Доля рекомендованных к редактированию вопросов составила <b>%3</b>.<br>"
                                      "Для повышения качества оценки знаний студентов обязательному редактированию подлежат вопросы № <font color=red><b>%4</b></font>.<br>"
                                      "Рекомендованы к редактированию вопросы № <font color=orange><b>%5</b></font>.").arg(countRed+countYellow).arg(trueQuestionIds.count()).arg((countRed+countYellow)/trueQuestionIds.count()).arg(indexes.join(", ")).arg(indYel.join(", ")));

       chartBuild(DS);
}

void DS::chartBuild(QList<double> DS)
{
    qDebug()<<DS;
        QChartView *chartView = new QChartView();
        QChart *chart = new QChart();
        QBarSeries *series = new QBarSeries();
        chart->addSeries(series);

        series->setName("DS");

        QBarSet * setList = new QBarSet("Задания теста");
        setList->append(DS);

        series->append(setList);
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(trueQuestionIds);
        chart->createDefaultAxes();
        chart->setAxisX(axisX, series);

        QValueAxis *axisY = new QValueAxis;
        axisY->setTitleText("Дифференциируюшая способность"); // RENAME ME!!!
        axisY->setTickCount(0.001);
        axisY->setMin(-1.0);
        axisY->setMax(1.0);
        chart->setAxisY(axisY);

        series->attachAxis(axisX);
        series->attachAxis(axisY);



        chartView->setRenderHint(QPainter::Antialiasing);
        chart->setTitle("DS");
        chartView->setChart(chart);
        chart->setTheme(QChart::ChartThemeBlueCerulean);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setAnimationDuration(1000);
        ui->frame->layout()->addWidget(chartView);
}

DS::~DS()
{
    delete ui;
}

void DS::on_pushButton_clicked()
{
    AnalyzeRes * ar = new AnalyzeRes();
    ar->show();
    close();
}
