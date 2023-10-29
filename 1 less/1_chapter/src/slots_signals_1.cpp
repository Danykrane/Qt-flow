//
// Created by Артём Гудзенко on 28.03.2023.
//

#include "../headers/slots_signals_1.h"

test::test() {}

void test::work() {
    QString str = "Butt 1";
    QLabel lbl(str + " lbl");
    lbl.show();
    QPushButton button(str, nullptr);
    button.resize(350, 100);
    button.show();
}