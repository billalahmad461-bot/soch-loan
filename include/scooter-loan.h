#pragma once
#include <string>

class ScooterLoan {
private:
    std::string _make;
    std::string _model;
    std::string _distance;
    std::string _charging_time;
    std::string _max_speed;
    int _installments;
    std::string _price;
    std::string _down_payment;
public:
    ScooterLoan();
    ScooterLoan(std::string make, std::string model, std::string distance, std::string charging_time, std::string max_speed, int installments, std::string price, std::string down_payment);
    
    std::string getMake() const;
    std::string getModel() const;
    std::string getDistance() const;
    std::string getChargingTime() const;
    std::string getMaxSpeed() const;
    int getInstallments() const;
    std::string getPrice() const;
    std::string getDownPayment() const;
};
