#include "display.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <thread>
#include <chrono>
#include <map>
#include <vector>

// -------------------- COLOR + ANIMATION HELPERS --------------------

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void typeText(const std::string &text, int speed = 15) {
    for (char c : text) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

void boxTop() {
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
}

void boxBottom() {
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
}

// -------------------- UTTERANCE LOADER ----------------------------

std::map<std::string, std::string> loadResponses(const std::string &filename) {
    std::map<std::string, std::string> responses;
    std::ifstream file(filename);
    if (!file) {
        setColor(12);
        std::cerr << "Error: Could not open utterances file!\n";
        setColor(7);
        return responses;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delim = line.find('#');
        if (delim != std::string::npos) {
            std::string key = line.substr(0, delim);
            std::string value = line.substr(delim + 1);
            responses[key] = value;
        }
    }
    return responses;
}

// -------------------- DISPLAY CLASS IMPLEMENTATION ----------------

Display::Display(const std::string &utterFile) {
    responses = loadResponses(utterFile);
}

// -------------------- GREETING / GENERAL RESPONSES ----------------

void Display::greetingResponse(const std::string &utterance) {
    system("cls");

    setColor(11);
    boxTop();
    std::cout << "║";
    setColor(14);
    std::cout << std::setw(34) << "WELCOME TO SOCH LOAN";
    setColor(11);
    std::cout << std::setw(24) << "║" << std::endl;
    boxBottom();

    setColor(10);
    if (responses.count(utterance))
        typeText("\n" + responses[utterance] + "\n\n");
    else if (responses.count("*"))
        typeText("\n" + responses["*"] + "\n\n");
    else
        typeText("\nHi! I'll be happy to help. Please press A if you want to apply for loan. Press X to exit\n");
    setColor(7);
}

// -------------------- UNDEFINED INPUT RESPONSE -------------------

void Display::undefinedInputResponse(const std::string &utterance) {
    setColor(12);
    if (responses.count("*"))
        typeText(responses["*"] + "\n");  // fetch from utterances.txt
    else
        typeText("Hi! I'll be happy to help. Please press A if you want to apply for loan. Press X to exit\n");
    setColor(7);
}

// -------------------- LOAN TYPE DISPLAY ---------------------------

void Display::displyLoanTypes(const std::string &utterance) {
    setColor(14);
    std::cout << "\nAvailable Loan Types:\n\n";

    setColor(11);
    std::cout << "┌───────────────┬───────────────────────────┐\n";
    std::cout << "│  Loan Type    │         Description        │\n";
    std::cout << "├───────────────┼───────────────────────────┤\n";
    std::cout << "│ Home Loan     │ For buying a house         │\n";
    std::cout << "│ Car Loan      │ For purchasing a vehicle   │\n";
    std::cout << "│ Bike Loan     │ For electric/petrol bikes  │\n";
    std::cout << "└───────────────┴───────────────────────────┘\n";

    setColor(10);
    if (responses.count(utterance))
        typeText("\n" + responses[utterance] + "\n");
    else if (responses.count("*"))
        typeText("\n" + responses["*"] + "\n");
    else
        typeText("\nPlease select a loan type...\n");
    setColor(7);
}

// -------------------- AREA SELECTION DISPLAY ---------------------

void Display::selectAreaDisplay(const std::string &utterance) {
    setColor(11);
    std::cout << "\nSelect Area Category:\n\n";

    setColor(14);
    std::cout << "┌───────────────┬──────────────┐\n";
    std::cout << "│  Category     │   Example    │\n";
    std::cout << "├───────────────┼──────────────┤\n";
    std::cout << "│ City Area     │ Lahore       │\n";
    std::cout << "│ Suburban      │ Bahria Town  │\n";
    std::cout << "│ Rural         │ Village Area │\n";
    std::cout << "└───────────────┴──────────────┘\n";

    setColor(10);
    if (responses.count(utterance))
        typeText("\n" + responses[utterance] + "\n");
    else if (responses.count("*"))
        typeText("\n" + responses["*"] + "\n");
    else
        typeText("\nEnter your preferred area...\n");
    setColor(7);
}

// -------------------- HOME LOAN DISPLAY ---------------------------

void Display::homeLoanDisplay(const std::vector<HomeLoan> &home_loan, int start, int end) {
    if (home_loan.empty()) {
        setColor(12);
        std::cout << "No home loan plans available!\n";
        setColor(7);
        return;
    }

    setColor(11);
    std::cout << "\nAVAILABLE HOME LOAN PLANS:\n\n";

    setColor(14);
    std::cout << "┌────┬──────────────┬───────────┬──────────────┬──────────────┐\n";
    std::cout << "│ ID │ Area         │ Size      │ Price        │ Installments │\n";
    std::cout << "├────┼──────────────┼───────────┼──────────────┼──────────────┤\n";

    for (int i = start; i <= end && i < (int)home_loan.size(); i++) {
        std::cout << "│ "
                  << std::setw(2) << i + 1 << " │ "
                  << std::setw(12) << home_loan[i].getArea() << " │ "
                  << std::setw(9) << home_loan[i].getSize() << " │ "
                  << std::setw(12) << home_loan[i].getPrice() << " │ "
                  << std::setw(12) << home_loan[i].getInstallments() << " │\n";
    }

    std::cout << "└────┴──────────────┴───────────┴──────────────┴──────────────┘\n";

    setColor(10);
    typeText("\nEnter the ID of the plan you want to view...\n");
    setColor(7);
}

// -------------------- HOME PLAN SELECTION -------------------------

void Display::selectHomeDisplay() {
    setColor(14);
    typeText("\nEnter Home Plan Number: ");
    setColor(7);
}

// -------------------- MONTHLY PAYMENT DISPLAY --------------------

void Display::payPerMonthDisplay(const std::string &price) {
    setColor(11);
    std::cout << "\nMonthly Payment:\n\n";

    setColor(10);
    std::cout << "┌─────────────────────────┐\n";
    std::cout << "│  Monthly: PKR " << price << "     │\n";
    std::cout << "└─────────────────────────┘\n";

    setColor(7);
}

// -------------------- INSTALLMENT PLAN PROMPT --------------------

void Display::isInstallmentPlanNeed() {
    setColor(14);
    typeText("\nDo you want to view the installment breakdown? (yes/no): ");
    setColor(7);
}

// -------------------- INSTALLMENT BREAKDOWN DISPLAY --------------

void Display::monthlyInstallmentDisplay(
    const std::string &total_price,
    const std::string &down_payment,
    const std::vector<std::string> &installments,
    const std::vector<std::string> &remaining_price)
{
    setColor(11);
    std::cout << "\nINSTALLMENT BREAKDOWN\n";

    setColor(14);
    std::cout << "┌───────────────┬─────────────────────────┐\n";
    std::cout << "│ Total Price   │ PKR " << std::setw(20) << total_price << " │\n";
    std::cout << "│ Down Payment  │ PKR " << std::setw(20) << down_payment << " │\n";
    std::cout << "└───────────────┴─────────────────────────┘\n\n";

    std::cout << "┌───────────┬───────────────────┬─────────────────────┐\n";
    std::cout << "│ Month     │ Installment (PKR) │ Remaining (PKR)    │\n";
    std::cout << "├───────────┼───────────────────┼─────────────────────┤\n";

    for (std::size_t i = 0; i < installments.size(); i++) {
        std::cout << "│ "
                  << std::setw(5) << (i + 1) << "    │ "
                  << std::setw(15) << installments[i] << " │ "
                  << std::setw(19) << remaining_price[i] << " │\n";
    }

    std::cout << "└───────────┴───────────────────┴─────────────────────┘\n";

    setColor(10);
    typeText("\nHope this helps! Let me know if you want another plan.\n");
    setColor(7);
}
