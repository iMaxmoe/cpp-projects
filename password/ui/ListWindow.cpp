#include "ListWindow.h"
#include <vector>
using namespace std;

ListWindow::ListWindow(QWidget *parent) :
    QMainWindow(parent),
    addWindow(),
    recordWindow(new RecordWindow),
    ui(new Ui::ListWindow),
    rm(new RecordManager),
    mp(new MasterPassword)
{
    ui->setupUi(this);
    ui->searchEdit->setPlaceholderText("Search Bar");
    connect(this->ui->addButton,&QPushButton::clicked,this,&ListWindow::addItem_clicked);
    connect(this->ui->settingButton,&QPushButton::clicked,this,&ListWindow::setting_clicked);
    connect(recordWindow, &RecordWindow::deleted, this, &ListWindow::login_deleted);
    connect(recordWindow, &RecordWindow::deleted, this, &ListWindow::subWindow_closed_handler);
    connect(recordWindow, &RecordWindow::RecordClosed, this, &ListWindow::subWindow_closed_handler);
    for (int i =0; i<27; ++i)
        hasShown[i] = false;
    ui->listWidget->setStyleSheet("background-color:transparent");
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    // create the bank
    if (rm->get_all_record().empty()) myBank = new Bank;
    else myBank = new Bank(rm->get_all_record());
    refresh(); // add the items in the bank to listview
    // search
    connect(ui->searchButton, &QPushButton::clicked, this, &ListWindow::search_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &ListWindow::back_clicked);
    refresh();
}

ListWindow::~ListWindow()
{
    QMessageBox::information(this,tr("Reminder"),tr("Saving your modification..."));
    rm->update_record(myBank);
    delete mp;
    delete rm;
    delete myBank;
    delete ui;
}

void ListWindow::closeEvent(QCloseEvent* event){
    delete this; // call the destructor if the list window is closed by the user
}

void ListWindow::subWindow_closed_handler(){
    this->show(); // show listwindow again
}

void ListWindow::addItem_clicked(){
    this->addWindow = new AddWindow(nullptr, myBank);
    // connect the add/ delete events to bank operations
    connect(this->addWindow, &AddWindow::saved, this, &ListWindow::login_added);
    connect(this->addWindow, &AddWindow::closed, this, &ListWindow::subWindow_closed_handler);
    addWindow->show();
    this->hide();
}

void ListWindow::create_addItem(QString login){
    QListWidgetItem *log = new QListWidgetItem;
    QFont f = QFont();
    f.setPointSize(18);
    log->setFont(f);
    log->setText(login);
    log->setSizeHint(QSize(60,60));// set font size
    ui->listWidget->addItem(log);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(open_recordWindow(QListWidgetItem*)));
    QChar str = login.front();
    if ((str == "A"||str=="a")){
        if (!hasShown[0]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("A");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[0]=true;
        }
    }
    else if ((str == "B"||str=="b")){
        if (!hasShown[1]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("B");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[1]=true;
        }
    }
    else if ((str == "C"||str=="c")){
        if (!hasShown[2]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("C");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[2]=true;
        }
    }
    else if ((str == "D"||str=="d")){
        if (!hasShown[3]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("D");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[3]=true;
        }
    }
    else if ((str == "E"||str=="e")){
        if (!hasShown[4]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("E");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[4]=true;
        }
    }
    else if ((str == "F"||str=="f")){
        if (!hasShown[5]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("F");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[5]=true;
        }
    }
    else if ((str == "G"||str=="g")){
        if (!hasShown[6]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("G");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[6]=true;
        }
    }
    else if ((str == "H"||str=="h")){
        if (!hasShown[7]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("H");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[7]=true;
        }
    }
    else if ((str == "I"||str=="i")){
        if (!hasShown[8]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("I");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[8]=true;
        }
    }
    else if ((str == "J"||str=="j")){
        if (!hasShown[9]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("J");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[9]=true;
        }
    }
    else if ((str == "K"||str=="k")){
        if (!hasShown[10]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("K");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[10]=true;
        }
    }
    else if ((str == "L"||str=="l")){
        if (!hasShown[11]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("L");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[11]=true;
        }
    }
    else if ((str == "M"||str=="m")){
        if (!hasShown[12]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("M");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[12]=true;
        }
    }
    else if ((str == "N"||str=="n")){
        if (!hasShown[13]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("N");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[13]=true;
        }
    }
    else if ((str == "O"||str=="o")){
        if (!hasShown[14]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("O");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[14]=true;
        }
    }
    else if ((str == "P"||str=="p")){
        if (!hasShown[15]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("P");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[15]=true;
        }
    }
    else if ((str == "Q"||str=="q")){
        if (!hasShown[16]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("Q");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[16]=true;
        }
    }
    else if ((str == "R"||str=="r")){
        if (!hasShown[17]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("R");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[17]=true;
        }
    }
    else if ((str == "S"||str=="s")){
        if (!hasShown[18]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("S");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[18]=true;
        }
    }
    else if ((str == "T"||str=="t")){
        if (!hasShown[19]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("T");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[19]=true;
        }
    }
    else if ((str == "U"||str=="u")){
        if (!hasShown[20]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("U");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[20]=true;
        }
    }
    else if ((str == "V"||str=="v")){
        if (!hasShown[21]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("V");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[21]=true;
        }
    }
    else if ((str == "W"||str=="w")){
        if (!hasShown[22]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("W");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[22]=true;
        }
    }
    else if ((str == "X"||str=="x")){
        if (!hasShown[23]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("X");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[23]=true;
        }
    }
    else if ((str == "Y"||str=="y")){
        if (!hasShown[24]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("Y");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[24]=true;
        }
    }
    else if ((str == "Z"||str=="z")){
        if(!hasShown[25]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("Z");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[25]=true;
        }
    }
    else{
        if (!hasShown[26]){
            QListWidgetItem *snap = new QListWidgetItem;
            QFont font = QFont();
            font.setBold(true);
            font.setPointSize(22);
            snap->setFont(font);
            snap->setText("#");
            snap->setSizeHint(QSize(60,60));// set font size
            ui->listWidget->addItem(snap);
            hasShown[26]=true;
        }
    }
    ui->listWidget->sortItems(Qt::AscendingOrder); // in alphabet order
    this->show(); // hide addwindow already, show this window
}

void ListWindow::open_recordWindow(QListWidgetItem* item){
    QFont f = item->font();
    if (f.bold()==false){ // Not indicator
        this->hide();
        QString loginName = item->text();
        Account* current = nullptr;
        myBank->find_record(loginName, current);
        recordWindow->change_login_name_label(current->get_login_name());
        recordWindow->change_account_label(current->get_account_name());
        recordWindow->change_password_label(current->get_password());
        current = nullptr;
        recordWindow->show();
    }
}

void ListWindow::login_added(QString login, QString account, QString password) {
    Account* added = new Account(login, account, password);
    myBank->add_record(added);
    vector<Account*> v;
    myBank->output_bank(v);
    refresh();
}

void ListWindow::login_deleted(QString login) {
    vector<Account*> v;
    myBank->output_bank(v);
    Account* temp = nullptr;
    myBank->find_record(login, temp);
    if (temp != nullptr) myBank->delete_record(temp);
    temp = nullptr;
    refresh();
}

void ListWindow::refresh() {
    // refresh the UI
    vector<Account*> logins;
    logins.clear();
    myBank->output_bank(logins);
    // First clear the list view
    ui->listWidget->clear();
    // Clear the index
    for (int i =0; i<27; ++i)
        hasShown[i] = false;
    // Add all the items to listview
    for (unsigned int i = 0; i < logins.size(); i++) {
        QStringList sum = logins.at(i)->toString().split(' ');
        create_addItem(sum.at(0));
    }
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

void ListWindow::search_clicked() {
    QString searchItem = ui->searchEdit->text();
    vector<Account*> matched;
    myBank->get_record(searchItem, matched);
    ui->listWidget->clear();
    for (int i =0; i<27; ++i)
        hasShown[i] = false;
    for (unsigned int i = 0; i < matched.size(); i++) {
        QStringList sum = matched.at(i)->toString().split(' ');
        create_addItem(sum.at(0));
    }
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

void ListWindow::back_clicked() {
    refresh();
}

/****************************************************************
 * Widget: setting master password
****************************************************************/
void ListWindow::setting_clicked(){
    masterWindow = new ChangeMasterPassword;
    connect(masterWindow, &ChangeMasterPassword::confirmed, this, &ListWindow::change_password);
    connect(this->masterWindow, &ChangeMasterPassword::masterClosed, this, &ListWindow::close_masterWindow);
    masterWindow->show();
    this->hide();
}

void ListWindow::close_masterWindow(){
    this->show();
}

void ListWindow::change_password(QString newPassword) {
    mp->change_master_password(newPassword);
    mp->update_master_password();
    this->show();
}

