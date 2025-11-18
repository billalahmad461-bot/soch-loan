#pragma once
#include<vector>
#include<string>
#include"home-loan.h"

class LoanSelection {
private:
    std::vector<HomeLoan> _home_loans;
public:
    LoanSelection();
    LoanSelection(const std::string &file_name);
    bool storeHomeLoans(const std::string &file_name);
    bool homeLoansInArea(const std::string &utterence);
    bool selectHome();
    bool payPerMonth();
    bool monthlyInstallment();
};
