#include "analiz.h"
#include "ui_analiz.h"
#include <QDebug>
#include "zavcath.h"
#include <QSqlQuery>
#include <QList>
#include <QMessageBox>
#include "analyzeres.h"
typedef QList < QList <int> > matrix;

QStringList testNames, testIds;
matrix marks;
QStringList taskIds;
QString testId;

Analiz::Analiz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analiz)
{

    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Матрица результатов тестирования");
    QString s = QString("SELECT * from \"Test\" "
                        " where \"cathedraID\" =  "
                        " (SELECT \"cathedraID\" FROM \"Cathedra\" WHERE \"cathedraFIO\" ~ '%1') ").arg(FIO);
//    qDebug()<<s;
    QSqlQuery q (s);
    testNames.clear();
    testIds.clear();
    while (q.next()) {
        testIds << q.value(0).toString();
        testNames << q.value(1).toString();
    }
    ui->comboBox->addItems(testNames);
}

Analiz::~Analiz()
{
    delete ui;
}

void Analiz::on_pushButton_2_clicked()
{
    ZavCath *zc = new ZavCath();
    zc->show();
    close();
}

void Analiz::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<testIds.at(index);
    testId = testIds.at(index);
    QSqlQuery q3(QString(" SELECT DISTINCT \"taskID\", string_agg( to_char(\"taskContentNum\",'999'), ',' ) as \"tasks\", string_agg( to_char(\"taskContentMark\",'999'), ',' ) as \"taskMarks\" "
                         " FROM (SELECT * FROM \"TaskContent\" ORDER BY \"taskID\", \"taskContentNum\" ) as \"table\" "
                         " WHERE \"taskID\" in (SELECT \"taskID\" FROM \"Task\" where \"testID\"=%1) "
                         " GROUP BY \"taskID\" "
                         " ORDER BY \"taskID\" ").arg(testId));

    QStringList taskNums;
    QStringList taskResults;
    taskIds.clear();
    while (q3.next()) {
        taskIds.append(q3.value(0).toString());
        taskNums.append(q3.value(1).toString());
        taskResults.append(q3.value(2).toString());
    }

    marks.clear();
    foreach (QString row, taskResults)
    {
        QList <int> rowItems;
        foreach (QString item, row.split(',')) {
            rowItems.append(item.toInt());
        }
        marks.append(rowItems);
    }
    ui->tableWidget->clear();
    if (marks.count()!=0)
    {
    ui->pushButton->setDisabled(false);
    ui->tableWidget->setRowCount(marks.count());
    ui->tableWidget->setColumnCount(marks.first().count());
    ui->tableWidget->setVerticalHeaderLabels(taskIds);

    for( int row=0; row<marks.count();row++)
    {
        for (int col=0;col<marks.at(row).count();col++)
        {
            QTableWidgetItem *it = new QTableWidgetItem();
            it->setText(QString("%1").arg(marks.at(row).at(col)));
            if (marks.at(row).at(col) <40)
            it->setBackgroundColor(Qt::gray);
            else it->setBackgroundColor(Qt::green);
            ui->tableWidget->setItem(row,col, it);
        }
    }
    }
    else {
        ui->pushButton->setDisabled(true);
        QMessageBox::information(this, "Внимание", "В выбранном тесте отсутствуют результаты");
    }
//    qDebug()<<marks;
}

void Analiz::on_pushButton_clicked()
{
    AnalyzeRes *ar = new AnalyzeRes();
    ar->show();
    close();
}
