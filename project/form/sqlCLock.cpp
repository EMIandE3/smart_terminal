
#include "sqlCLock.h"
#include <QDebug>
#include <QSqlError>
#include <QFileInfoList>
#include <QDir>
#include <QCoreApplication>
#include <QProcess>

sqlCLock::sqlCLock(QWidget *parent)
    : QMainWindow(parent)
{

    QFile file(":/style/sqlCLock_style.qss");

    /* 判断文件是否存在 */
    if (file.exists() ) {
        /* 以只读的方式打开 */
        file.open(QFile::ReadOnly);
        /* 以字符串的方式保存读出的结果 */
        QString styleSheet = QLatin1String(file.readAll());
        /* 设置全局样式 */
        this->setStyleSheet(styleSheet);
        /* 关闭文件 */
        file.close();
    }

    /* 设置主窗体的显示位置与大小 */
    this->setGeometry(0, 0, 800, 480);

    /* 查看本机可用的数据库驱动 */
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers) {
        qDebug()<<driver;
    }

    /* 以QSQLITE驱动方式打开或者创建数据库 */
    sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    sqlDatabase.setDatabaseName("alarm.db");
    /* 以open的方式打开alarm.db数据库，则会创建一个alarm.db */
    if (!sqlDatabase.open())
        qDebug()<<"连接数据库错误"<<sqlDatabase.lastError()<<endl;
    else
        qDebug()<<"连接数据库成功"<<endl;

    QSqlQuery query(sqlDatabase);
    /* 使用指令式创建表 */
    query.exec("create table alarm (id int primary key, time vchar(15), flag vchar(5))");
    /* 以指令的方式插入数据 */
    //query.exec("insert into alarm values(0, '06:00', 'false')");

    model = new QSqlTableModel(this, sqlDatabase);

    /* 模型设置表的名字，需要与数据库的表的名字相同 */
    model->setTable("alarm");

    /* 如果有修改则同步修改到数据库，
     * 注意这个规则需要与tabview这样的控件才生效，
     * 因为tabview可以直接编辑表里的内容 */
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    /* 成功则返回true，查看数据库里是否有alarm这个表格 */
    model->select();

    /* 如果数据表数据为空，则添加两个闹钟 */
    if (model->rowCount() == 0) {
        /* 插入一行 */
        model->insertRow(model->rowCount());
        /* 在该行插入数据 */
        model->setData(model->index(0, 0), 1);
        model->setData(model->index(0, 1), "06:00");
        model->setData(model->index(0, 2), "false");
        /* 插入数据后记得提交 */
        model->submit();

        /* 再插入一行 */
        model->insertRow(model->rowCount());
        model->setData(model->index(1, 0), 2);
        model->setData(model->index(1, 1), "18:00");
        model->setData(model->index(1, 2), "true");
        /* 提交 */
        model->submit();
    }

    hourPicker = new NumberPicker(this);
    hourPicker->setRange(0, 24);

    minutePicker = new NumberPicker(this);
    minutePicker->setRange(0, 60);

    /* 标签，用于显示时&分 */
    QLabel *label[3];
    label[0] = new QLabel();
    label[1] = new QLabel();
    label[2] = new QLabel();

    QFont font;
    font.setBold(true);
    font.setPixelSize(10);
    QPalette pal;
    pal.setBrush(QPalette::WindowText, QColor(0, 0, 0));

    label[0]->setFont(font);
    label[1]->setFont(font);
    label[2]->setFont(font);

    label[0]->setText(" ");
    label[1]->setText("时");
    label[2]->setText("分");

    /* 主布局初始化 */
    listWidget = new QListWidget();
    mainWidget = new QWidget();
    bottomWidget = new QWidget();
    alarmDialog = new QDialog(this);
    timeWidget = new QWidget();
    btWidget = new QWidget();
    addAlarm = new QPushButton();
    yesButton = new QPushButton();
    cancelButton = new QPushButton();
    vBoxLayout[0] = new QVBoxLayout();
    vBoxLayout[1] = new QVBoxLayout();
    hBoxLayout[0] = new QHBoxLayout();
    hBoxLayout[1] = new QHBoxLayout();
    hBoxLayout[2] = new QHBoxLayout();

//    addAlarm->setIcon(QIcon(":/icons/addalarm1.png"));
    addAlarm->setMaximumSize(84, 84);
    addAlarm->setObjectName("addAlarm");
    addAlarm->setMinimumSize(84, 84);

    bottomWidget->setMinimumHeight(84);
    bottomWidget->setMaximumHeight(84);
    yesButton->setText("确认");
    cancelButton->setText("取消");
    yesButton->setMaximumSize(100, 50);
    yesButton->setMinimumSize(100, 50);
    cancelButton->setMinimumSize(100, 50);
    cancelButton->setMaximumSize(100, 50);
    btWidget->setMaximumHeight(70);
    btWidget->setMinimumHeight(70);
    alarmDialog->setMinimumSize(300, 300);
    alarmDialog->setMaximumSize(300, 300);
    alarmDialog->setModal(true);
    yesButton->setObjectName("yesButton");
    cancelButton->setObjectName("cancelButton");

    /* 主布局 */
    vBoxLayout[0]->addWidget(listWidget);
    vBoxLayout[0]->addWidget(bottomWidget);
    vBoxLayout[0]->setContentsMargins(0, 0, 0, 0);

    mainWidget->setLayout(vBoxLayout[0]);

    setCentralWidget(mainWidget);

    /* 底部按钮布局 */
    hBoxLayout[0]->addWidget(addAlarm);
    hBoxLayout[0]->setContentsMargins(0, 0, 0, 0);
    bottomWidget->setLayout(hBoxLayout[0]);

    /* 对话框布局 */
    vBoxLayout[1]->addWidget(timeWidget);
    vBoxLayout[1]->addWidget(btWidget);
    vBoxLayout[1]->setContentsMargins(0, 0, 0, 0);
    alarmDialog->setLayout(vBoxLayout[1]);

    hBoxLayout[1]->addWidget(label[0]);
    hBoxLayout[1]->addWidget(hourPicker);
    hBoxLayout[1]->addWidget(label[1]);
    hBoxLayout[1]->addWidget(minutePicker);
    hBoxLayout[1]->addWidget(label[2]);
    hBoxLayout[1]->setContentsMargins(0, 0, 0, 0);
    timeWidget->setLayout(hBoxLayout[1]);

    hBoxLayout[2]->addWidget(yesButton);
    hBoxLayout[2]->addWidget(cancelButton);

    btWidget->setLayout(hBoxLayout[2]);

    /* 打印出闹钟数据库里的信息 */
    for (int i = 0; i < model->rowCount(); i++) {
        for (int j = 0; j < 3; j++) {
            QModelIndex qindex = model->index(i, j);
            switch (j) {
            case 0:
                qDebug()<<"第"<<model->data(qindex).toInt()<<"行数据";
                break;
            case 1:
                listWidget->addItem(model->data(qindex).toString());
                listWidget->setSizeIncrement(80, 80);
                qDebug()<<"闹钟时间为："<<model->data(qindex).toString();
                break;
            case 2:
                qDebug()<<"闹钟状态为："
                       <<model->data(qindex).toString()<<endl;
                if (model->data(qindex).toString() != "true")
                    listWidget->item(i)
                            ->setTextColor(QColor(22, 22, 22, 60));
                else
                    listWidget->item(i)
                            ->setTextColor(QColor(22, 22, 22, 225));
                break;
            default:
                break;
            }
        }
    }

    /* 在列表里添加闹钟开关 */
    for (int i = 0; i < model->rowCount(); i++) {
        ItemObjectInfo info;
        info.widget = new QWidget();
        info.switchButton = new SwitchButton();
        info.hBoxLayout = new QHBoxLayout();
        info.switchButton->setMaximumSize(55, 30);
        info.switchButton->setMinimumSize(55, 30);
        info.hBoxLayout->setContentsMargins(0, 0, 0, 0);
        info.hBoxLayout->setAlignment(Qt::AlignRight);
        info.hBoxLayout->addWidget(info.switchButton);
        info.widget->setLayout(info.hBoxLayout);
        listWidget->setItemWidget(listWidget->item(i),
                                  info.widget);
        itemObjectInfo.append(info);

        /* 连接信号槽 */
        connect(info.switchButton,
                SIGNAL(toggled(bool)),
                this,
                SLOT(switchButtonClicked(bool)));

        /* 获取数据库里的闹钟开关状态 */
        QModelIndex qindex = model->index(i, 2);
        if (model->data(qindex).toBool())
            /* 设置列表里的闹钟开关按钮状态 */
            info.switchButton->setToggle(true);
    }

    /* 按钮 */
    connect(addAlarm, SIGNAL(clicked()), this,
            SLOT(addAlarmClicked()));

    connect(yesButton, SIGNAL(clicked()), this,
            SLOT(yesButtonClicked()));

    connect(cancelButton, SIGNAL(clicked()), this,
            SLOT(cancelButtonClicked()));

    /* 列表 */
    connect(listWidget,
            SIGNAL(itemClicked(QListWidgetItem*)),
            this,
            SLOT(listWidgetItemClicked(QListWidgetItem*)));
}

sqlCLock::~sqlCLock()
{
    /* 关闭数据库 */
    sqlDatabase.close();
}

void sqlCLock::addAlarmClicked()
{
    /* 选择时间对话框里显示当前系统时间 */
    hourPicker->setValue(QTime::currentTime().hour());
    minutePicker->setValue(QTime::currentTime().minute());

    /* 取消按钮显示文本为"取消" */
    cancelButton->setText("取消");

    /* 如果是点击添加闹钟的按钮，则设置闹钟列表的索引index为-1 */
    listWidget->setCurrentRow(-1);

    /* 显示对话框 */
    alarmDialog->show();
}

void sqlCLock::listWidgetItemClicked(QListWidgetItem *item)
{
    /* 从被点击项里获取闹钟数据 */
    QStringList list =
            listWidget->item(listWidget->row(item))->text().split(":");

    /* 选择时间对话框里显示被选择项的时间 */
    hourPicker->setValue(list.at(0).toInt());
    minutePicker->setValue(list.at(1).toInt());

    /* 取消按钮显示文本为"删除" */
    cancelButton->setText("删除");

    /* 显示闹钟选择对话框 */
    alarmDialog->show();

    /* 作用使其失去选择 */
    listWidget->clearSelection();
}

void sqlCLock::yesButtonClicked()
{
    /* 获取数值选择值的数据，转为字符串 */
    QString hour;
    QString minute;

    if (hourPicker->readValue() < 10)
        hour = "0" + QString::number(hourPicker->readValue()) + ":";
    else
        hour = QString::number(hourPicker->readValue()) + ":";

    if (minutePicker->readValue() < 10)
        minute = "0" + QString::number(minutePicker->readValue());
    else
        minute = QString::number(minutePicker->readValue());

    /* 如果不是选中闹钟列表的数据 */
    if (listWidget->currentRow() == -1) {
        /* 插入一行数据，闹钟时间为选择的闹钟时间 */
        int row = model->rowCount();

        /* 插入数据到数据库 */
        model->insertRow(row);
        model->setData(model->index(row, 0), row + 1);
        model->setData(model->index(row, 1), hour + minute);
        model->setData(model->index(row, 2), "true");
        model->submit();

        /* 添加闹钟到列表 */
        listWidget->addItem(hour + minute);
        listWidget->setSizeIncrement(80, 80);

        /* 添加到容器 */
        ItemObjectInfo info;
        info.widget = new QWidget();
        info.switchButton = new SwitchButton();
        info.hBoxLayout = new QHBoxLayout();
        info.switchButton->setMaximumSize(55, 30);
        info.switchButton->setMinimumSize(55, 30);
        info.hBoxLayout->setContentsMargins(0, 0, 0, 0);
        info.hBoxLayout->setAlignment(Qt::AlignRight);
        info.hBoxLayout->addWidget(info.switchButton);
        info.widget->setLayout(info.hBoxLayout);
        info.switchButton->setToggle(true);

        /* 连接信号槽 */
        connect(info.switchButton, SIGNAL(toggled(bool)), this,
                SLOT(switchButtonClicked(bool)));

        listWidget->setItemWidget(
                    listWidget->item(listWidget->count() - 1),
                    info.widget);
        itemObjectInfo.append(info);
    } else {
        /* 修改数据（更新闹钟数据） */
        int row =  listWidget->currentRow();
        model->setData(model->index(row, 0), row + 1);
        model->setData(model->index(row, 1), hour + minute);
        model->setData(model->index(row, 2), "true");
        model->submit();

        /* 设置当前项的闹钟文本 */
        listWidget->currentItem()->setText(hour + minute);
    }

    /* 再确保提交 */
    if (model->isDirty())
        model->submitAll();

    /* 关闭对话框 */
    alarmDialog->close();
}

void sqlCLock::cancelButtonClicked()
{
    if (cancelButton->text() == "删除") {
        /* 删除数据库整一行数据 */
        model->removeRow(listWidget->currentRow());
        model->submit();
        /* 执行上面语句 */
        model->select();
        itemObjectInfo.remove(listWidget->currentRow());
        listWidget->takeItem(listWidget->currentRow());
    }

    /* 再确保提交 */
    if (model->isDirty())
        model->submitAll();

    /* 关闭对话框 */
    alarmDialog->close();
}


/* 当点击闹钟开关时，将闹钟开关状态同步更新到数据库里 */
void sqlCLock::switchButtonClicked(bool checked)
{
    listWidget->clearSelection();

    SwitchButton *button = (SwitchButton *)sender();
    for (int i = 0; i < itemObjectInfo.count(); i++) {
        if (button == itemObjectInfo.at(i).switchButton) {
            if (checked) {
                model->setData(model->index(i, 2), "true");
                listWidget->item(i)
                        ->setTextColor(QColor(22, 22, 22, 225));
            } else {
                model->setData(model->index(i, 2), "false");
                listWidget->item(i)
                        ->setTextColor(QColor(22, 22, 22, 60));
            }

            model->submit();
            break;
        }
    }
}
