#ifndef BANK_H
#define BANK_H

#include <QString>
#include <vector>

#include "account.h"
using namespace std;

/* Bank: AVL database*/
class Bank
{
private:
    Account* root = nullptr;
    int get_height(Account*) const;
    int bfactor(Account*) const;
    void fix_height(Account*) const;
    Account* rotate_left(Account* a);
    Account* rotate_right(Account* a);
    Account* balance(Account*);
    Account* find_min(Account*) const;
    Account* remove_min(Account* p);

public:
    Bank() = default;
    Bank(vector<Account*>); // create the bank using the record data
    ~Bank() {delete root;}
    bool is_empty() const {return root == nullptr;}
    void get_record(Account*, QString, vector<Account*>&) const; // match the prefix of the login name
    void get_record(QString, vector<Account*>&) const;
    Account* add_record(Account*, Account*); // helper function
    void add_record(Account*); // AVL insertion
    Account* delete_record(Account*, Account*); // helper
    void delete_record(Account*);
    void output_bank(Account* p, vector<Account*>& x); // List all the items in the bank. Used in: Listview, save record
    void output_bank(vector<Account*>& x);
    void find_record(Account*, QString, Account*&); // helper function
    void find_record(QString, Account*&);
};

#endif // BANK_H
