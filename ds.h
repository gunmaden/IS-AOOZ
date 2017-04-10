#ifndef DS_H
#define DS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QBarSeries>

QT_CHARTS_USE_NAMESPACE

typedef QList < QList <int> > matrix;
extern matrix trueMatrix;
extern int NS;
extern QStringList trueTaskIds, trueQuestionIds;
extern QList <int> sumsColumns, sumsRows, sumsFalseColumns, sumsFalseRows;
extern QList <QPair <QString, int> > idsMap;
extern QList <QPair <int, int> > columnsMap, rowsMap;
extern QMap <int, int> sizes;

namespace Ui {
class DS;
}

class DS : public QWidget
{
    Q_OBJECT

public:
    explicit DS(QWidget *parent = 0);
    void chartBuild(QList <double> DS);
    ~DS();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DS *ui;
};

#endif // DS_H
