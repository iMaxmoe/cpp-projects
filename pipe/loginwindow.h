#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class GameInstance;
class RecordManager;

using std::string;

namespace Ui
{
    class LoginWindow;
}

class LoginWindow : public QMainWindow // Under namespace ui
{
    Q_OBJECT

 public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

 private:
    Ui::LoginWindow *ui;
    GameInstance *game;
    RecordManager *rm;
    int current_level;
    bool started;
    void start_game();
    void set_statusbar_text(string str);
    void refresh_background();

 private slots:
    void on_prev_button_clicked();
    void on_next_button_clicked();
    void on_start_button_clicked();
    void on_timemode_clicked();
    void game_closed();
};

#endif // LOGINWINDOW_H
