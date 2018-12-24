#include "Bank.h"

Bank::Bank(vector<Account*> record_list)
{
    unsigned int i = 0;
    while(record_list.size() > i) {
        add_record(record_list[i]);
        i += 1;
    }
}

void Bank::output_bank(Account* p, vector<Account*>& x){
    if (p == nullptr) return;
    x.push_back(p);
    output_bank(p->left, x);
    output_bank(p->right, x);
}

void Bank::output_bank(vector<Account*>& x) {
    output_bank(root, x);
}

Account* Bank::rotate_left(Account* a) {
    Account* b = a->right;
    a->right = b->left;
    b->left = a;
    fix_height(a);
    fix_height(b);
    return b;
}

Account* Bank::rotate_right(Account* a) {
    Account* b = a->left;
    a->left = b->right;
    b->right = a;
    fix_height(a);
    fix_height(b);
    return b;
}

Account* Bank::add_record(Account* p, Account* added) {
    if (p == nullptr) return added; // If it is an empty tree
    if (added->get_login_name() <= p->get_login_name())
        p->left = add_record(p->left, added);
    else
        p->right = add_record(p->right, added);
    return balance(p);
}

void Bank::add_record(Account* added) {
    root = add_record(root, added);
}

Account* Bank::balance(Account* p) {
    if (!p) return p;
    fix_height(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right)<0)
            p->right = rotate_right(p->right);
        return rotate_right(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left)>0)
            p->left = rotate_right(p->left);
        return rotate_left(p);
    }
    return p; // balance not required
}

int Bank::bfactor(Account* p) const{
    if (!p) return 0; // if input a nullptr, return 0
    return get_height(p->left) - get_height(p->right);
}

void copy_account_info(Account*& a, Account* b) {
    a->get_login_name() = b->get_login_name();
    a->get_account_name() = b->get_account_name();
    a->get_password() = b->get_password();
}

Account* Bank::delete_record(Account* p, Account* q) {
    if (p == nullptr) return p; // item not found
    if (q->get_login_name() < p->get_login_name())
        p->left = delete_record(p->left, q);
    else if (q->get_login_name() > p->get_login_name())
        p->right = delete_record(p->right, q);
    else { // Record found. Modify the tree.
        Account* l = p->left;
        Account* r = p->right;
        delete p;
        if (r == nullptr) return l;
        Account* min = find_min(r);
        min->right = remove_min(r);
        min->left = l;
        return balance(min);
    }
    return balance(p);
}

void Bank::delete_record(Account* q) {
    root = delete_record(root, q);
}

Account* Bank::find_min(Account* p) const {
    return p->left? find_min(p->left): p;
}

Account* Bank::remove_min(Account* p) {
    if (p->left == nullptr) return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}

int Bank::get_height(Account* p) const{
    return p? p->height: -1;
}

void Bank::fix_height(Account* p) const{
    int hl = get_height(p->left);
    int hr = get_height(p->right);
    p->height = (hl>hr ? hl:hr)+1;
}

void Bank::get_record(Account* p, QString input, vector<Account*>& output) const{
    if (p == nullptr) return;
    int len = input.length();
    QString sub_login_name = (p->get_login_name().length()>len)? p->get_login_name().mid(0,len): p->get_login_name();
    if (input < sub_login_name)
        get_record(p->left, input, output);
    else if (input > sub_login_name)
        get_record(p->right, input, output);
    else {
        output.push_back(p);
        get_record(p->left, input, output);
        get_record(p->right, input, output);
    }
}

void Bank::get_record(QString input, vector<Account*>& output) const{
    get_record(root, input, output);
}

void Bank::find_record(Account* p, QString input, Account*& result) {
    if (p == nullptr) return;
    QString sub_login_name = p->get_login_name();
    if (input < sub_login_name)
        find_record(p->left, input, result);
    else if (input > sub_login_name)
        find_record(p->right, input, result);
    else {
        result = p;
    }
    return;
}

void Bank::find_record(QString input, Account*& result) {
    find_record(root, input, result);
}
