#include <iostream>
#include <vector>
#include <limits>
#include <string>

#include "HospitalService.h"

using namespace std;

/*
|--------------------------------------------------------------------------
| Clear Invalid Input
|--------------------------------------------------------------------------
*/

void clearInput()
{
    cin.clear();

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );
}

/*
|--------------------------------------------------------------------------
| Patient Management Menu
|--------------------------------------------------------------------------
*/

void patientMenu(HospitalService& hospital)
{
    int choice = -1;

    do
    {
        cout << "\n=========================================\n";
        cout << "          PATIENT MANAGEMENT\n";
        cout << "=========================================\n";
        cout << "1. Register Patient\n";
        cout << "2. Search Patient by ID\n";
        cout << "3. Search Patient by Phone\n";
        cout << "4. Search Patient by Name\n";
        cout << "5. Update Patient\n";
        cout << "6. Delete Patient\n";
        cout << "7. Display All Patients\n";
        cout << "0. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            clearInput();
            cout << "[ERROR] Please enter a valid number.\n";
            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
            {
                string id;
                string name;
                string phone;
                string allergies;

                cout << "\nEnter Patient ID: ";
                getline(cin, id);

                cout << "Enter Patient Name: ";
                getline(cin, name);

                cout << "Enter Phone Number: ";
                getline(cin, phone);

                cout << "Enter Allergies (leave empty for None): ";
                getline(cin, allergies);

                hospital.patients().registerPatient(
                    id,
                    name,
                    phone,
                    allergies
                );

                break;
            }

            case 2:
            {
                string id;

                cout << "\nEnter Patient ID: ";
                getline(cin, id);

                Patient* patient =
                    hospital.patients().searchPatient(id);

                if (patient != nullptr)
                {
                    cout << "\n========== PATIENT FOUND ==========\n";
                    cout << "ID        : " << patient->patientId << endl;
                    cout << "Name      : " << patient->name << endl;
                    cout << "Phone     : " << patient->phone << endl;
                    cout << "Allergies : "
                         << patient->criticalAllergies
                         << endl;
                }
                else
                {
                    cout << "[ERROR] Patient not found.\n";
                }

                break;
            }

            case 3:
            {
                string phone;

                cout << "\nEnter Phone Number: ";
                getline(cin, phone);

                Patient* patient =
                    hospital.patients().searchByPhone(phone);

                if (patient != nullptr)
                {
                    cout << "\n========== PATIENT FOUND ==========\n";
                    cout << "ID        : " << patient->patientId << endl;
                    cout << "Name      : " << patient->name << endl;
                    cout << "Phone     : " << patient->phone << endl;
                    cout << "Allergies : "
                         << patient->criticalAllergies
                         << endl;
                }
                else
                {
                    cout << "[ERROR] Patient not found.\n";
                }

                break;
            }

            case 4:
            {
                string name;

                cout << "\nEnter Patient Name: ";
                getline(cin, name);

                vector<Patient> results =
                    hospital.patients().searchByName(name);

                if (results.empty())
                {
                    cout << "[ERROR] No matching patients found.\n";
                }
                else
                {
                    cout << "\n========== SEARCH RESULTS ==========\n";

                    for (const auto& patient : results)
                    {
                        cout << "---------------------------------\n";
                        cout << "ID        : "
                             << patient.patientId
                             << endl;

                        cout << "Name      : "
                             << patient.name
                             << endl;

                        cout << "Phone     : "
                             << patient.phone
                             << endl;

                        cout << "Allergies : "
                             << patient.criticalAllergies
                             << endl;
                    }
                }

                break;
            }

            case 5:
            {
                string id;
                string phone;
                string allergies;

                cout << "\nEnter Patient ID: ";
                getline(cin, id);

                cout << "Enter New Phone Number: ";
                getline(cin, phone);

                cout << "Enter New Allergies: ";
                getline(cin, allergies);

                hospital.patients().updatePatient(
                    id,
                    phone,
                    allergies
                );

                break;
            }

            case 6:
            {
                string id;

                cout << "\nEnter Patient ID: ";
                getline(cin, id);

                hospital.patients().deletePatient(id);

                break;
            }

            case 7:
            {
                hospital.patients().displayPatients();
                break;
            }

            case 0:
            {
                cout << "Returning to Main Menu...\n";
                break;
            }

            default:
            {
                cout << "[ERROR] Invalid choice.\n";
            }
        }

    }
    while (choice != 0);
}

/*
|--------------------------------------------------------------------------
| Blood Bank Management Menu
|--------------------------------------------------------------------------
*/

void bloodBankMenu(HospitalService& hospital)
{
    int choice = -1;

    do
    {
        cout << "\n=========================================\n";
        cout << "          BLOOD BANK MANAGEMENT\n";
        cout << "=========================================\n";
        cout << "1. Add Blood Unit\n";
        cout << "2. Request Blood\n";
        cout << "3. Search Blood Unit\n";
        cout << "4. Display Inventory Summary\n";
        cout << "5. Display Detailed Inventory\n";
        cout << "6. Update Blood Unit Expiry\n";
        cout << "7. Remove Blood Unit\n";
        cout << "8. Remove Expired Units\n";
        cout << "9. Check Low Stock\n";
        cout << "10. Get Total Inventory\n";
        cout << "0. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            clearInput();
            cout << "[ERROR] Please enter a valid number.\n";
            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
            {
                string id;
                string group;
                string fridge;
                string shelf;

                int daysToExpiry;
                int slot;

                cout << "\nEnter Blood Unit ID: ";
                getline(cin, id);

                cout << "Enter Blood Group: ";
                getline(cin, group);

                cout << "Enter Days to Expiry: ";
                cin >> daysToExpiry;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid expiry value.\n";
                    break;
                }

                clearInput();

                cout << "Enter Fridge ID: ";
                getline(cin, fridge);

                cout << "Enter Shelf ID: ";
                getline(cin, shelf);

                cout << "Enter Slot Number: ";
                cin >> slot;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid slot number.\n";
                    break;
                }

                clearInput();

                hospital.bloodBank().addUnit(
                    id,
                    group,
                    daysToExpiry,
                    fridge,
                    shelf,
                    slot
                );

                break;
            }

            case 2:
            {
                string group;
                BloodUnit allocatedUnit;

                cout << "\nEnter Blood Group: ";
                getline(cin, group);

                if (
                    hospital.bloodBank().requestBlood(
                        group,
                        allocatedUnit
                    )
                )
                {
                    cout << "\n========== BLOOD ALLOCATED ==========\n";
                    cout << "Unit ID     : "
                         << allocatedUnit.unitId
                         << endl;

                    cout << "Blood Group : "
                         << allocatedUnit.bloodGroup
                         << endl;

                    cout << "Expiry      : "
                         << allocatedUnit.daysToExpiry
                         << " days"
                         << endl;

                    cout << "Fridge      : "
                         << allocatedUnit.fridgeId
                         << endl;

                    cout << "Shelf       : "
                         << allocatedUnit.shelfId
                         << endl;

                    cout << "Slot        : "
                         << allocatedUnit.slotNumber
                         << endl;
                }
                else
                {
                    cout << "[ERROR] No usable blood available.\n";
                }

                break;
            }

            case 3:
            {
                string id;

                cout << "\nEnter Blood Unit ID: ";
                getline(cin, id);

                BloodUnit* unit =
                    hospital.bloodBank().searchUnit(id);

                if (unit != nullptr)
                {
                    cout << "\n========== BLOOD UNIT FOUND ==========\n";
                    cout << "Unit ID     : " << unit->unitId << endl;
                    cout << "Blood Group : " << unit->bloodGroup << endl;
                    cout << "Expiry      : "
                         << unit->daysToExpiry
                         << " days"
                         << endl;

                    cout << "Fridge      : " << unit->fridgeId << endl;
                    cout << "Shelf       : " << unit->shelfId << endl;
                    cout << "Slot        : " << unit->slotNumber << endl;
                }
                else
                {
                    cout << "[ERROR] Blood unit not found.\n";
                }

                break;
            }

            case 4:
            {
                hospital.bloodBank().displayInventory();
                break;
            }

            case 5:
            {
                hospital.bloodBank().displayDetailedInventory();
                break;
            }

            case 6:
            {
                string id;
                int newDays;

                cout << "\nEnter Blood Unit ID: ";
                getline(cin, id);

                cout << "Enter New Days to Expiry: ";
                cin >> newDays;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid expiry value.\n";
                    break;
                }

                clearInput();

                if (
                    hospital.bloodBank().updateExpiry(
                        id,
                        newDays
                    )
                )
                {
                    cout << "[SUCCESS] Blood unit expiry updated.\n";
                }
                else
                {
                    cout << "[ERROR] Blood unit not found.\n";
                }

                break;
            }

            case 7:
            {
                string id;

                cout << "\nEnter Blood Unit ID: ";
                getline(cin, id);

                if (hospital.bloodBank().removeUnit(id))
                {
                    cout << "[SUCCESS] Blood unit removed.\n";
                }
                else
                {
                    cout << "[ERROR] Blood unit not found.\n";
                }

                break;
            }

            case 8:
            {
                hospital.bloodBank().removeExpiredUnits();

                cout << "[SUCCESS] Expired blood units removed.\n";

                break;
            }

            case 9:
            {
                string group;
                int threshold;

                cout << "\nEnter Blood Group: ";
                getline(cin, group);

                cout << "Enter Low Stock Threshold: ";
                cin >> threshold;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid threshold.\n";
                    break;
                }

                clearInput();

                int units =
                    hospital.bloodBank().getTotalUnits(group);

                cout << "Available Units: "
                     << units
                     << endl;

                if (
                    hospital.bloodBank().isLowStock(
                        group,
                        threshold
                    )
                )
                {
                    cout << "[WARNING] Blood group is LOW IN STOCK.\n";
                }
                else
                {
                    cout << "[INFO] Blood stock level is sufficient.\n";
                }

                break;
            }

            case 10:
            {
                cout << "\nTotal Blood Units: "
                     << hospital.bloodBank().getTotalInventory()
                     << endl;

                break;
            }

            case 0:
            {
                cout << "Returning to Main Menu...\n";
                break;
            }

            default:
            {
                cout << "[ERROR] Invalid choice.\n";
            }
        }

    }
    while (choice != 0);
}

/*
|--------------------------------------------------------------------------
| Hospital Navigation Menu
|--------------------------------------------------------------------------
*/

void navigationMenu(HospitalService& hospital)
{
    int choice = -1;

    do
    {
        cout << "\n=========================================\n";
        cout << "          HOSPITAL NAVIGATION\n";
        cout << "=========================================\n";
        cout << "1. Add Corridor\n";
        cout << "2. Remove Corridor\n";
        cout << "3. Block Corridor\n";
        cout << "4. Unblock Corridor\n";
        cout << "5. Find Fastest Route\n";
        cout << "6. Get Route Time\n";
        cout << "7. Update Traffic Delay\n";
        cout << "8. Reset All Traffic\n";
        cout << "9. Display Hospital Map\n";
        cout << "10. Get Neighbours\n";
        cout << "0. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            clearInput();
            cout << "[ERROR] Please enter a valid number.\n";
            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
            {
                int from;
                int to;
                int baseTime;

                cout << "\nEnter Starting Node: ";
                cin >> from;

                cout << "Enter Destination Node: ";
                cin >> to;

                cout << "Enter Base Travel Time: ";
                cin >> baseTime;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid input.\n";
                    break;
                }

                clearInput();

                hospital.router().addCorridor(
                    from,
                    to,
                    baseTime
                );

                

                break;
            }

            case 2:
            {
                int from;
                int to;

                cout << "\nEnter Starting Node: ";
                cin >> from;

                cout << "Enter Destination Node: ";
                cin >> to;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid input.\n";
                    break;
                }

                clearInput();

                if (hospital.router().removeCorridor(from, to))
                {
                    cout << "[SUCCESS] Corridor removed.\n";
                }
                else
                {
                    cout << "[ERROR] Corridor not found.\n";
                }

                break;
            }

            case 3:
            {
                int from;
                int to;

                cout << "\nEnter Starting Node: ";
                cin >> from;

                cout << "Enter Destination Node: ";
                cin >> to;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid input.\n";
                    break;
                }

                clearInput();

                if (hospital.router().blockCorridor(from, to))
                {
                    cout << "[SUCCESS] Corridor blocked.\n";
                }
                else
                {
                    cout << "[ERROR] Corridor not found.\n";
                }

                break;
            }

            case 4:
            {
                int from;
                int to;

                cout << "\nEnter Starting Node: ";
                cin >> from;

                cout << "Enter Destination Node: ";
                cin >> to;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid input.\n";
                    break;
                }

                clearInput();

                if (hospital.router().unblockCorridor(from, to))
                {
                    cout << "[SUCCESS] Corridor unblocked.\n";
                }
                else
                {
                    cout << "[ERROR] Corridor not found.\n";
                }

                break;
            }

            case 5:
            {
                int startNode;
                int endNode;

                cout << "\nEnter Starting Node: ";
                cin >> startNode;

                cout << "Enter Destination Node: ";
                cin >> endNode;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid node.\n";
                    break;
                }

                clearInput();

                vector<int> route =
                    hospital.router().findFastestRoute(
                        startNode,
                        endNode
                    );

                if (route.empty())
                {
                    cout << "[ERROR] No route found.\n";
                }
                else
                {
                    cout << "\nFastest Route: ";

                    for (size_t i = 0;
                         i < route.size();
                         i++)
                    {
                        cout << route[i];

                        if (i < route.size() - 1)
                        {
                            cout << " -> ";
                        }
                    }

                    cout << endl;
                }

                break;
            }

            case 6:
            {
                int startNode;
                int endNode;

                cout << "\nEnter Starting Node: ";
                cin >> startNode;

                cout << "Enter Destination Node: ";
                cin >> endNode;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid node.\n";
                    break;
                }

                clearInput();

                int time =
                    hospital.router().getRouteTime(
                        startNode,
                        endNode
                    );

                if (time == numeric_limits<int>::max())
                {
                    cout << "[ERROR] No route found.\n";
                }
                else
                {
                    cout << "Total Route Time: "
                         << time
                         << " seconds"
                         << endl;
                }

                break;
            }

            case 7:
            {
                int from;
                int to;
                int delay;

                cout << "\nEnter Starting Node: ";
                cin >> from;

                cout << "Enter Destination Node: ";
                cin >> to;

                cout << "Enter Traffic Delay: ";
                cin >> delay;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid input.\n";
                    break;
                }

                clearInput();

                hospital.router().updateTrafficFromAI(
                    from,
                    to,
                    delay
                );

                cout << "[SUCCESS] Traffic delay updated.\n";

                break;
            }

            case 8:
            {
                hospital.router().resetTraffic();

                cout << "[SUCCESS] All traffic delays reset.\n";

                break;
            }

            case 9:
            {
                hospital.router().displayMap();
                break;
            }

            case 10:
            {
                int node;

                cout << "\nEnter Node: ";
                cin >> node;

                if (cin.fail())
                {
                    clearInput();
                    cout << "[ERROR] Invalid node.\n";
                    break;
                }

                clearInput();

                vector<Edge> neighbours =
                    hospital.router().getNeighbours(node);

                if (neighbours.empty())
                {
                    cout << "No neighbouring locations found.\n";
                }
                else
                {
                    cout << "\nNeighbours of Location "
                         << node
                         << ":\n";

                    for (const auto& edge : neighbours)
                    {
                        cout << "-> "
                             << edge.to
                             << " | Time: "
                             << edge.getTotalWeight()
                             << " seconds";

                        if (edge.isBlocked)
                        {
                            cout << " | BLOCKED";
                        }

                        cout << endl;
                    }
                }

                break;
            }

            case 0:
            {
                cout << "Returning to Main Menu...\n";
                break;
            }

            default:
            {
                cout << "[ERROR] Invalid choice.\n";
            }
        }

    }
    while (choice != 0);
}

/*
|--------------------------------------------------------------------------
| Certificate Management Menu
|--------------------------------------------------------------------------
*/

void certificateMenu(HospitalService& hospital)
{
    int choice = -1;

    do
    {
        cout << "\n=========================================\n";
        cout << "        CERTIFICATE MANAGEMENT\n";
        cout << "=========================================\n";
        cout << "1. Generate Certificate\n";
        cout << "2. Verify Certificate\n";
        cout << "3. Search Certificate\n";
        cout << "4. Delete Certificate\n";
        cout << "5. Display All Certificates\n";
        cout << "6. Total Certificates\n";
        cout << "0. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            clearInput();
            cout << "[ERROR] Please enter a valid number.\n";
            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
            {
                string certId;
                string patientId;
                string patientName;
                string detail;

                cout << "\nEnter Certificate ID: ";
                getline(cin, certId);

                if (
                    hospital.certificates()
                    .searchCertificate(certId) != nullptr
                )
                {
                    cout << "[WARNING] Certificate already exists.\n";
                    break;
                }

                cout << "Enter Patient ID: ";
                getline(cin, patientId);

                Patient* patient =
                    hospital.patients().searchPatient(patientId);

                if (patient == nullptr)
                {
                    cout << "[ERROR] Patient does not exist.\n";
                    break;
                }

                patientName = patient->name;

                cout << "Patient Name: "
                     << patientName
                     << endl;

                cout << "Enter Certificate Details: ";
                getline(cin, detail);

                string hash =
                    hospital.certificates()
                    .generateCertificate(
                        certId,
                        patientId,
                        patientName,
                        detail
                    );

                cout << "\n[SUCCESS] Certificate generated.\n";
                cout << "Digital Hash: "
                     << hash
                     << endl;

                break;
            }

            case 2:
{
    string certId;
    string patientName;
    string detail;

    cout << "\nEnter Certificate ID: ";
    getline(cin, certId);

    Certificate* certificate =
        hospital.certificates()
        .searchCertificate(certId);

    if (certificate == nullptr)
    {
        cout << "[ERROR] Certificate not found.\n";
        break;
    }

    cout << "Enter Patient Name: ";
    getline(cin, patientName);

    cout << "Enter Certificate Details: ";
    getline(cin, detail);

    bool valid =
        hospital.certificates()
        .verifyCertificate(
            certId,
            patientName,
            detail
        );

    if (valid)
    {
        cout << "[SUCCESS] Certificate is VALID.\n";
    }
    else
    {
        cout << "[WARNING] Certificate verification FAILED.\n";
    }

    break;
}
            case 3:
            {
                string certId;

                cout << "\nEnter Certificate ID: ";
                getline(cin, certId);

                Certificate* certificate =
                    hospital.certificates()
                    .searchCertificate(certId);

                if (certificate != nullptr)
                {
                    cout << "\n========== CERTIFICATE FOUND ==========\n";

                    cout << "Certificate ID : "
                         << certificate->certificateId
                         << endl;

                    cout << "Patient ID     : "
                         << certificate->patientId
                         << endl;

                    cout << "Patient Name   : "
                         << certificate->patientName
                         << endl;

                    cout << "Details        : "
                         << certificate->details
                         << endl;

                    cout << "Digital Hash   : "
                         << certificate->digitalHash
                         << endl;
                }
                else
                {
                    cout << "[ERROR] Certificate not found.\n";
                }

                break;
            }

            case 4:
            {
                string certId;

                cout << "\nEnter Certificate ID: ";
                getline(cin, certId);

                if (
                    hospital.certificates()
                    .deleteCertificate(certId)
                )
                {
                    cout << "[SUCCESS] Certificate deleted.\n";
                }
                else
                {
                    cout << "[ERROR] Certificate not found.\n";
                }

                break;
            }

            case 5:
            {
                hospital.certificates().displayCertificates();
                break;
            }

            case 6:
            {
                cout << "\nTotal Certificates: "
                     << hospital.certificates()
                            .totalCertificates()
                     << endl;

                break;
            }

            case 0:
            {
                cout << "Returning to Main Menu...\n";
                break;
            }

            default:
            {
                cout << "[ERROR] Invalid choice.\n";
            }
        }

    }
    while (choice != 0);
}

/*
|--------------------------------------------------------------------------
| Main Application
|--------------------------------------------------------------------------
*/

int main()
{
    HospitalService hospital;

    cout << "\n";
    cout << "=============================================\n";
    cout << "      SMART HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "=============================================\n";
    cout << "        Initializing System...\n";
    cout << "=============================================\n\n";

    /*
    |--------------------------------------------------------------------------
    | Load Existing Data
    |--------------------------------------------------------------------------
    */

    hospital.loadSystem();

    int choice = -1;

    do
    {
        cout << "\n";
        cout << "=============================================\n";
        cout << "      SMART HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "=============================================\n";
        cout << "1. Patient Management\n";
        cout << "2. Blood Bank Management\n";
        cout << "3. Hospital Navigation\n";
        cout << "4. Certificate Management\n";
        cout << "5. View Dashboard\n";
        cout << "6. Save System\n";
        cout << "0. Exit\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            clearInput();

            cout << "[ERROR] Please enter a valid number.\n";

            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
            {
                patientMenu(hospital);
                break;
            }

            case 2:
            {
                bloodBankMenu(hospital);
                break;
            }

            case 3:
            {
                navigationMenu(hospital);
                break;
            }

            case 4:
            {
                certificateMenu(hospital);
                break;
            }

            case 5:
            {
                hospital.displayDashboard();
                break;
            }

            case 6:
            {
                hospital.saveSystem();
                break;
            }

            case 0:
            {
                cout << "\nSaving system before exit...\n";

                hospital.saveSystem();

                cout << "\n=============================================\n";
                cout << "       SYSTEM CLOSED SUCCESSFULLY\n";
                cout << "=============================================\n";

                break;
            }

            default:
            {
                cout << "[ERROR] Invalid choice.\n";
            }
        }

    }
    while (choice != 0);

    return 0;
}