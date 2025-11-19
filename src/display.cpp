#include "../include/display.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <thread>
#include <chrono>

// -------------------- COLOR + ANIMATION HELPERS --------------------
void Display::setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Display::typeText(const std::string &text, int speed) {
    for (char c : text) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

void Display::boxTop() {
    std::cout << "+------------------------------------------------------------+\n";
}

void Display::boxBottom() {
    std::cout << "+------------------------------------------------------------+\n";
}

// -------------------- GREETING --------------------
void Display::greetingResponse(const std::string &utterance) {
    setColor(11);
    boxTop();
    std::cout << "|";
    setColor(14);
    std::cout << std::setw(34) << "WELCOME TO SOCH LOAN";
    setColor(11);
    std::cout << std::setw(12) << "|" << "\n";
    boxBottom();
    setColor(10);
    typeText("\n" + utterance + "\n\n");
    setColor(7);
}

// -------------------- UNDEFINED INPUT --------------------
void Display::undefinedInputResponse(const std::string &utterance) {
    setColor(12);
    typeText(utterance + "\n");
    setColor(7);
}

// -------------------- LOAN TYPES --------------------
void Display::displyLoanTypes(const std::string &utterance) {
    setColor(14);
    std::cout << "\nAvailable Loan Types:\n\n";
    setColor(11);
    std::cout << "+---------------+---------------------------+\n";
    std::cout << "| Loan Type     | Description               |\n";
    std::cout << "+---------------+---------------------------+\n";
    std::cout << "| Home Loan     | For buying a house       |\n";
    std::cout << "| Car Loan      | For purchasing a vehicle |\n";
    std::cout << "| Bike Loan     | For electric/petrol bikes|\n";
    std::cout << "+---------------+---------------------------+\n";
    setColor(10);
    typeText("\nPlease select a loan type...\n");
    setColor(7);
}

// -------------------- AREA SELECTION --------------------
void Display::selectAreaDisplay(const std::string &utterance) {
    setColor(11);
    std::cout << "\nSelect Area Category:\n\n";
    setColor(14);
    std::cout << "+-------------+------------+\n";
    std::cout << "| Category    | Example    |\n";
    std::cout << "+-------------+------------+\n";
    std::cout << "| City Area   | Lahore     |\n";
    std::cout << "| Suburban    | Bahria Town|\n";
    std::cout << "| Rural       | Village    |\n";
    std::cout << "+-------------+------------+\n";
    setColor(10);
    typeText("\nEnter your preferred area...\n");
    setColor(7);
}

// -------------------- OTHER FUNCTIONS --------------------
void Display::selectHomeDisplay() {
    setColor(14);
    typeText("\nEnter Home Plan Number: ");
    setColor(7);
}

void Display::payPerMonthDisplay(const std::string &payment_info) {
    setColor(11);
    std::cout << "\nMonthly Payment:\n\n";
    setColor(10);
    typeText(payment_info + "\n");
    setColor(7);
}

void Display::isInstallmentPlanNeed(const std::string &prompt) {
    setColor(14);
    typeText("\n" + prompt + ": ");
    setColor(7);
}

void Display::monthlyInstallmentDisplay(
    const std::string &total_price,
    const std::string &down_payment,
    const std::vector<std::string> &installments,
    const std::vector<std::string> &remaining_price)
{
    setColor(11);
    std::cout << "\nINSTALLMENT BREAKDOWN\n\n";
    setColor(14);
    std::cout << "+----------------+--------------------+\n";
    std::cout << "| Total Price    | PKR " << std::setw(15) << total_price << " |\n";
    std::cout << "| Down Payment   | PKR " << std::setw(15) << down_payment << " |\n";
    std::cout << "+----------------+--------------------+\n\n";

    std::cout << "+-------+-----------------+-----------------+\n";
    std::cout << "| Month | Installment (PKR)| Remaining (PKR) |\n";
    std::cout << "+-------+-----------------+-----------------+\n";

    for (size_t i = 0; i < installments.size(); i++) {
        std::cout << "| " << std::setw(5) << (i + 1)
                  << " | " << std::setw(15) << installments[i]
                  << " | " << std::setw(15) << remaining_price[i] << " |\n";
    }

    std::cout << "+-------+-----------------+-----------------+\n";
    setColor(10);
    typeText("\nHope this helps! Let me know if you want another plan.\n");
    setColor(7);
}
