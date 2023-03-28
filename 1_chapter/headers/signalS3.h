//
// Created by Артём Гудзенко on 28.03.2023.
//

#pragma once

#include <QObject>
#include <QSignalMapper>

class Counter : public QObject {
Q_OBJECT
private:
    int m_nValue;

public:
    Counter();
    virtual ~Counter() {};

public slots:
    void slotInc();

signals:
    void goodbye       (   );
    void counterChanged(int);
};

