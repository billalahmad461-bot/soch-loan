#include "../include/home-loan.h"
#include <stdexcept>

// Default constructor - initializes all members to safe default values
HomeLoan::HomeLoan() 
    : _area("Unknown"), _size("Unknown"), _installments(0), _price("0"), _down_payment("0") {}

// Parameterized constructor with validation
HomeLoan::HomeLoan(std::string area, std::string size, int installments, 
                   std::string price, std::string down_payment)
    : _area(area), _size(size), _installments(installments), 
      _price(price), _down_payment(down_payment) {
    
    // Validate input parameters
    if (_area.empty()) {
        _area = "Unknown Area";
    }
    
    if (_size.empty()) {
        _size = "Unknown Size";
    }
    
    if (_installments < 0) {
        _installments = 0; // Prevent negative installments
    }
    
    if (_price.empty()) {
        _price = "0";
    }
    
    if (_down_payment.empty()) {
        _down_payment = "0";
    }
}

// Getter for area with basic validation
std::string HomeLoan::getArea() {
    if (_area.empty()) {
        return "Area Not Specified";
    }
    return _area;
}

// Getter for size with basic validation
std::string HomeLoan::getSize() {
    if (_size.empty()) {
        return "Size Not Specified";
    }
    return _size;
}

// Getter for installments with validation
int HomeLoan::getInstallments() {
    if (_installments < 0) {
        return 0; // Return 0 instead of negative value
    }
    return _installments;
}

// Getter for price - returns the original formatted string with commas
std::string HomeLoan::getPrice() {
    if (_price.empty()) {
        return "0";
    }
    return _price;
}

// Getter for down payment - returns the original formatted string with commas
std::string HomeLoan::getDownPayment() {
    if (_down_payment.empty()) {
        return "0";
    }
    return _down_payment;
}
