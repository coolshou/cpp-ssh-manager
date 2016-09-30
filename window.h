#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <config.h>
#include <QListWidgetItem>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

public slots:
        void onListViewItemSelected(QListWidgetItem *item);
        void onBtnSettingsClicked(bool clicked);
        void onBtnReloadClicked(bool clicked);
private:
    void setupUi(Config *config);
    Config *loadConfig();
    QString getSettingsJsonString(QString filename);
    void showErrorAlert(QString message);
    void updateConnectionList(Config *config);
    void reloadConfig();

    Config *config;
    QListWidget *listView;
    void updateConnections();
};

#endif // WINDOW_H
