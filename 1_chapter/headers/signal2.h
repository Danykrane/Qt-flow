//
// Created by Артём Гудзенко on 28.03.2023.
//

#pragma once

#include <QObject>
#include <QDebug>

class MySign: public QObject{
    Q_OBJECT
public:
    MySign();
public slots:
    void slot() {
        qDebug() << "I am slot";
        qDebug() << sender()->objectName(); //узнать от какого объекта вызван слот
    }

    void sendSign(){
        emit sendString("Info"); //вызов сигнала
    }

signals:
    void sendString(const QString&); // сигнал с параметром
    void doIt();
};


