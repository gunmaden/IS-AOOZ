#ifndef ANALYZERES_H
#define ANALYZERES_H

#include <QWidget>

namespace Ui {
class AnalyzeRes;
}

class AnalyzeRes : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeRes(QWidget *parent = 0);
    ~AnalyzeRes();

private:
    Ui::AnalyzeRes *ui;
};

#endif // ANALYZERES_H
