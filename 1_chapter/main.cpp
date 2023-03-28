#include <QtWidgets>
#include "headers/signalS3.h"

int main (int argc, char** argv)
{
  QApplication app(argc, argv);

    QLabel      lbl("0");
    QPushButton cmd("ADD");
    Counter     counter;

    lbl.show();
    cmd.show();
    cmd.resize(350, 100);
    lbl.resize(100, 100);

    QObject::connect(&cmd, SIGNAL(clicked()),
                     &counter, SLOT(slotInc())
    );

    QObject::connect(&counter, SIGNAL(counterChanged(int)),
                     &lbl, SLOT(setNum(int))
    );

    QObject::connect(&counter, SIGNAL(goodbye()),
                     &app, SLOT(quit())
    );

    return app.exec();
}