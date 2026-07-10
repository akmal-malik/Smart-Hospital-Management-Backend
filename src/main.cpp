#include <iostream>
#include <vector>

#include "HospitalService.h"

using namespace std;

int main()
{
    HospitalService hospital;

    cout << "=========================================\n";
    cout << " CITY HOSPITAL MANAGEMENT BACKEND\n";
    cout << "=========================================\n\n";

    // Load Existing Database
    hospital.loadSystem();

    /*
    --------------------------------------------------
    Patient Module
    --------------------------------------------------
    */

    cout << "\n========== PATIENT MODULE ==========\n";

    Patient* patient =
        hospital.patients().searchPatient("P-101");

    if (patient == nullptr)
    {
        hospital.patients().registerPatient(
            "P-101",
            "Akmal Malik",
            "9876543210",
            "Penicillin Allergy"
        );

        patient =
            hospital.patients().searchPatient("P-101");
    }

    if (patient != nullptr)
    {
        cout << "Patient Found : "
             << patient->name
             << endl;
    }

    /*
    --------------------------------------------------
    Blood Bank
    --------------------------------------------------
    */

    cout << "\n========== BLOOD BANK ==========\n";

    if (hospital.bloodBank().searchUnit("B-001") == nullptr)
    {
        hospital.bloodBank().addUnit(
            "B-001",
            "O-",
            14,
            "Fridge-A",
            "Shelf-1",
            5
        );
    }

    if (hospital.bloodBank().searchUnit("B-002") == nullptr)
    {
        hospital.bloodBank().addUnit(
            "B-002",
            "O-",
            2,
            "Fridge-A",
            "Shelf-2",
            1
        );
    }

    BloodUnit blood;

    if (hospital.bloodBank().requestBlood("O-", blood))
    {
        cout << "Allocated Unit : "
             << blood.unitId
             << endl;
    }
    else
    {
        cout << "No blood available.\n";
    }

    /*
    --------------------------------------------------
    Hospital Router
    --------------------------------------------------
    */

    cout << "\n========== ROUTER ==========\n";

    if (hospital.router().getNeighbours(0).empty())
    {
        hospital.router().addCorridor(0,1,30);
        hospital.router().addCorridor(1,2,20);
        hospital.router().addCorridor(2,3,15);
        hospital.router().addCorridor(3,4,25);
    }

    vector<int> route =
        hospital.router().findFastestRoute(0,4);

    cout << "Route : ";

    for (int node : route)
    {
        cout << node << " ";
    }

    cout << endl;

    /*
    --------------------------------------------------
    Certificate
    --------------------------------------------------
    */

    cout << "\n========== CERTIFICATE ==========\n";

    Certificate* cert =
        hospital.certificates().searchCertificate("CERT-001");

    if (cert == nullptr)
    {
        string hash =
            hospital.certificates().generateCertificate(
                "CERT-001",
                "P-101",
                "Akmal Malik",
                "Fit to Work"
            );

        cout << "Certificate Hash : "
             << hash
             << endl;
    }
    else
    {
        cout << "Certificate Already Exists.\n";
        cout << "Certificate Hash : "
             << cert->digitalHash
             << endl;
    }

    /*
    --------------------------------------------------
    Dashboard
    --------------------------------------------------
    */

    hospital.displayDashboard();

    /*
    --------------------------------------------------
    Save Everything
    --------------------------------------------------
    */

    hospital.saveSystem();

    cout << "\nBackend Test Completed Successfully.\n";

    return 0;
}