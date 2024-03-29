# Qt 5.10

### Модули Qt
Qt сожержит в себе 14 основных библиотек (модулей).

**Основные модули:**
```cpp
- QtCore (базовый компонент, состоит из классов, не отвечающих за графиеское отображение);
- QtGui (Модуль базовых классов для программирования
графического интерфейса);
- QtWidgets (Модуль, дополняющий QtGui «строительным
материалом» для графического интерфейса
в виде виджетов на C++);
- QtQuick (Модуль, содержащий описательный фреймворк
для быстрого создания графического интерфей-
са);
- QtQML (Модуль, содержащий движок для языка QML
и JavaScript);
- QtNetwork (Модуль для программирования сети);
- QtSql (Модуль для программирования баз данных);
- QtSvg (Модуль для работы с SVG (Scalable Vector
Graphics), масштабируемая векторная графика);
- QtXml (Модуль поддержки XML, классы, относящиеся
к SAX и DOM);
- QtXmlPatterns (Модуль поддержки XPath, XQuery, XSLT
и XmlShemaValidator);
- QtMultimedia (Модуль мультимедиа. Собрание классов
для работы со звуком, видео, камерой и радио);
- QtMultimediaWidgets (Модуль с виджетами для модуля QtMultimedia);
- QtPrintSupport (модуль для работы с принтером);
- QtTest ().
```

**Доп модули:**
```cpp
- QtWebEngineCore (Позволяет очень просто интегрировать
в приложение возможости веб);
- QtWebEngineWidgets (Предоставляет готовые к интеграции в приложение элементы в виде виджетов с возможностью также расширять элементы веб своими собственными виджетами);
- Qt 3D (Qt3DAnimation, Qt3DCore, Qt3DExtras, Qt3DInput, Qt3DLogic, Qt3DRender и Qt3DScene2D);
- QtBluetooth (Содержит классы для использования
беспроводной технологии Bluetooth);
- QtLocation (Предоставляет классы геолокации для опре-
деления текущего местоположения);
- QtSensors (Обеспечивает доступ к сенсорам мобильных
устройств — таким, как, например, сенсор ори-
ентации и акселерометр);
- QtCharts (диаграммы);
- QtDataVisualization (диаграммы в 3d);
- QtVirtualKeyboard (Собственная реализация виртуальной клавиа-
туры для целого ряда языков);
- QtRemoteObjects (Поддержка межпроцессного взаимодействия
(IPC). В простой форме обеспечивает обмен
информацией между приложениями, находя-
щимися как на одном, так и на удаленных
компьютерах);
```

### Объектная модель `Qt`

**Иерархия классов QT**


Класс `QObject` содержит поддержку:

- сигналов и слотов (signal/slot);
- таймера;
- механизма объединения объектов в иерархии (предки отвечают за удаление своих потомков);
- событий и механизма их фильтрации;
- организации объектных иерархий;
- метаобъектной информации (`QMetaObject` имя класса, список наследников, указатель на родительский класс);
- привидения типов (`qobject_cast<T>()`);
- свойств (макрос `Q_PROPERTY`).


При множественном наследовании наследуем в первую очередь от `QObject` - **базового класса**.

```cpp
class MyClass: public QObject, public Another{
// ...
};
```

Разработка интерфейса в C++ не было первоначальной задачей, однако `Х Win-dow System` попробовал это реализовать за счет `callback` функций.

**Минусы такого подхода**: нет проверки на типы возвращаемых значений тк используем указатель на ф-ии типа `void`

**Макрос** `Q_OBJECT` (Meta Object Compiler) следует сразу нс след линии за именем класса

```cpp
class className{
	Q_OBJECT // ";" не ставится
};
```

Данный макрос используется в классах QT для **связывания сигналов и
слотов**. Если в классе не используется сигнала — слотовая система то
данный параметр можно не использовать.

**Цель** данного макроса указать компилятору метаобъектов
который создает moc файлы что в данном классе присутвуют сигналы/слоты и они
должны быть связанны с другими сигналами/слотами через метод **connect**. Если указать данный макрос где не используется сигнально-слотовая система то данный макрос будет игнорирован.

**MOC** - кодогенератор, который парсит заголовочные файлы и генерирует дополнительный C++ файл, который компилируется с остальной частью программы.

**Отправить** сигнал отреагировать слотом.

**Сигналы и слоты** могут объединять объекты даже в **разных потоках**.

```cpp
    bool isOk = false;
    auto close = [=]() -> bool{
        d->connectionStatus = false;
        return d->disconnectDevice();
    };

    QMetaObject::invokeMethod(
        QAbstractEventDispatcher::instance(d->m_thread.get()),
        close, Qt::BlockingQueuedConnection, &isOk);
```

>При уничтожении объекта происходит автоматическое разъединение всех сигнально-слотовых связей

### Сигналы

Пример сигнала: звонок будильника, жест регулироващика, костер индейцев.

**Сигнал Qt:** методы для пересылки сообщений. Причина появления: изменение состояния управляющего объекта (движение ползунка).

**Сигналы** - прототипы методов. (void) За их реализацию отвечает MOC. (макрос Q_OBJECT)

Для сигналов нужно прописать ключевое слово **signals**, чтобы программа поняла, где находится область слотов

```cpp
class MySign: public QObject{
    Q_OBJECT
public:
    MySign();
signals: //область сигналов
    void sendString(const QString&); // сигнал с параметром
    void doIt();
};
```
Сигнал **doIt()** не имеет реализации, реализацию обеспечивает `MOC`:
```cpp
void MySignal::doIt()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
```
Пример .moc файла проекта EthernetToCan

```cpp
// SIGNAL 0
void TcpClient::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TcpClient::disconnectedFromServer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TcpClient::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
```


Сигналы можно соединить:
- со слотами;
- с другими сигналами.



Пример:
```cpp
#include <QPushButton>
#include <QDebug>

class Sample: public QObject{
    Q_OBJECT
    public:
    Sample(QObject *parent): QObject(parent){
        m_resetBtn = new QPushButton("reset");
        createConnections();
    }

    void createConnections(){
        // сигнал к слоту
        connect(m_resetBtn, &QPushButton::clicked, this, &Sample::onResetBtnClicked);

        // сигнал к сигналу firstSignal
        connect(this, &Sample::firstSignal, this, &Sample::secondSignal);

        connect(this, $Sample::secondSignal, [=](){
            qDebug()<<"emit of first Signal";
        });

    }

    public slots:
    
    void onResetBtnClicked(){
        qDebug() << "sender addr: "<< &(static_cast<QPushButton*>(sender()));
        // вызов firstSignal
        emit firstSignal();
    }

    void onFirstSihnalEmited(){
    }
    void onSecondSignalEmited();

    signals:
    void firstSignal();
    void secondSignal();

    private:
    QPushButton *m_resetBtn;
};
```

**Вызов сигнала:** `emit nameOfSign()`

## Слоты

**Слоты:** методы, которые присоединяются к сигналам. Различие между методами: прием сигналов.

Чтобы слот мог соединяться **только с сигналами сторонних объектов**, но не **вызываться как обычный метод со стороны**, этот слот необходимо объявить как **protected или private**. **Во всех других** случаях объявляйте их как **public**.

В объявлениях перед каждой группой слотов должно стоят соответственно: private slots:, protected slots: или pubic slots: **Слоты** могут быть и **виртуальными**. (в 10 раз дольше, поэтому не желательно)

**Особенности слотов:**

- нельзя параметры по умолчанию `public slots: void SlotMeth(int n = 8)`
- не должны быть static
- соединение с `virtual slots` в 10 раз медленней.

```cpp
sender()->objectName(); //узнать от какого объекта вызван слот
```

```cpp
class MySign: public QObject{
    Q_OBJECT
public:
    MySign();

public slots: //публичные слоты
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
```

## Соединение объектов

Объекты соединяются при помощи `QObject::connnect()`. <br>
Синтаксис соединения: 
```cpp
QObject::connect(const QObject* sender,
                const QMetaMethod& signal, 
                const QObject* receiver, 
                const QMetaMethod& slot,
                Qt::ConnectionType type = Qt::AutoConnection)
```
**Преимущество:** все ошибки соединения сигналов со слотами выявляются на этапе `компиляции` программы, а не при ее *исполнении*.
```
sender - указатель на объект, отправляющий сигнала;
signaL - указатель на метод сигнала;
receiver - указатель на объект, принимающий сигнал;
slot - указатель на метод, принимающий сигнал (слот);
type - тип соединения (режим обраюотки).
```

Разновидность Qt::Connection:
- `Qt::DirectConnection` — сигнал обрабатывается сразу вызовом соответствующего метода слота;
- `Qt::QueuedConnection` — сигнал преобразуется в событие ставится
в общую очередь для обработки;
- `Qt::AutoConnection` — это автоматический режим (по умолчанию), который действует следующим образом: 
> Если отсылающий сигнал объект находится в одном потоке с принимающим
его объектом, то устанавливается режим Qt::DirectConnection, в противном случае — режим Qt::QueuedConnection. 
-  `Qt::BlockingQueuedConnection` - тоже, что и `Qt::QueuedConnection` только с блокированием пока слот не будет выполнен. С дополнительным параметром, булевой переменной.

### QSignalMapper 

Класс `QSignalMapper` в Qt служит для связывания одного или нескольких сигналов с одним слотом. Он позволяет передать дополнительную информацию в слот, используя метод setMapping();

Пример:

```cpp
#include <QSignalMapper>
```


```cpp
QSignalMapper* signalMapper = new QSignalMapper(this);
```

```cpp
QPushButton* m_incBtn = new QPushButton("inc");
QPushButton* m_decBtn = new QPushButton("dec");
```


```cpp
 connect(m_incBtn,
            &QPushButton::clicked,
            signalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(m_decBtn,
            &QPushButton::clicked,
            signalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));


signalMapper->setMapping(m_incBtn, 0);
signalMapper->setMapping(m_decBtn, 1);
```


```cpp
    connect(signalMapper,
            static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
            [=] (int value) {
                if (value == 0)
                {
                    int textDisplay = (m_displayCounter->text().toInt()) + 1;
                    m_displayCounter->setText(QString::number(textDisplay));
                }
                else if (value == 1)
                {
                    int textDisplay = (m_displayCounter->text().toInt()) - 1;
                    m_displayCounter->setText(QString::number(textDisplay));
                }
            });
```

Однако с приходом `лямбда выражений` в C++ можно проще (достаточно передать указатели по значению в список захвата):

```cpp
QPushButton* m_incBtn = new QPushButton("inc");
QPushButton* m_decBtn = new QPushButton("dec");
QMap<QPushButton*, uint16_t> m_btnValues;

m_btnValues[m_incBtn] = 0;
m_btnValues[m_decBtn] = 1;

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
```

## Объектная иерархия

`Объектная иерархия` (от `QObject`) нужна для того, чтобы не беспокоиться об удалении объектов Qt.

Получение информации от объектов:
- `parent()` - `QObject*` предок (**верхний уровень** вернет **0**);
- `children()` -  `QList<QObject*>` список указателей жочерних классов.

Метод `dumpObjectTree()` - выводит список дочерних (объектов потомков в виде дерева).

Пример:
```cpp
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
```
```cpp
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

    pobj2->setParent(new QObject);
    qDebug() << pobj2->parent()->objectName();
```

## Метаобъектная инфомация

Каждый объект, созданный от класса QObject или от унаследованного от него класса, располагает структурой данных, называемой метаобъектной информацией (`QMetaObject`).