#pragma once
#include <string>

class CarLoan {
private:
    std::string _make;
    std::string _model;
    std::string _engine;
    std::string _used;
    std::string _manufacturing_year;
    int _installments;
    std::string _price;
    std::string _down_payment;
public:
    CarLoan();
    CarLoan(std::string make, std::string model, std::string engine, std::string used, std::string year, int installments, std::string price, std::string down_payment);
    
    std::string getMake() const;
    std::string getModel() const;
    std::string getEngine() const;
    std::string getUsed() const;
    std::string getManufacturingYear() const;
    int getInstallments() const;
    std::string getPrice() const;
    std::string getDownPayment() const;
};
