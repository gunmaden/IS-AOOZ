#ifndef VAIRIETY_H
#define VAIRIETY_H
#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>

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
class vairiety;
}

class vairiety : public QWidget
{
    Q_OBJECT

public:
    explicit vairiety(QWidget *parent = 0);
    void chartBuild(QList<double> variety, QList<double> posPrec);
    ~vairiety();

private slots:
    void on_pushButton_clicked();

private:
    Ui::vairiety *ui;
};

#endif // VAIRIETY_H
