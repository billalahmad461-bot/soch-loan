#pragma once
#include<vector>
#include<string>
#include"home-loan.h"

class Display {
public:
    void greetingResponse(const std::string &utterence);
    void undefinedInputResponse(const std::string &utterence);
    void displyLoanTypes(const std::string &utterence);
    void selectAreaDisplay(const std::string &utterence);
    void homeLoanDisplay(const std::vector<HomeLoan> &home_loan, int start, int end);
    void selectHomeDisplay();
    void payPerMonthDisplay(const std::string &price);
    void isInstallmentPlanNeed();
    void monthlyInstallmentDisplay(const std::string &total_price, const std::string &down_payment, const std::vector<std::string> &installments, const std::vector<std::string> &remaining_price);
};
