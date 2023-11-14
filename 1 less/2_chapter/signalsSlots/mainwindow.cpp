#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QSignalMapper>

#include <QDebug>

void showParents (QObject* current, int& colSpaces)
{
    if (current == nullptr)
    {
        return;
    }
    if (current->children().size() == 0)
    {
        colSpaces = 0;
    }
    QString str;
    for (int i = 0; i < colSpaces; ++i)
    {
        str.append(" ");
    }
    qDebug() << str + current->objectName();
    showParents(current->parent(), colSpaces += 2);
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    createWidgets();
    createConnections();
    showObjectModel();
    //    int colSp = 0;
    //    showParents(this, colSp);
    //    this->dumpObjectTree();
}

MainWindow::~MainWindow() {}

void MainWindow::onBtnClicked()
{
    qDebug() << "значение в текстовом поле: " << m_displayCounter->text();
}

void MainWindow::createWidgets()
{
    m_incBtn              = new QPushButton("inc");
    m_decBtn              = new QPushButton("dec");
    m_btnValues[m_incBtn] = 0;
    m_btnValues[m_decBtn] = 1;

    m_displayCounter = new QLineEdit("0");

    QVBoxLayout* mainLayer = new QVBoxLayout(new QWidget);
    QHBoxLayout* btnsLayer = new QHBoxLayout(new QWidget);
    btnsLayer->addWidget(m_incBtn);
    btnsLayer->addWidget(m_decBtn);

    mainLayer->addWidget(btnsLayer->parentWidget());
    mainLayer->addWidget(m_displayCounter);

    setCentralWidget(mainLayer->parentWidget());
}

void MainWindow::createConnections()
{
    //    QSignalMapper* signalMapper = new QSignalMapper(this);

    //    connect(m_incBtn,
    //            &QPushButton::clicked,
    //            signalMapper,
    //            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    //    connect(m_decBtn,
    //            &QPushButton::clicked,
    //            signalMapper,
    //            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    //    signalMapper->setMapping(m_incBtn, 0);
    //    signalMapper->setMapping(m_decBtn, 1);

    //    connect(signalMapper,
    //            static_cast<void
    //            (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
    //            [=] (int value) {
    //                if (value == 0)
    //                {
    //                    int textDisplay = (m_displayCounter->text().toInt()) +
    //                    1;
    //                    m_displayCounter->setText(QString::number(textDisplay));
    //                }
    //                else if (value == 1)
    //                {
    //                    int textDisplay = (m_displayCounter->text().toInt()) -
    //                    1;
    //                    m_displayCounter->setText(QString::number(textDisplay));
    //                }
    //            });

    //    bool isOk = true;
    auto onClicked = [=] () {
        auto* sender      = qobject_cast<QPushButton*>(QObject::sender());
        int   textDisplay = 0;
        if (m_btnValues.value(sender) == 0)
        {
            textDisplay = (m_displayCounter->text().toInt()) + 1;
        }
        else if (m_btnValues.value(sender) == 1)
        {
            textDisplay = (m_displayCounter->text().toInt()) - 1;
        }
        m_displayCounter->setText(QString::number(textDisplay));
    };

    connect(m_incBtn, &QPushButton::clicked, this, onClicked);
    connect(m_decBtn, &QPushButton::clicked, this, onClicked);

    //    qDebug() << "состояние подключения" << isOk;

    connect(m_incBtn, &QPushButton::clicked, this, &MainWindow::onBtnClicked);
}

void MainWindow::showObjectModel()
{
    QObject* pobj1 = new QObject;
    pobj1->setObjectName("parent pobj1");
    QObject* pobj2 = new QObject(pobj1);
    QObject* pobj4 = new QObject(pobj2);
    QObject* pobj3 = new QObject(pobj1);
    pobj2->setObjectName("the first child of pobj1 (pobj2)");
    pobj3->setObjectName("the second child of pobj1 (pobj3)");
    pobj4->setObjectName("the first child of pobj2 (pobj4)");

    qDebug() << "objects: ";
    qDebug() << pobj1->objectName();
    qDebug() << pobj2->objectName();
    qDebug() << pobj3->objectName();
    qDebug() << pobj4->objectName();

    qDebug() << "parents: ";
    qDebug() << pobj2->parent()->objectName();
    qDebug() << pobj3->parent()->objectName();
    qDebug() << pobj4->parent()->objectName();

    qDebug() << "parents:";
    //    pobj2->setParent(new QObject);
    //    qDebug() << pobj2->parent()->objectName();
    int colSp;
    showParents(pobj4, colSp);
    //    qDebug() << "Children:";
    //    QObject::dumpObjectTree();
}
