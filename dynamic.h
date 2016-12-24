#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <QLineSeries>
#include <QWidget>

QT_CHARTS_USE_NAMESPACE

extern QString FIO;
namespace Ui {
class dynamic;
}

class dynamic : public QWidget
{
    Q_OBJECT

public:
    explicit dynamic(QWidget *parent = 0);
    ~dynamic();

    void prepareChart(QList<QLineSeries *> seriesList);
protected:
    void limitCheckBoxes();
private slots:
    void on_pushButton_clicked();

    void chartBuildByGroups();
    void chartBuildByDisciples();
private:
    Ui::dynamic *ui;
    void setLayouts();
};

#endif // DYNAMIC_H
