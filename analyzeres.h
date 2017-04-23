#ifndef ANALYZERES_H
#define ANALYZERES_H

#include <QWidget>
typedef QList < QList <int> > matrix;
extern matrix marks;
extern QStringList taskIds;
extern QString testId;
namespace Ui {
class AnalyzeRes;
}

class AnalyzeRes : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeRes(QWidget *parent = 0);
    ~AnalyzeRes();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AnalyzeRes *ui;
};

#endif // ANALYZERES_H
