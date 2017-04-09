#ifndef ANALIZ_H
#define ANALIZ_H

#include <QWidget>

namespace Ui {
class Analiz;
}

class Analiz : public QWidget
{
    Q_OBJECT

public:
    explicit Analiz(QWidget *parent = 0);
    ~Analiz();

private:
    Ui::Analiz *ui;
};

#endif // ANALIZ_H
