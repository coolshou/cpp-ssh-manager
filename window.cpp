#include "window.h"

#include <QVBoxLayout>
#include <QListView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDir>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>
#include <config.h>
#include <QJsonArray>
#include <connectionlistmodel.h>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QListWidget>
#include <QProcess>

/**
 * @brief Window::Window
 */
Window::Window()
{
    config = loadConfig();
    setupUi(config);
    updateConnections();
}


void Window::onListViewItemSelected(QListWidgetItem *item)
{
    Connection con = qvariant_cast<Connection>(item->data(Qt::UserRole));
    QProcess *process = new QProcess(this);
    QString cmd =
            QString(config->command.ssh->join(" "))
            + " "
            + con.host
            + " -p "
            + QString::number(con.port)
            + " "
            + QString(con.args.join(" "))
    ;

    process->start(cmd);

}

void Window::onBtnSettingsClicked(bool clicked)
{
    QString filename = "/.sshManager.config.json";
    QDir *dir = new QDir();
    QString filepath = dir->homePath() + filename;

    QProcess *process = new QProcess(this);
    QString cmd = QString(config->command.edit->join(" ")) + " " + filepath;

    process->start(cmd);
}

void Window::onBtnReloadClicked(bool clicked)
{
    config = loadConfig();
    updateConnections();
}

/**
 * @brief Window::setupUi
 */
void Window::setupUi(Config *config)
{
    this->setGeometry(config->window.x, config->window.y, config->window.width, config->window.height);
    this->setMinimumSize(config->window.width, config->window.height);
    this->setMaximumSize(config->window.width, config->window.height);

    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);

    listView = new QListWidget();
    layout->addWidget(listView);

    QPushButton *btnSettings = new QPushButton();
    btnSettings->setText("Settings");

    QPushButton *btnReload = new QPushButton();
    btnReload->setText("Reload");

    QHBoxLayout *buttonWrapper = new QHBoxLayout();
    buttonWrapper->addWidget(btnSettings);
    buttonWrapper->addWidget(btnReload);

    layout->addLayout(buttonWrapper);

    setWindowIcon(QIcon("icon.png"));

    connect(listView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListViewItemSelected(QListWidgetItem*)));
    connect(btnSettings, SIGNAL(clicked(bool)), this, SLOT(onBtnSettingsClicked(bool)));
    connect(btnReload, SIGNAL(clicked(bool)), this, SLOT(onBtnReloadClicked(bool)));
}

/**
 * @brief Window::loadConfig
 */
Config *Window::loadConfig()
{
    QString filename = "/.sshManager.config.json";
    QDir *dir = new QDir();
    QString filepath = dir->homePath() + filename;

    QString jsonString = getSettingsJsonString(filepath);

    QJsonDocument itemDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject itemObject = itemDoc.object();

    QString required[3] = {"command", "window","connections"};

    for (QString item : required) {
        if (!itemObject.contains(item)) {
            this->showErrorAlert("Invalid config! No section [" + item + "]");
        }
    }

    Config *config = new Config();

    config->window.x = itemObject["window"].toObject().take("x").toInt();
    config->window.y = itemObject["window"].toObject().take("y").toInt();
    config->window.width = itemObject["window"].toObject().take("width").toInt();
    config->window.height = itemObject["window"].toObject().take("height").toInt();

    config->command.edit = config->getListFromJsonArray(itemObject["command"].toObject().take("edit").toArray());
    config->command.ssh = config->getListFromJsonArray(itemObject["command"].toObject().take("ssh").toArray());

    for (QVariant item : itemObject["connections"].toArray().toVariantList()){
        Connection *connection = new Connection();

        QMap<QString, QVariant> map = item.toMap();
        connection->host = map.value("host").toString();
        connection->label = map.value("label").toString();
        if (map.contains("port")){
            connection->port = map.value("port").toInt();
        }
        if (map.contains("args")) {
            for (QVariant arg : map.value("args").toList()) {
                connection->args.append(arg.toString());
            }
        }

        config->connections.append(*connection);
    }

    return config;
}

/**
 * @brief Window::getSettingsJsonString
 * @param filename
 * @return
 */
QString Window::getSettingsJsonString(QString filename)
{
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    return val;
}

void Window::showErrorAlert(QString message)
{
    QMessageBox alert;
    alert.setText(message);
    alert.critical(this, "Error", message);
    exit(1);
}

void Window::updateConnections()
{
    listView->clear();

    for (Connection con : config->connections) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant variant = QVariant::fromValue(con);
        item->setData(Qt::UserRole, variant);
        item->setText(con.label);

        listView->addItem(item);
    }
}
