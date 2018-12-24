#ifndef RECORDWINDOW_H
#define RECORDWINDOW_H

#include <QMainWindow>
#include "ui_RecordWindow.h"

namespace Ui {
class RecordWindow;
}

class RecordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecordWindow(QWidget *parent = nullptr);
    ~RecordWindow();
    void change_login_name_label(QString);
    void change_account_label(QString);
    void change_password_label(QString);

private:
    Ui::RecordWindow *ui;
    void closeEvent(QCloseEvent *event);

public slots:
    void backButton_clicked();
    void deleteButton_clicked();
    void editButton_clicked();

signals:
    void RecordClosed();
    void back();
    void deleted(QString);
};

#endif // RECORDWINDOW_H
