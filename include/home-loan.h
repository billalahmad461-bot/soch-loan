#pragma once
#include<string>
class HomeLoan {
private:
    std::string _area;
    std::string _size;
    int _installments;
    std::string _price;
    std::string _down_payment;
public:
    HomeLoan();
    HomeLoan(std::string area, std::string size, int installments, std::string price, std::string down_payment);
    
    // ADD CONST TO ALL GETTERS
    std::string getArea() const;
    std::string getSize() const;
    int getInstallments() const;
    std::string getPrice() const;
    std::string getDownPayment() const;
};