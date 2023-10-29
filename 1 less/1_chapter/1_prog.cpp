//#include <QApplication>
//#include <QPushButton>
#include <QtWidgets>


int main(int argc, char **argv) {
    QString str = "Butt 1";
    QApplication a(argc, argv);
    QLabel lbl(str + " lbl");
    lbl.show();
    QPushButton button(str, nullptr);
    button.resize(350, 100);
    button.show();

    return a.exec();
}
