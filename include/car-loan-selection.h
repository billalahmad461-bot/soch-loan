#pragma once
#include <vector>
#include <string>
#include "car-loan.h"

class CarLoanSelection {
private:
    std::vector<CarLoan> _car_loans;
public:
    CarLoanSelection();
    CarLoanSelection(const std::string &file_name);
    bool storeCarLoans(const std::string &file_name);
    std::vector<CarLoan> carsInMake(const std::string &make);
    std::string calculateMonthlyPayment(const CarLoan &loan) const;
    void calculateInstallmentBreakdown(const CarLoan &loan, std::vector<std::string> &installments, std::vector<std::string> &remaining_price, std::string &total_price, std::string &down_payment) const;
};
