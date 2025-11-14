# Soch Loan
A CLI-based chat bot to provide the loan.

## Descroption
It reads predefined user inputs from file to intereact with users to give the feel of chat bot and guide the users applying for differect types of loans. 

## Features
- Reads user inputs and Soch Loan responses from 'utterences.txt'.
- Provides general response for unknown inputs using a '*' fallback.
- Supports Home Loan moudle with area, size, price, installments, and down payment options.
- File-driven design. No need to modify the code to add new utterneces or loan data.
- Eisily extendible to handle car, scooter or personal loans in future phases.

## File Structure
```
soch-loan/
|
├ data/
|   ├utterence.txt
|   └home.txt
|
├ include/
|   ├utterence-handler.h
|   └loan-selection.h
|
├ src/
|   ├utterence-handler.cpp
|   └loan-selection.cpp
|
└ main.cpp
```

## How to Run
1. Open the terminal in project folder.
2. Compile using:
     g++ src/*.cpp main.cpp -I include -o soch-loan
3. Run using:
    .\soch-loan.exe

## File Description
- **utterences.txt** - Contains predefined user inputs and chatbot responses.
- **home.txt** - Contains home-loan details (area, size, price, etc.).
- **utterence-handler.h/cpp** - Module to read and match utterences.
- **loan-selection.h/cpp** - Module to read and display loan data.
- **main.cpp** - Controls the chatbot flow.

## Naming Conventions

This project follows consistent naming conventions to ensure clarity, readability, and maintainability across all source files.

| **Type** | **Convention** | **Example** |
|-----------|----------------|--------------|
| File | lowercase-hyphen | user-manager.cpp |
| Class / Struct | PascalCase | EmployeeManager |
| Function | camelCase | calculateSalary |
| Variable | snake_case | employee_count |
| Constant | UPPERCASE_WITH_UNDERSCORES | MAX_USERS |
| Global | UPPERCASE_WITH_UNDERSCORES | GLOBAL_TOTAL_USERS |
