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
    std::string getArea();
    std::string getSize();
    int getInstallments();
    std::string getPrice();
    std::string getDownPayment();
};
