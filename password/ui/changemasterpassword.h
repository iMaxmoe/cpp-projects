#ifndef CHANGEMASTERPASSWORD_H
#define CHANGEMASTERPASSWORD_H
#include <QMainWindow>
#include "ui_MasterWindow.h"

namespace Ui {
class ChangeMasterPassword;
}

class ChangeMasterPassword: public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeMasterPassword(QWidget *parent = nullptr);
    ~ChangeMasterPassword();

private:
    Ui::MasterWindow *ui;
    void closeEvent(QCloseEvent *event);
    bool checked;
    bool reinChecked;

public slots:
    void confirm_clicked();
    void revealInput();
    void revealReinput();

signals:
    void confirmed(QString);
    void masterClosed();
};

#endif // CHANGEMASTERPASSWORD_H
