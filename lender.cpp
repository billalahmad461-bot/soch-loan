#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../include/application-handler.h"

void printApplication(const Application& app) {
    std::cout << "ID: " << app.app_id << "\n";
    std::cout << "Loan Type: " << app.loan_type << "\n";
    std::cout << "Sub Type: " << app.sub_type << "\n";
    std::cout << "Plan ID: " << app.plan_id << "\n";
    std::cout << "Full Name: " << app.full_name << "\n";
    std::cout << "Father's Name: " << app.father_name << "\n";
    std::cout << "Postal Address: " << app.postal_address << "\n";
    std::cout << "Contact Number: " << app.contact_number << "\n";
    std::cout << "Email: " << app.email_address << "\n";
    std::cout << "CNIC: " << app.cnic_number << "\n";
    std::cout << "CNIC Expiry: " << app.cnic_expiry << "\n";
    std::cout << "Employment: " << app.employment_status << "\n";
    std::cout << "Marital: " << app.marital_status << "\n";
    std::cout << "Gender: " << app.gender << "\n";
    std::cout << "Dependents: " << app.num_dependents << "\n";
    std::cout << "Annual Income: " << app.annual_income << "\n";
    std::cout << "Avg Electricity: " << app.avg_electricity << "\n";
    std::cout << "Current Electricity: " << app.current_electricity << "\n";
    std::cout << "Existing Loans: " << app.existing_loans << "\n"; // can parse if needed
    std::cout << "Ref1 Name: " << app.ref1_name << "\n";
    std::cout << "Ref1 CNIC: " << app.ref1_cnic << "\n";
    std::cout << "Ref1 Issue: " << app.ref1_issue << "\n";
    std::cout << "Ref1 Phone: " << app.ref1_phone << "\n";
    std::cout << "Ref1 Email: " << app.ref1_email << "\n";
    std::cout << "Ref2 Name: " << app.ref2_name << "\n";
    std::cout << "Ref2 CNIC: " << app.ref2_cnic << "\n";
    std::cout << "Ref2 Issue: " << app.ref2_issue << "\n";
    std::cout << "Ref2 Phone: " << app.ref2_phone << "\n";
    std::cout << "Ref2 Email: " << app.ref2_email << "\n";
    std::cout << "CNIC Front: " << app.cnic_front << "\n";
    std::cout << "CNIC Back: " << app.cnic_back << "\n";
    std::cout << "Electricity Bill: " << app.elec_bill << "\n";
    std::cout << "Salary Slip: " << app.salary_slip << "\n";
    std::cout << "Status: " << app.status << "\n";
    std::cout << "Starting Month: " << app.starting_month << "\n";
}

int main() {
    ApplicationHandler handler;
    handler.load("data/applications.txt");

    int choice;
    while (true) {
        std::cout << "1. List applications\n";
        std::cout << "2. View details\n";
        std::cout << "3. Approve\n";
        std::cout << "4. Reject\n";
        std::cout << "5. Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            for (const auto& app : handler.getApplications()) {
                std::cout << app.app_id << " " << app.full_name << " " << app.cnic_number << " " << app.status << "\n";
            }
        } else if (choice == 2) {
            std::string id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            const Application* app = handler.getById(id);
            if (app) {
                printApplication(*app);
            } else {
                std::cout << "Not found.\n";
            }
        } else if (choice == 3 || choice == 4) {
            std::string id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            Application* app = handler.getById(id);
            if (app && app->status == "submitted") {
                app->status = (choice == 3) ? "approved" : "rejected";
                handler.save("data/applications.txt");
                std::cout << "Updated.\n";
            } else {
                std::cout << "Cannot update.\n";
            }
        } else if (choice == 5) {
            break;
        }
    }

    return 0;
}
