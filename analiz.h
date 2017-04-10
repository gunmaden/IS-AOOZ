#ifndef ANALIZ_H
#define ANALIZ_H

#include <QWidget>
extern QString FIO,IDD;

namespace Ui {
class Analiz;
}

class Analiz : public QWidget
{
    Q_OBJECT

public:
    explicit Analiz(QWidget *parent = 0);
    ~Analiz();

private slots:
    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::Analiz *ui;
};

#endif // ANALIZ_H
