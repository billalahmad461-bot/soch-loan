// File: src/application.cpp (Fixed to handle optional final #)
#include "../include/application.h"
#include <sstream>
#include <iostream>
#include <vector>

Application::Application() : status("submitted") {}

std::string Application::serialize() const {
    std::stringstream ss;
    ss << app_id << "#"
       << loan_type << "#"
       << sub_type << "#"
       << plan_id << "#"
       << full_name << "#"
       << father_name << "#"
       << postal_address << "#"
       << contact_number << "#"
       << email_address << "#"
       << cnic_number << "#"
       << cnic_expiry << "#"
       << employment_status << "#"
       << marital_status << "#"
       << gender << "#"
       << num_dependents << "#"
       << annual_income << "#"
       << avg_electricity << "#"
       << current_electricity << "#"
       << existing_loans << "#"
       << ref1_name << "#"
       << ref1_cnic << "#"
       << ref1_issue << "#"
       << ref1_phone << "#"
       << ref1_email << "#"
       << ref2_name << "#"
       << ref2_cnic << "#"
       << ref2_issue << "#"
       << ref2_phone << "#"
       << ref2_email << "#"
       << cnic_front << "#"
       << cnic_back << "#"
       << elec_bill << "#"
       << salary_slip << "#"
       << status << "#"
       << starting_month;
    return ss.str();
}

void Application::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(ss, token, '#')) {
        parts.push_back(token);
    }
    size_t num = parts.size();
    if (num == 34 || num == 35) {
        app_id = parts[0];
        loan_type = parts[1];
        sub_type = parts[2];
        plan_id = parts[3];
        full_name = parts[4];
        father_name = parts[5];
        postal_address = parts[6];
        contact_number = parts[7];
        email_address = parts[8];
        cnic_number = parts[9];
        cnic_expiry = parts[10];
        employment_status = parts[11];
        marital_status = parts[12];
        gender = parts[13];
        num_dependents = parts[14];
        annual_income = parts[15];
        avg_electricity = parts[16];
        current_electricity = parts[17];
        existing_loans = parts[18];
        ref1_name = parts[19];
        ref1_cnic = parts[20];
        ref1_issue = parts[21];
        ref1_phone = parts[22];
        ref1_email = parts[23];
        ref2_name = parts[24];
        ref2_cnic = parts[25];
        ref2_issue = parts[26];
        ref2_phone = parts[27];
        ref2_email = parts[28];
        cnic_front = parts[29];
        cnic_back = parts[30];
        elec_bill = parts[31];
        salary_slip = parts[32];
        status = parts[33];
        if (num == 35) {
            starting_month = parts[34];
        } else {
            starting_month = "";
        }
    } else {
        std::cerr << "Invalid line format - expected 34 or 35 fields, got " << num << "\n";
    }
}
