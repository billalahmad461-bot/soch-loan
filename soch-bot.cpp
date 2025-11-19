#include <iostream>
#include <string>

#include "include/utterence-handler.h"
#include "include/loan-selection.h"
#include "include/display.h"

int main() {
    // 1. Load utterances from file in data/ folder
    UtterenceHandler utterHandler;
    if (!utterHandler.storeUserInputAndResponse("data/utterences.txt")) {
        std::cerr << "Failed to load data/utterences.txt. Exiting...\n";
        return 1;
    }

    // 2. Load home loans from file in data/ folder
    LoanSelection loanSelection;
    if (!loanSelection.storeHomeLoans("data/home.txt")) {
        std::cerr << "Failed to load data/home.txt. Exiting...\n";
        return 1;
    }

    // 3. Initial greeting
    Display display;
    display.greetingResponse("Hi");

    std::string userInput;

    while (true) {
        std::cout << "\nYou: ";
        std::getline(std::cin, userInput);

        // Exit condition
        if (userInput == "X" || userInput == "x") {
            std::cout << "Exiting Soch Loan. Goodbye!\n";
            break;
        }

        // Utterance handling (will print appropriate greeting/response)
        bool matched = utterHandler.generateResponse(userInput);
        (void)matched; // just to silence unused-variable warning

        // If user pressed A/a → start loan-type flow
        if (userInput == "A" || userInput == "a") {
            // Show available loan types
            display.displyLoanTypes(userInput);

            std::string loanType;
            std::cout << "\nEnter Loan Type (H = Home, others not implemented yet, X = back): ";
            std::getline(std::cin, loanType);

            if (loanType == "X" || loanType == "x") {
                continue; // back to main chat loop
            }

            if (loanType == "H" || loanType == "h") {
                // Home loan flow for Increment 1

                // Show all home loans
                loanSelection.selectHome();

                // Show monthly payment summary for all plans
                loanSelection.payPerMonth();

                // Show installment breakdown for all plans
                loanSelection.monthlyInstallment();
            } else {
                std::cout << "For now, only Home loan (H) is supported in Increment 1.\n";
            }
        }
        // Direct H/h (if user types H separately)
        else if (userInput == "H" || userInput == "h") {
            display.selectAreaDisplay(userInput);
            loanSelection.selectHome();
            loanSelection.payPerMonth();
            loanSelection.monthlyInstallment();
        }
        // Everything else is just handled by UtterenceHandler
    }

    return 0;
}
