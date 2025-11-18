#include "../include/loan-selection.h"
#include "../include/display.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Default constructor
LoanSelection::LoanSelection() {}

// Parameterized constructor
LoanSelection::LoanSelection(const std::string &file_name) {
    storeHomeLoans(file_name);
}

bool LoanSelection::storeHomeLoans(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {  
        std::cerr << "Error: Could not open file: " << file_name << std::endl;
        return false;
    }

    _home_loans.clear();
    std::string line;
    
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string area, size, installmentsStr, price, down_payment;
        
        // Parse CSV format with # delimiter
        if (std::getline(ss, area, '#') &&
            std::getline(ss, size, '#') &&
            std::getline(ss, installmentsStr, '#') &&
            std::getline(ss, price, '#') &&
            std::getline(ss, down_payment, '#')) {
            
            // Convert installments to integer
            int installments = 0;
            try {
                installments = std::stoi(installmentsStr);
            } catch (const std::exception& e) {
                std::cerr << "Error converting installments to integer: " << installmentsStr << std::endl;
                continue;
            }
            
            // Create HomeLoan object and add to vector
            HomeLoan homeLoan(area, size, installments, price, down_payment);
            _home_loans.push_back(homeLoan);
        }
    }
    
    file.close();
    std::cout << "Loaded " << _home_loans.size() << " home loans from file." << std::endl;
    return true;
}

bool LoanSelection::homeLoansInArea(const std::string &utterence) {
    std::string area = utterence;
    std::transform(area.begin(), area.end(), area.begin(), ::tolower);
    
    std::vector<HomeLoan> filteredLoans;
    
    // WORKAROUND: Remove const from loop
    for (auto& loan : _home_loans) {
        std::string loanArea = loan.getArea();
        std::transform(loanArea.begin(), loanArea.end(), loanArea.begin(), ::tolower);
        
        if (loanArea.find(area) != std::string::npos) {
            filteredLoans.push_back(loan);
        }
    }
    
    if (filteredLoans.empty()) {
        std::cout << "No home loans found for area: " << utterence << std::endl;
        return false;
    }
    
    Display display;
    display.homeLoanDisplay(filteredLoans, 0, filteredLoans.size() - 1);
    return true;
}

bool LoanSelection::selectHome() {
    if (_home_loans.empty()) {
        std::cout << "No home loans available. Please load home loans first." << std::endl;
        return false;
    }
    
    Display display;
    display.homeLoanDisplay(_home_loans, 0, _home_loans.size() - 1);
    return true;
}

bool LoanSelection::payPerMonth() {
    if (_home_loans.empty()) {
        std::cout << "No home loans available for payment calculation." << std::endl;
        return false;
    }
    
    std::vector<std::string> monthlyPayments;
    
    // WORKAROUND: Remove const from loop
    for (auto& loan : _home_loans) {
        std::string priceStr = loan.getPrice();
        std::string downPaymentStr = loan.getDownPayment();
        
        priceStr.erase(std::remove(priceStr.begin(), priceStr.end(), ','), priceStr.end());
        downPaymentStr.erase(std::remove(downPaymentStr.begin(), downPaymentStr.end(), ','), downPaymentStr.end());
        
        try {
            double price = std::stod(priceStr);
            double downPayment = std::stod(downPaymentStr);
            int installments = loan.getInstallments();
            
            if (installments > 0) {
                double monthlyInstallment = (price - downPayment) / installments;
                std::string paymentInfo = loan.getArea() + " - " + loan.getSize() + 
                                         ": Monthly Installment = " + std::to_string((int)monthlyInstallment) + 
                                         " for " + std::to_string(installments) + " months";
                monthlyPayments.push_back(paymentInfo);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error calculating payment for: " << loan.getArea() << std::endl;
            continue;
        }
    }
    
    std::string allPayments;
    for (size_t i = 0; i < monthlyPayments.size(); ++i) {
        allPayments += monthlyPayments[i];
        if (i < monthlyPayments.size() - 1) allPayments += "\n";
    }
    
    Display display;
    display.payPerMonthDisplay(allPayments);
    return true;
}

bool LoanSelection::monthlyInstallment() {
    if (_home_loans.empty()) {
        std::cout << "No home loans available for installment plans." << std::endl;
        return false;
    }
    
    std::vector<std::string> installmentPlans;
    std::vector<std::string> remainingPrices;
    
    // WORKAROUND: Remove const from loop
    for (auto& loan : _home_loans) {
        std::string priceStr = loan.getPrice();
        std::string downPaymentStr = loan.getDownPayment();
        
        priceStr.erase(std::remove(priceStr.begin(), priceStr.end(), ','), priceStr.end());
        downPaymentStr.erase(std::remove(downPaymentStr.begin(), downPaymentStr.end(), ','), downPaymentStr.end());
        
        try {
            double price = std::stod(priceStr);
            double downPayment = std::stod(downPaymentStr);
            int installments = loan.getInstallments();
            
            if (installments > 0) {
                double monthlyInstallment = (price - downPayment) / installments;
                double remainingPrice = price - downPayment;
                
                std::string plan = loan.getArea() + " - " + loan.getSize() + "\n" +
                                 "Total Price: " + loan.getPrice() + "\n" +
                                 "Down Payment: " + loan.getDownPayment() + "\n" +
                                 std::to_string(installments) + " months x " + 
                                 std::to_string((int)monthlyInstallment) + " per month";
                installmentPlans.push_back(plan);
                
                std::string remaining = "Remaining after down payment: " + std::to_string((int)remainingPrice);
                remainingPrices.push_back(remaining);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error creating installment plan for: " << loan.getArea() << std::endl;
            continue;
        }
    }
    
    Display display;
    std::string total_price = "Multiple properties available - see details below";
    std::string down_payment = "Various down payment options available";
    
    display.monthlyInstallmentDisplay(total_price, down_payment, installmentPlans, remainingPrices);
    return true;
}