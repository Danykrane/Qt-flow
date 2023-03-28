//
// Created by Артём Гудзенко on 28.03.2023.
//

#include "../headers/signalS3.h"


Counter::Counter() : QObject(), m_nValue(0)
{
}

void Counter::slotInc()
{
    emit counterChanged(++m_nValue);

    if (m_nValue == 10) {
        emit goodbye();
    }
}