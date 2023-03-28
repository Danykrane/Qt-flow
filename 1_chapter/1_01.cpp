#include <QtWidgets>

int main(int argc, char **argv){
    QApplication app(argc, argv); // объект приложения
    char val = 'a';

    QString str = "First label" + QString(' ') + QString(val); // инициализация Qstring
    QLabel lbl(str); // передача в конструктор lbl
    lbl.show(); // запуск метода вывода на экран

    return app.exec(); // завершение программы, запуск метода exec, который возвр код вывода
}