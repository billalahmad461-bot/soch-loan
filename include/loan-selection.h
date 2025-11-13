#ifndef LOAN_SELECTION_H
#define LOAN_SELECTION_H


#include <string>
using namespace std;


const int MAX_HOME_LOANS = 100;
const int MAX_AREAS = 100; // max distinct areas


struct Homeloan
{
string size;
string area;
string installments;
string price;
string downpayment;
};


extern Homeloan homeloans[MAX_HOME_LOANS];
extern int homeloan_count;


void readHomeloans(const string& filename);
void displayHomeloans();
void displayHomeloansForArea(const string& area);
int getAvailableAreas(string areas[], int maxAreas);


#endif
