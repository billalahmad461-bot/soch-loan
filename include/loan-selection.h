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
    bool displayHomeLoansForArea(std::vector<HomeLoan> home_loans, std::string area);
    bool payPerMonth();
    bool monthlyInstallment();
};
