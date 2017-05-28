#include "analyzeres.h"
#include "ui_analyzeres.h"
#include <QMessageBox>
#include <QtMath>
#include <QSqlQuery>
#include <QDebug>
#include "analiz.h"
#include "ds.h"
#include "vairiety.h"
//#include "operations.cpp"

typedef QList < QList <int> > matrix;

matrix trueMatrix;
QStringList trueTaskIds, trueQuestionIds;
QList <int> sumsColumns, sumsRows;
QList <QPair <QString, int> > idsMap;
QList <QPair <int, int> > columnsMap, rowsMap;
QMap <int, int> sizes;
int NS;

int count(QList<int> intList)
{
    int sum=0;
    foreach (int item, intList) {
        item>=40?sum++:false;
    }
    return sum;
}

matrix prepareMatrix(matrix m, int row, int col){
    for (int r=0;r<row;r++){
        QList <int> listRow;
        for (int c=0;c<col;c++)
        {
            listRow.append(-100);
        }
        m.append(listRow);
    }
    return m;
}

int neededSize(QMap<int,int> map)
{
    int max_val= map.values().at(0);
    int min_val=map.values().at(0);
    int sum_val=0;
    foreach (int value, map.values())
    {
        value>max_val?max_val=value:false;
        value<min_val?min_val=value:false;
        sum_val+=value;
    }
    if (double(min_val)/double(max_val)<0.85){
        return map.key(max_val);
    }
    else {
        return map.key(min_val);
    }
}

double findSum(QList<double> doubleList){
    double result=0;
    foreach (double val, doubleList) {
        result+=val;
    }
    return result;
}

int findSum(QList<int> intList){
    int result=0;
    foreach (int val, intList) {
        result+=val;
    }
    return result;
}

double avgFromIntList (QList <int> intList, int cond=1) {
    double result=0.0;
    int counter=0;
    foreach (int val, intList) {
        if (val>=cond) {
            counter++;
            result+=val;
        }
    }
    result=result/counter;
    return result;
}


double findSigma (QList<int> intList, double avgVal){
    QList <double> l;
    foreach (double val, intList) {
        l.append(pow(val-avgVal,2.0));
    }
    return sqrt(1.0/double(intList.count())*findSum(l));
}

QList <double> firstPart(QList <double> doubleList, double avgVal, double sigma){
    QList <double> result;
    foreach (double val, doubleList) {
        result.append((val-avgVal)/sigma);
    }
    return result;
}

QList <double> secondPart(QList <int> intList, int count)
{
    QList <double> result;
    foreach (double val, intList) {
        result.append(sqrt(val/(count-val)));
    }
    return result;
}

QList <double> differentiateProbability(QList<double> first, QList<double> second){
    QList <double> result;
    for (int i=0;i<first.count();i++){
        result.append(first.at(i)*second.at(i));
    }
    return result;
}

double standartDeviation(QList <int> data, double avg){
    double sum = 0;
    int count = data.count();
    foreach (int item, data) {
        sum+=pow(item-avg,2);
    }
    return sqrt(double(sum/(count-1)));
}

QList <int> multiplyArrays(QList <int> array1, QList <int> array2){
    QList <int> res;
    for(int i=0;i<array1.count();i++)
    {
        res<<array1.at(i)*array2.at(i);
    }
    return res;
}

QList <double> multiplyArrays(QList <double> array1, QList <double> array2){
    QList <double> res;
    for(int i=0;i<array1.count();i++)
    {
        res<<array1.at(i)*array2.at(i);
    }
    return res;
}

void out(auto L){
    qDebug()<<"===================================";
    foreach (auto i, L) {
        qDebug()<<"///  "<<i;
    }
    qDebug()<<"===================================";
}

QList <double> diffWAvg(QList <int> intList, double avg)
{
    QList <double> res;
    foreach (int it, intList) {
        res<<it-avg;
    }
    return res;
}

double findValidity(QList <int> taskMark100, QList <int> sessionMark){

    double avgTaskMark = avgFromIntList(taskMark100, -1);
    double avgSessionRes = avgFromIntList(sessionMark, -1);
    double devSessionRes = standartDeviation(sessionMark,avgSessionRes);
    double devTaskMark = standartDeviation(taskMark100,avgTaskMark); // отклонения
    return findSum(
                multiplyArrays(
                    diffWAvg(taskMark100,avgTaskMark),diffWAvg(sessionMark,avgSessionRes)
                    )
                )/(taskMark100.count()*sqrt(pow(devTaskMark,2)*pow(devSessionRes,2)))
            ;
}

double findReliability(int questionsCount, QList <int> trueCount)
{
    double avgTrueCount = avgFromIntList(trueCount);
    double devTrueCount = standartDeviation(trueCount, avgTrueCount);
    QList <double> P,Q;
    foreach (int val, trueCount) {
        double pj = val/questionsCount;
        P.append(pj);
        Q.append(1-pj);
    }
    QList <double> mult = multiplyArrays(P,Q);
    double sum = findSum(mult);
    return (questionsCount-sum)/((questionsCount-1)*devTrueCount);
}

AnalyzeRes::AnalyzeRes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeRes)
{
    sizes.clear();
    foreach (QList <int> row, marks) {
        if (!sizes.contains(row.size()))
        {
            sizes[row.size()]=1;
        }
        else {
            sizes[row.size()]++;
        }
    }
    NS = neededSize(sizes);

    for (int i=0;i<marks.size();i++)
    {
        QList <int> row = marks.at(i);
        if (row.size()>NS){
            while (row.size()>NS){
                row.removeLast();
            }
        }
        else {
            while (row.size()<NS){
                row.append(0);
            }
        }
        marks.replace(i,row);
    }

    sumsColumns.clear();
    sumsRows.clear();
    QList<int> indexR, indexC;
    for (int column=0 ; column<NS ; column++){
        int sum=0;
        for (int row=0 ; row < taskIds.size() ; row++ )
        {
            marks.at(row).at(column)>=40?sum++:false;
        }
        sumsColumns.append(sum);
        if (sum==0||sum==taskIds.count())
            indexC<<column;
    }

    for(int i=0;i<marks.count();i++)
    {
        QList <int> l = marks.at(i);
        sumsRows.append(count(l));
        if (count(l)==0||count(l)==NS)
            indexR<<i;
    }

    QStringList deletedTasks, deletedQuestions;

    foreach (int ind, indexR) {
        deletedTasks<<QString("%1").arg(taskIds.at(ind));
    }
    foreach (int ind, indexC) {
        deletedQuestions<<QString("%1").arg(ind+1);
    }

    int counter=0;
    foreach (int ind, indexR) {
        marks.removeAt(ind-counter);
        sumsRows.removeAt(ind-counter);
        taskIds.removeAt(ind-counter);
        counter++;
    }

    counter=0;
    foreach (int ind, indexC) {
        for (int i=0;i<marks.count();i++)
        {
            QList <int> junk=marks.at(i);
            junk.removeAt(ind-counter);
            marks.replace(i,junk);
        }
        sumsColumns.removeAt(ind-counter);
        counter++;
    }
    NS -= indexC.count();

    columnsMap.clear();
    rowsMap.clear();
    for (int i=0; i < sumsColumns.size(); i++)
    {
        columnsMap.append(qMakePair(sumsColumns.at(i),i));
    }
    idsMap.clear();
    for (int i=0; i < sumsRows.size(); i++)
    {
        rowsMap.append(qMakePair(sumsRows.at(i),i));
        idsMap.append(qMakePair(taskIds.at(i),i));
    }

    std::sort(columnsMap.begin(),columnsMap.end());
    std::reverse(columnsMap.begin(),columnsMap.end());
    std::sort(rowsMap.begin(),rowsMap.end());
    std::reverse(rowsMap.begin(),rowsMap.end());

    trueMatrix.clear();
    trueMatrix = prepareMatrix(trueMatrix, rowsMap.count(), columnsMap.count());
    trueTaskIds.clear();
    trueQuestionIds.clear();
    for (int row=0;row<marks.size();row++)
    {
        trueMatrix.replace(row,marks.at(rowsMap.at(row).second));
        trueTaskIds.append(idsMap.at(rowsMap.at(row).second).first);
    }

    for (int row=0;row<marks.size();row++)
    {
        QList <int> junk = trueMatrix.at(row);
        for (int column=0; column<NS; column++)
        {
            junk.replace(column,trueMatrix.at(row).at(columnsMap.at(column).second));
        }
        trueMatrix.replace(row,junk);
    }

    sumsColumns.clear();
    sumsRows.clear();

    for (int row=0;row<trueMatrix.count();row++)
    {
        sumsRows<<count(trueMatrix.at(row));
    }

    for (int col=0;col<NS; col++){
        QList <int> l;
        foreach (QList <int> list, trueMatrix) {
            l<<list.at(col);
        }
        sumsColumns<<count(l);
    }

    // ------------------------------- Deleted questions numbering

    for (int i=0;i<columnsMap.count();i++){
        trueQuestionIds.append(QString("%1 (%2)").arg(i+1).arg(columnsMap.at(i).second+1));
    }


    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ //
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/favicon.ico"));
    this->setWindowTitle("Результаты анализа теста");
    ui->tableWidget->setRowCount(trueMatrix.count());
    ui->tableWidget->setColumnCount(NS);
    ui->tableWidget->setVerticalHeaderLabels(trueTaskIds);
    ui->tableWidget->setHorizontalHeaderLabels(trueQuestionIds);

    for( int row=0; row<trueMatrix.count();row++)
    {
        for (int col=0;col<NS;col++)
        {
            QTableWidgetItem *it = new QTableWidgetItem();
            it->setText(QString("%1").arg(trueMatrix.at(row).at(col)));
            if (trueMatrix.at(row).at(col) <40)
                it->setBackgroundColor(Qt::gray);
            else it->setBackground(Qt::green);

            ui->tableWidget->setItem(row,col, it);
        }
    }


    QSqlQuery q(QString (" SELECT DISTINCT \"table\".\"taskID\", cast(avg(\"t\".\"taskMark100\") as INTEGER ) as \"taskMark100\", \"sr\".\"Mark\" "
                         " FROM (SELECT * FROM \"TaskContent\" ORDER BY \"taskID\", \"taskContentNum\" ) as \"table\" "
                         " JOIN \"Task\" as \"t\" on \"table\".\"taskID\" = \"t\".\"taskID\" "
                         " JOIN \"SessionRes\" as \"sr\" on \"sr\".\"StudId\" = \"t\".\"studID\" "
                         " WHERE \"table\".\"taskID\" in (SELECT \"taskID\" FROM \"Task\" where \"testID\"=%1) "
                         " GROUP BY \"table\".\"taskID\", \"sr\".\"Mark\" "
                         " ORDER BY \"table\".\"taskID\" ").arg(testId));
    QList <int> taskMark100, sessionMark;
    if (q.size()==0)
        ui->labelValidity->setText("Невозможно определить валидность теста, т.к. отсутствуют результаты прохождения сессии");
    else {
        while (q.next()) {
            taskMark100<<q.value(1).toInt();
            sessionMark<<q.value(2).toInt();
        }
        double validity=findValidity(taskMark100,sessionMark);
        qDebug()<<validity;
        if (validity<0.11)
            ui->labelValidity->setText(QString("Значение коэффициента: %1 . Этот тест не следует использовать").arg(validity));
        if (validity>=0.11 && validity<=0.2)
            ui->labelValidity->setText(QString("Значение коэффициента: %1 . Этот тест можно использовать в зависимости от обстоятельств").arg(validity));
        if (validity>=0.21 && validity<=0.35)
            ui->labelValidity->setText(QString("Значение коэффициента: %1 . Этот тест можно использовать").arg(validity));
        if (validity>0.35)
            ui->labelValidity->setText(QString("Значение коэффициента: %1 . Этот тест с очень хорошей валидностью").arg(validity));
    }
    double reliability = findReliability(NS,sumsRows);
    qDebug()<<reliability;
    if (reliability>=0.8)
        ui->label_2->setText(QString("Надежность теста составляет: %1 , что говорит о высокой надежности теста").arg(reliability));
    if (reliability<0.8 && reliability>=0.7)
        ui->label_2->setText(QString("Надежность теста составляет: %1 , что говорит о хоршей надежности теста").arg(reliability));
    if (reliability<0.7)
        ui->label_2->setText(QString("Надежность теста составляет: %1 , данный тест не рекомендуется использовать").arg(reliability));

    if (!deletedQuestions.empty()||!deletedTasks.empty())
        QMessageBox::information(this, "Внимание", QString("Из расчета убраны вопросы: %1 \n Из расчета убраны результаты теста: %2")
                                 .arg(deletedQuestions.join(", ")).arg(deletedTasks.join(", ")));
}

AnalyzeRes::~AnalyzeRes()
{
    delete ui;
}

void AnalyzeRes::on_pushButton_clicked()
{
    vairiety *va = new vairiety();
    va->show();
    close();
}

void AnalyzeRes::on_pushButton_3_clicked()
{
    Analiz *a = new Analiz();
    a->show();
    close();
}

void AnalyzeRes::on_pushButton_2_clicked()
{
    DS * ds = new DS();
    ds->show();
    close();
}
