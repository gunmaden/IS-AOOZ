#include "vairiety.h"
#include "ui_vairiety.h"
#include "analyzeres.h"
#include <QDebug>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

int countList(QList<int> intList)
{
    int sum=0;
    foreach (int item, intList) {
        item>=40?sum++:false;
    }
    return sum;
}

vairiety::vairiety(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vairiety)
{
    QList <int> sumsFalseColumns, sumsFalseRows;
    for (int row=0;row<trueMatrix.count();row++)
    {
        sumsRows<<countList(trueMatrix.at(row));
        sumsFalseRows<<NS-countList(trueMatrix.at(row));
    }

    for (int col=0;col<NS; col++){
        QList <int> l;
        foreach (QList <int> list, trueMatrix) {
            l<<list.at(col);
        }
        sumsFalseColumns<<trueMatrix.count()-countList(l);
    }

    QList <double> precPosColumns, precNegColumns; // Доля верных/неверных ответов

    foreach (int i, sumsColumns) {
        precPosColumns<<double(i)/double(trueMatrix.count());
        precNegColumns<<double(trueMatrix.count()-i)/double(trueMatrix.count());
    }

    // Вариация

    for (int i=0;i<columnsMap.count();i++){
         trueQuestionIds.append(QString("%1 (%2)").arg(i+1).arg(columnsMap.at(i).second+1));
    }

    QList <double> variety;

    for (int i=0;i<precNegColumns.count();i++)
    {
        variety<<precNegColumns.at(i)*precPosColumns.at(i);
    }
//    qDebug()<<variety<<"\n"<<variety.count();
//    qDebug()<<precPosColumns<<"\n"<<precPosColumns.count();



    // ---------------------------------------------------------------------- //
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(variety.count());
    for (int i=0;i<variety.count();i++)
    {
        QTableWidgetItem *it = new QTableWidgetItem();
        it->setText(QString("%1").arg(variety.at(i)));
        ui->tableWidget->setItem(0,i, it);
    }
    ui->tableWidget->horizontalHeader()->hide();
    chartBuild(variety, precPosColumns);
}

void vairiety::chartBuild(QList <double> variety, QList <double> posPrec)
{
    QChartView *chartView = new QChartView();
    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();
    chart->addSeries(series);
    series->setName("Tasks variety");
    for (int i=0;i<variety.count();i++)
    {
           series->append(posPrec.at(i),variety.at(i));
           qDebug()<<variety.at(i);
    }
    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(0.1);
    axisX->setTitleText("Dolya vernyh"); // RENAME ME!!!
    axisX->setMin(0.0);
    axisX->setMax(1.0);
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Variety"); // RENAME ME!!!
    axisY->setTickCount(0.1);
    axisY->setMin(0.0);
    axisY->setMax(0.26);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);


    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setTitle("Variety");
    chartView->setChart(chart);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(1000);
    ui->frame->layout()->addWidget(chartView);
}



vairiety::~vairiety()
{
    delete ui;
}

void vairiety::on_pushButton_clicked()
{
    AnalyzeRes *ar = new AnalyzeRes();
    ar->show();
    close();
}
