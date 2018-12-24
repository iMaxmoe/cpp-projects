#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFont>
#include <QPushButton>
#include <QString>
#include <QChar>
#include <QListWidgetItem>
#include <QMessageBox>

#include "ui_ListWindow.h"
#include "masterpassword.h"
#include "AddWindow.h"
#include "RecordWindow.h"
#include "RecordManager.h"
#include "bank.h"
#include "ChangeMasterPassword.h"

namespace Ui {
class ListWindow;
}

class ListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListWindow(QWidget *parent = nullptr);
    ~ListWindow();
    AddWindow* addWindow;
    RecordWindow* recordWindow;

private:
    Ui::ListWindow *ui;
    bool hasShown[27];
    RecordManager* rm;
    MasterPassword* mp;
    Bank* myBank;
    void create_addItem(QString login);
    void refresh(); //refresh the listview UI
    ChangeMasterPassword* masterWindow;

private slots:
    void addItem_clicked(); // click the addItem button
    void setting_clicked(); // click the setting button
    void search_clicked(); // click the search button
    void back_clicked(); // click the back button
    void subWindow_closed_handler(); // reopen the listview
    void open_recordWindow(QListWidgetItem* item);
    void login_added(QString, QString, QString);
    void login_deleted(QString);
    void closeEvent(QCloseEvent* event); // when listWindow is closed
    void close_masterWindow(); // close the masterwindow
    void change_password(QString);
};

#endif // LISTWINDOW_H
