#include "loginwindow.h"
#include "gameinstance.h"
#include "recordmanager.h"
#include "ui_loginwindow.h"
#include <sstream>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>
using std::ostringstream;

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}


LoginWindow::LoginWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::LoginWindow),
    rm(new RecordManager()),
    current_level(1),
    started(false)
{
    ui -> setupUi(this); // Set up the widgets described in the ui file
}

LoginWindow::~LoginWindow()
{
    delete rm;
    delete ui;
}

void LoginWindow::set_statusbar_text(string str)
{
    ui -> statusBar -> showMessage(QString::fromStdString(str));
}

void LoginWindow::refresh_background()
{
    ostringstream buf;
    buf << "#centralWidget { border-image: url(\":/resources/images/login_pic/level_" << current_level << ".png\"); }";
    ui -> centralWidget -> setStyleSheet(QString::fromStdString(buf.str()));
}

void LoginWindow::start_game()
{
    if (started) return;
    game = new GameInstance(current_level, rm -> get_record(current_level));
    connect(game, SIGNAL(game_over()), this, SLOT(game_closed()));
    started = true;
}

void LoginWindow::game_closed()
{
    int result = game->fetch_result();
    if (rm->get_record(current_level) == -1 && result != -1&& result != -2 ){
        rm->update_record(current_level, result);
    }
    else if (rm->get_record(current_level) > result && result != -1&& result != -2) {
        rm->update_record(current_level, result);
    }
    started = false;
    delete this->game;
}

void LoginWindow::on_prev_button_clicked()
{
  // First clear the message
  statusBar()->showMessage("");
  if(current_level == 1) statusBar()->showMessage("You are already at the minimal level.");
  else {
    current_level--;
    refresh_background();
  }
}

void LoginWindow::on_next_button_clicked()
{
    // First clear the message
    statusBar()->showMessage("");

    if(current_level == 3)
        statusBar()->showMessage("You are already at the maximal level.");
    else{
        if (rm->get_record(current_level) == -1){
            statusBar()->showMessage("You can not move to the next level before passing the level.");
        }
        else {
           current_level++;
           refresh_background();
        }
    }
}

void LoginWindow::on_start_button_clicked()
{
    statusBar()->showMessage("");
    start_game();
}

void LoginWindow::on_timemode_clicked()
{
    statusBar()->showMessage("");
    start_game();
}


