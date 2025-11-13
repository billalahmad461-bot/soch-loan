#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/loan-selection.h"
using namespace std;

Homeloan homeloans[MAX_HOME_LOANS];
int homeloan_count = 0;

void readHomeloans(const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    
    // Skip first line if it’s a header
    if (getline(file, line))
    {
        // Optional: check if line contains "Size" or "Price" to confirm it's a header
        if (line.find("Size") != string::npos) {
            // skipped
        } else {
            // if it’s actual data, parse it
            istringstream iss(line);
            getline(iss, homeloans[homeloan_count].size, '#');
            getline(iss, homeloans[homeloan_count].area, '#');
            getline(iss, homeloans[homeloan_count].installments, '#');
            getline(iss, homeloans[homeloan_count].price, '#');
            getline(iss, homeloans[homeloan_count].downpayment, '#');
            homeloan_count++;
        }
    }

    // Read rest of the file normally
    while (getline(file, line) && homeloan_count < MAX_HOME_LOANS)
    {
        istringstream iss(line);
        getline(iss, homeloans[homeloan_count].size, '#');
        getline(iss, homeloans[homeloan_count].area, '#');
        getline(iss, homeloans[homeloan_count].installments, '#');
        getline(iss, homeloans[homeloan_count].price, '#');
        getline(iss, homeloans[homeloan_count].downpayment, '#');
        homeloan_count++;
    }

    file.close();
}


void displayHomeloans()
{
    cout << "Available Home Loans:\n";
    for (int i = 0; i < homeloan_count; i++)
    {
        cout << "Home Loan " << (i + 1) << ":\n";
        cout << "Size: " << homeloans[i].size << endl;
        cout << "Area: " << homeloans[i].area << endl;
        cout << "Installments: " << homeloans[i].installments << endl;
        cout << "Price: " << homeloans[i].price << endl;
        cout << "Downpayment: " << homeloans[i].downpayment << endl;
        cout << "------------------------\n";
    }
}

// Display loans that match the given area string
void displayHomeloansForArea(const string& area)
{
    bool found = false;
    cout << "Home loans for area: " << area << "\n";
    for (int i = 0; i < homeloan_count; i++)
    {
        if (homeloans[i].area == area)
        {
            found = true;
            cout << "Home Loan " << (i + 1) << ":\n";
            cout << "Size: " << homeloans[i].size << endl;
            cout << "Installments: " << homeloans[i].installments << endl;
            cout << "Price: " << homeloans[i].price << endl;
            cout << "Downpayment: " << homeloans[i].downpayment << endl;
            cout << "------------------------\n";
        }
    }
    if (!found)
        cout << "No home loans found for this area.\n";
}

// Fill 'areas' array with unique area names found in homeloans and return count
int getAvailableAreas(string areas[], int maxAreas)
{
    int areaCount = 0;
    for (int i = 0; i < homeloan_count; i++)
    {
        bool exists = false;
        for (int j = 0; j < areaCount; j++)
        {
            if (areas[j] == homeloans[i].area)
            {
                exists = true;
                break;
            }
        }
        if (!exists && areaCount < maxAreas)
        {
            areas[areaCount++] = homeloans[i].area;
        }
    }
    return areaCount;
}
