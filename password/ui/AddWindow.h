#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QMainWindow>
#include "ui_addwindow.h"
#include "bank.h"

namespace Ui {
class AddWindow;
}

class AddWindow : public QMainWindow
{
    Q_OBJECT

public:
    AddWindow(QWidget *parent = nullptr, Bank* bank =  nullptr);
    ~AddWindow();

private:
    Ui::AddWindow *ui;
    Bank* myBank;
    void closeEvent(QCloseEvent *event);
    bool checked;
    bool reinChecked;

signals:
    void closed();
    void saved(QString, QString, QString); // clicked save, destruct it and return to listWindow
    void test(QString); // check whether there already exists an account

public slots:
    void added(); // fininshing add, click create
    void revealInput();
    void revealReinput();
};

#endif // ADDWINDOW_H
