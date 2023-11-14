#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onBtnClicked();

private:
    void extracted();
    void createWidgets();
    void createConnections();
    void showObjectModel();

private:
    QPushButton*                 m_incBtn;
    QPushButton*                 m_decBtn;
    QLineEdit*                   m_displayCounter;
    QMap<QPushButton*, uint16_t> m_btnValues;
};
#endif // MAINWINDOW_H
