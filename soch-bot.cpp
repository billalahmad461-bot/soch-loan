#include <iostream>
#include <string>
#include "include/utterence-handler.h"
#include "include/loan-selection.h"
#include "include/display.h"
#include "include/home-loan.h"

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
    std::string initial = utterHandler.getResponse("*");
    display.greetingResponse(initial);

    enum class State { NORMAL, SELECT_LOAN_TYPE, SELECT_AREA, SELECT_PLAN, CONFIRM_INSTALLMENT };
    State currentState = State::NORMAL;

    std::vector<HomeLoan> current_filtered;
    HomeLoan selected_loan;
    std::string userInput;

    while (true) {
        std::cout << "\nYou: ";
        std::getline(std::cin, userInput);
        std::string originalInput = userInput;

        userInput = utterHandler.trim(userInput);
        userInput = utterHandler.toLower(userInput);

        if (userInput == "x") {
            std::string exitMsg = utterHandler.getResponse("exit");
            std::cout << exitMsg << "\n";
            break;
        }

        if (currentState == State::NORMAL) {
            std::string response = utterHandler.generateResponse(originalInput);
            if (response.empty()) {
                response = utterHandler.getResponse("*");
            }

            // Show banner only on real greetings
            if (userInput == "hi" || userInput == "hello" || userInput == "*") {
                display.showGreetingBanner();
            }

            display.greetingResponse(response);

            // Allow user to jump directly with "h" — no need for "a" first
            if (userInput == "h" || userInput == "home" || userInput == "home loan") {
                currentState = State::SELECT_AREA;
            }
            // Normal flow: "a" → loan type selection
            else if (userInput == "a") {
                currentState = State::SELECT_LOAN_TYPE;
            }
        } else if (currentState == State::SELECT_LOAN_TYPE) {
            if (userInput == "h") {
                std::string response = utterHandler.generateResponse("h");
                display.greetingResponse(response);
                currentState = State::SELECT_AREA;
            } else if (userInput == "c" || userInput == "s" || userInput == "p") {
                std::string response = utterHandler.getResponse("not_implemented");
                display.greetingResponse(response);
                currentState = State::NORMAL;
            } else {
                std::string response = utterHandler.getResponse("invalid_loan_type");
                display.greetingResponse(response);
            }

        } else if (currentState == State::SELECT_AREA) {
            int areaNum = -1;
            try {
                areaNum = std::stoi(userInput);
            } catch (...) {}

            if (areaNum >= 1 && areaNum <= 4) {
                std::string key = "select_area" + std::to_string(areaNum);
                std::string response = utterHandler.getResponse(key);
                display.greetingResponse(response);

                std::string area = "area " + std::to_string(areaNum);
                current_filtered = loanSelection.homeLoansInArea(area);

                if (current_filtered.empty()) {
                    std::string noLoans = utterHandler.getResponse("no_loans");
                    display.undefinedInputResponse(noLoans);
                    currentState = State::NORMAL;
                } else {
                    std::string prompt = utterHandler.getResponse("prompt_select_plan");
                    display.homeLoanDisplay(current_filtered, 0, current_filtered.size() - 1, prompt);
                    currentState = State::SELECT_PLAN;
                }

            } else {
                std::string invalid = utterHandler.getResponse("invalid_area");
                display.greetingResponse(invalid);
            }

        } else if (currentState == State::SELECT_PLAN) {
            int id = -1;
            try {
                id = std::stoi(userInput);
            } catch (...) {}

            if (id >= 1 && id <= static_cast<int>(current_filtered.size())) {
                std::string key = "selected_plan";
                std::string response = utterHandler.getResponse(key);
                response = utterHandler.replacePlaceholder(response, "{id}", userInput);
                display.greetingResponse(response);

                selected_loan = current_filtered[id - 1];
                std::string monthlyInfo = loanSelection.calculateMonthlyPayment(selected_loan);
                display.payPerMonthDisplay(monthlyInfo);

                std::string promptInst = utterHandler.getResponse("prompt_installment");
                display.promptForInput(promptInst);

                currentState = State::CONFIRM_INSTALLMENT;

            } else {
                std::string invalid = utterHandler.getResponse("invalid_plan");
                display.greetingResponse(invalid);
            }

        } else if (currentState == State::CONFIRM_INSTALLMENT) {
            if (userInput == "yes" || userInput == "y") {
                std::string response = utterHandler.getResponse("selected_installment");
                display.greetingResponse(response);

                std::vector<std::string> insts, rems;
                std::string total, down;
                loanSelection.calculateInstallmentBreakdown(selected_loan, insts, rems, total, down);
                display.monthlyInstallmentDisplay(total, down, insts, rems);

                currentState = State::NORMAL;

            } else if (userInput == "no" || userInput == "n") {
                std::string response = utterHandler.getResponse("no_installment");
                display.greetingResponse(response);
                currentState = State::NORMAL;

            } else {
                std::string invalid = utterHandler.getResponse("invalid_yes_no");
                display.greetingResponse(invalid);
            }
        }
    }

    return 0;
}
