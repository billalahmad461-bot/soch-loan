#pragma once
#include <vector>
#include <string>
#include "scooter-loan.h"

class ScooterLoanSelection {
private:
    std::vector<ScooterLoan> _scooter_loans;
public:
    ScooterLoanSelection();
    ScooterLoanSelection(const std::string &file_name);
    bool storeScooterLoans(const std::string &file_name);
    std::vector<ScooterLoan> scootersInMake(const std::string &make);
    std::string calculateMonthlyPayment(const ScooterLoan &loan) const;
    void calculateInstallmentBreakdown(const ScooterLoan &loan, std::vector<std::string> &installments, std::vector<std::string> &remaining_price, std::string &total_price, std::string &down_payment) const;
};
