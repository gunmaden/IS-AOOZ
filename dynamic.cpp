#include "dynamic.h"
#include "ui_dynamic.h"
#include "decane.h"
#include <QChart>
#include <QChartView>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QCheckBox>
#include <QScatterSeries>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QMainWindow>

QT_CHARTS_USE_NAMESPACE

dynamic::dynamic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dynamic)
{
    //    QStringList groups;
    //    QStringList disciples;
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Динамический отчет");
    ui->dateEdit->setMinimumDate(QDate(2010,1,1));
    //    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit_2->setMinimumDate(QDate(2010,1,1));
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_2->setMaximumDate(QDate::currentDate());

    QString groupsQueryBody = QString(" SELECT DISTINCT "
                                      " task.\"studGroupName\" "
                                      " FROM \"Task\" AS task, \"Test\" tes "
                                      " WHERE tes.\"testID\" = task.\"testID\" AND "
                                      " task.\"studGroupName\" IN (SELECT stg.\"studGroupName\" "
                                      " FROM \"StudGroup\" stg, \"Decane\" d "
                                      " WHERE (d.\"facultyName\" = stg.\"facultyName\" AND "
                                      " d.\"decaneName\" = '%1')) "
                                      " GROUP BY task.\"studGroupName\", tes.\"testName\" ").arg(FIO);
    QStringList disciplesIds;
    QString disciplesQueryBody = QString (" SELECT DISTINCT tes.\"testName\", task.\"testID\" "
                                          " FROM \"Task\" AS task, \"Test\" tes "
                                          " WHERE tes.\"testID\" = task.\"testID\" AND "
                                          " task.\"studGroupName\" IN (%1) ").arg(groupsQueryBody);
    setLayouts();

    QSqlQuery groupsQuery(groupsQueryBody);
    while ( groupsQuery.next() ){
        QCheckBox * box = new QCheckBox(groupsQuery.value(0).toString());
        box->setChecked(false);
        ui->groupBox->layout()->addWidget(box);
        connect(box,SIGNAL(toggled(bool)),this,SLOT(chartBuildByGroups()));
    }

    QSqlQuery disciplesQuery(disciplesQueryBody);
    while ( disciplesQuery.next() ){
        QCheckBox * box = new QCheckBox(disciplesQuery.value(0).toString());
        disciplesIds.append(disciplesQuery.value(1).toString());
        box->setChecked(false);
        ui->groupBox_2->layout()->addWidget(box);
        connect(box,SIGNAL(toggled(bool)),this,SLOT(chartBuildByDisciples()));
    }
}



void dynamic::setLayouts(){
    QVBoxLayout *l1 = new QVBoxLayout();
    ui->groupBox->setLayout(l1);
    QVBoxLayout *l2 = new QVBoxLayout();
    ui->groupBox_2->setLayout(l2);
}

void dynamic::limitCheckBoxes()
{
    int disciplesCheckboxesCounter=0;
    int groupsCheckboxesCounter=0;

    QList<QCheckBox *> disciplesCheckboxes;
    QList<QCheckBox *> groupsCheckboxes;

    groupsCheckboxes = ui->groupBox->findChildren<QCheckBox *>();
    disciplesCheckboxes = ui->groupBox_2->findChildren<QCheckBox *>();

    foreach (QCheckBox *box, disciplesCheckboxes) {
        if (box->checkState()==Qt::Checked)
            disciplesCheckboxesCounter++;
        if (disciplesCheckboxesCounter!=0)
            break;
    }

    if (disciplesCheckboxesCounter!=0)
        foreach (QCheckBox *box, groupsCheckboxes) {
            if (box->checkState()!=Qt::Checked)
                box->setDisabled(true);
        }
    else {
        foreach (QCheckBox *box, groupsCheckboxes) {
            box->setDisabled(false);
        }
    }

    foreach (QCheckBox *box, groupsCheckboxes) {
        if (box->checkState()==Qt::Checked)
            groupsCheckboxesCounter++;
        if (groupsCheckboxesCounter!=0)
            break;
    }
    if (groupsCheckboxesCounter!=0)
        foreach (QCheckBox *box, disciplesCheckboxes) {
            if (box->checkState()!=Qt::Checked)
                box->setDisabled(true);
        }
    else {
        foreach (QCheckBox *box, disciplesCheckboxes) {
            box->setDisabled(false);
        }
    }

}

void dynamic::chartBuildByDisciples()
{
    limitCheckBoxes();
    QDate from = ui->dateEdit->date();
    QDate to = ui->dateEdit_2->date();

    QStringList discipless;

    QList<QCheckBox *> disciplesCheckboxes;
    disciplesCheckboxes = ui->groupBox_2->findChildren<QCheckBox *>();

    foreach (QCheckBox *box, disciplesCheckboxes) {
        if (box->checkState()==Qt::Checked)
            discipless<<box->text();
    }

    QList <QLineSeries *> seriesList;
    foreach (QString g, discipless) {
        QString req = QString(" SELECT task.\"taskMark100\", task.\"taskReceive\" "
                              " FROM \"Task\" task "
                              " JOIN \"Test\" test "
                              " ON task.\"testID\" = test.\"testID\" "
                              " WHERE (test.\"testName\" IN ('%1')) "
                              " AND (task.\"taskReceive\" BETWEEN '%2' AND '%3') "
                              " AND (task.\"taskMark100\" !=0 ) ").arg(g).arg(from.toString(Qt::ISODate)).arg(to.toString(Qt::ISODate));
//        qDebug()<<req;

        QLineSeries *series = new QLineSeries();
        series->setName(g);

        QSqlQuery q(req);
        QStringList dates, rawDates;
        QList <double> results, rawResults;
        while (q.next()) {
            rawDates<<q.value(1).toDate().toString(Qt::ISODate);
            dates<<q.value(1).toDate().toString(Qt::ISODate);
            rawResults<<q.value(0).toDouble();
        }

        dates.removeDuplicates();
        foreach (QString date, dates) {
            double avg = 0;
            int counter = 0;
            for (int i=0;i<rawDates.count();i++)
            {
                if (rawDates.at(i)==date)
                {
                    avg+=rawResults.at(i);
                    counter++;
                }
            }
            avg = avg/counter;
            results<<avg;
        }

        qDebug()<<dates;
        qDebug()<<results;

        for (int i=0;i<dates.count();i++)
        {
            QDateTime dt;
            dt = QDateTime::fromString(dates.at(i),"yyyy-MM-dd");
//            qDebug()<<dt.toString(Qt::ISODate);
            series->append(dt.toMSecsSinceEpoch(), results.at(i));
        }
        seriesList<<series;
    }
    prepareChart(seriesList);
}

void dynamic::prepareChart(QList <QLineSeries *> seriesList)
{
    QChartView *chartView = new QChartView();
    QChart *chart = new QChart();

    foreach (QLineSeries *ls, seriesList)
    {
        QLineSeries * series = ls;
        chart->addSeries(series);
    }

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd.MM.yyyy");
    axisX->setTitleText("Дата");
    axisX->setMin(ui->dateEdit->dateTime());
    axisX->setMax(ui->dateEdit_2->dateTime());
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Баллы");
    axisY->setMin(0.0);
    axisY->setMax(100.0);
    chart->addAxis(axisY, Qt::AlignLeft);

    foreach (auto series, chart->series()) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setTitle("Динамический график");
    chartView->setChart(chart);

    for (int i=0;i<ui->frame->layout()->count();i++)
    {
        ui->frame->layout()->removeItem(ui->frame->layout()->itemAt(i));
    }
    ui->frame->layout()->addWidget(chartView);

}


void dynamic::chartBuildByGroups()
{
    limitCheckBoxes();
    QDate from = ui->dateEdit->date();
    QDate to = ui->dateEdit_2->date();
    QStringList groups;

    QList<QCheckBox *> groupsCheckboxes;
    groupsCheckboxes = ui->groupBox->findChildren<QCheckBox *>();

    foreach (QCheckBox *box, groupsCheckboxes) {
        if (box->checkState()==Qt::Checked)
            groups<<box->text();
    }

    QList <QLineSeries *> seriesList;
    foreach (QString g, groups) {
        QString req = QString(" SELECT "
                              " task.\"taskMark100\", "
                              " \"taskReceive\" "
                              " FROM \"Task\" task "
                              " WHERE (\"taskReceive\" BETWEEN '%1' AND '%2') AND "
                              " task.\"studGroupName\" IN ('%3') AND task.\"taskMark100\"!=0 ").arg(from.toString(Qt::ISODate)).arg(to.toString(Qt::ISODate)).arg(g);
        QLineSeries *series = new QLineSeries();
        series->setName(g);
        QSqlQuery q(req);
        QStringList dates, rawDates;
        QList <double> results, rawResults;
        while (q.next()) {
            rawDates<<q.value(1).toDate().toString(Qt::ISODate);
            dates<<q.value(1).toDate().toString(Qt::ISODate);
            rawResults<<q.value(0).toDouble();
        }

        dates.removeDuplicates();
        foreach (QString date, dates) {
            double avg = 0;
            int counter = 0;
            for (int i=0;i<rawDates.count();i++)
            {
                if (rawDates.at(i)==date)
                {
                    avg+=rawResults.at(i);
                    counter++;
                }
            }
            avg = avg/counter;
            results<<avg;
        }

        qDebug()<<dates;
        qDebug()<<results;

        for (int i=0;i<dates.count();i++)
        {
            QDateTime dt;
            dt = QDateTime::fromString(dates.at(i),"yyyy-MM-dd");
            series->append(dt.toMSecsSinceEpoch(), results.at(i));
        }
        seriesList<<series;
    }
    prepareChart(seriesList);
}

dynamic::~dynamic()
{
    delete ui;
}

void dynamic::on_pushButton_clicked()
{
    Decane *d = new Decane();
    d->show();
    close();
}

void dynamic::on_dateEdit_dateChanged(const QDate &date)
{
    QList<QCheckBox *> disciplesCheckboxes;
    QList<QCheckBox *> groupsCheckboxes;

    groupsCheckboxes = ui->groupBox->findChildren<QCheckBox *>();
    disciplesCheckboxes = ui->groupBox_2->findChildren<QCheckBox *>();

    int d=0,g=0;
    foreach (QCheckBox *box, disciplesCheckboxes) {
            if (box->checkState()==Qt::Checked)
            {
                d++;
                break;
            }
    }
        foreach (QCheckBox *box, groupsCheckboxes) {
                if (box->checkState()==Qt::Checked)
                {
                    g++;
                    break;
                }
        }

    if (d!=0)
        chartBuildByDisciples();
    else if (g!=0) {
        chartBuildByGroups();
    }
}

void dynamic::on_dateEdit_2_userDateChanged(const QDate &date)
{
    QList<QCheckBox *> disciplesCheckboxes;
    QList<QCheckBox *> groupsCheckboxes;

    groupsCheckboxes = ui->groupBox->findChildren<QCheckBox *>();
    disciplesCheckboxes = ui->groupBox_2->findChildren<QCheckBox *>();

    int d=0,g=0;
    foreach (QCheckBox *box, disciplesCheckboxes) {
            if (box->checkState()==Qt::Checked)
            {
                d++;
                break;
            }
    }
    foreach (QCheckBox *box, groupsCheckboxes) {
                if (box->checkState()==Qt::Checked)
                {
                    g++;
                    break;
                }

    }

    if (d!=0)
        chartBuildByDisciples();
    else if (g!=0) {
        chartBuildByGroups();
    }
}
