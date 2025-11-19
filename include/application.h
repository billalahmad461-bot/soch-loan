#pragma once
#include <string>
#include <vector>
#include <map>

class Application {
public:
    std::string app_id;
    std::string loan_type;
    std::string sub_type;
    std::string plan_id;
    std::string full_name;
    std::string father_name;
    std::string postal_address;
    std::string contact_number;
    std::string email_address;
    std::string cnic_number;
    std::string cnic_expiry;
    std::string employment_status;
    std::string marital_status;
    std::string gender;
    std::string num_dependents;
    std::string annual_income;
    std::string avg_electricity;
    std::string current_electricity;
    std::string existing_loans;
    std::string ref1_name;
    std::string ref1_cnic;
    std::string ref1_issue;
    std::string ref1_phone;
    std::string ref1_email;
    std::string ref2_name;
    std::string ref2_cnic;
    std::string ref2_issue;
    std::string ref2_phone;
    std::string ref2_email;
    std::string cnic_front;
    std::string cnic_back;
    std::string elec_bill;
    std::string salary_slip;
    std::string status;
    std::string starting_month;

    Application();
    std::string serialize() const;
    void deserialize(const std::string& line);
};
