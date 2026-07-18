#include "PatientManager.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Utils.h"

using namespace std;

/*
|--------------------------------------------------------------------------
| Register Patient
|--------------------------------------------------------------------------
*/

void PatientManager::registerPatient(
    string id,
    string name,
    string phone,
    string allergies)
{
    // Validate Patient ID
if (isEmpty(id))
{
    cout << "[ERROR] Patient ID cannot be empty.\n";
    return;
}

if (patientExists(id))
{
    cout << "[ERROR] Patient ID already exists.\n";
    return;
}

// Validate Name
if (isEmpty(name))
{
    cout << "[ERROR] Patient name cannot be empty.\n";
    return;
}

// Validate Phone Number
if (!isValidPhone(phone))
{
    cout << "[ERROR] Invalid phone number.\n";
    return;
}

// Validate Allergies
if (isEmpty(allergies))
{
    allergies = "None";
}
    cout << "\n[PROCESS] Registering Patient...\n";

    string newName = toLower(name);

    for (const auto& patient : database)
    {
        string existingName = toLower(patient.name);

        int distance =
            getLevenshteinDistance(
                newName,
                existingName
            );

        if (distance <= 3 ||
            patient.phone == phone)
        {
            cout << "\n[WARNING] Duplicate Patient Found\n";

            cout << "Existing ID : "
                 << patient.patientId
                 << endl;

            cout << "Existing Name : "
                 << patient.name
                 << endl;

            cout << "Registration Blocked.\n";

            return;
        }
    }

    Patient p;

    p.patientId = id;
    p.name = name;
    p.phone = phone;
    p.criticalAllergies = allergies;

    database.push_back(p);

    cout << "[SUCCESS] Patient Registered.\n";
}

/*
|--------------------------------------------------------------------------
| Search Patient By ID
|--------------------------------------------------------------------------
*/

Patient* PatientManager::searchPatient(
    string patientId)
{
    if (isEmpty(patientId))
    {
        return nullptr;
    }

    for (auto& patient : database)
    {
        if (patient.patientId == patientId)
        {
            return &patient;
        }
    }

    return nullptr;
}

/*
|--------------------------------------------------------------------------
| Search Patient By Phone
|--------------------------------------------------------------------------
*/

Patient* PatientManager::searchByPhone(
    string phone)
{
    if (!isValidPhone(phone))
    {
        return nullptr;
    }

    for (auto& patient : database)
    {
        if (patient.phone == phone)
        {
            return &patient;
        }
    }

    return nullptr;
}

/*
|--------------------------------------------------------------------------
| Search Patient By Name
|--------------------------------------------------------------------------
*/

vector<Patient> PatientManager::searchByName(
    string name)
{
    vector<Patient> result;

    if (isEmpty(name))
    {
        return result;
    }

    string searchName = toLower(name);

    for (const auto& patient : database)
    {
        string currentName = toLower(patient.name);

        int distance =
            getLevenshteinDistance(
                searchName,
                currentName
            );

        if (distance <= 3)
        {
            result.push_back(patient);
        }
    }

    return result;
}

/*
|--------------------------------------------------------------------------
| Update Patient
|--------------------------------------------------------------------------
*/

bool PatientManager::updatePatient(
    string patientId,
    string phone,
    string allergies)
{
    if (isEmpty(patientId))
    {
        cout << "[ERROR] Patient ID cannot be empty.\n";
        return false;
    }

    if (!isValidPhone(phone))
    {
        cout << "[ERROR] Invalid phone number.\n";
        return false;
    }

    if (isEmpty(allergies))
    {
        allergies = "None";
    }

    Patient* patient = searchPatient(patientId);

    if (patient == nullptr)
    {
        cout << "[ERROR] Patient not found.\n";
        return false;
    }

    patient->phone = phone;
    patient->criticalAllergies = allergies;

    cout << "[SUCCESS] Patient updated.\n";

    return true;
}

/*
|--------------------------------------------------------------------------
| Delete Patient
|--------------------------------------------------------------------------
*/

bool PatientManager::deletePatient(
    string patientId)
{
    if (isEmpty(patientId))
    {
        cout << "[ERROR] Patient ID cannot be empty.\n";
        return false;
    }

    for (auto it = database.begin();
         it != database.end();
         it++)
    {
        if (it->patientId == patientId)
        {
            database.erase(it);

            cout << "[SUCCESS] Patient deleted.\n";

            return true;
        }
    }

    cout << "[ERROR] Patient not found.\n";

    return false;
}

/*
|--------------------------------------------------------------------------
| Patient Exists
|--------------------------------------------------------------------------
*/

bool PatientManager::patientExists(
    string patientId)
{
    if (isEmpty(patientId))
    {
        return false;
    }

    return searchPatient(patientId) != nullptr;
}

/*
|--------------------------------------------------------------------------
| Total Patients
|--------------------------------------------------------------------------
*/

int PatientManager::totalPatients()
{
    return static_cast<int>(database.size());
}

/*
|--------------------------------------------------------------------------
| Display Patients
|--------------------------------------------------------------------------
*/

void PatientManager::displayPatients()
{
    cout << "\n========== PATIENT DATABASE ==========\n";

    if (database.empty())
    {
        cout << "No patients found.\n";
        return;
    }

    for (const auto& patient : database)
    {
        cout << "---------------------------------\n";
        cout << "ID         : "
             << patient.patientId
             << endl;

        cout << "Name       : "
             << patient.name
             << endl;

        cout << "Phone      : "
             << patient.phone
             << endl;

        cout << "Allergies  : "
             << patient.criticalAllergies
             << endl;
    }

    cout << "---------------------------------\n";
}

/*
|--------------------------------------------------------------------------
| Save Patients
|--------------------------------------------------------------------------
*/

void PatientManager::savePatients()
{
    ofstream file("database/patients.txt");

    if (!file.is_open())
    {
        cout << "[ERROR] Unable to save patients.\n";
        return;
    }

    for (const auto& patient : database)
    {
        file << patient.patientId << ","
             << patient.name << ","
             << patient.phone << ","
             << patient.criticalAllergies
             << "\n";
    }

    file.close();

    cout << "[SUCCESS] Patient database saved.\n";
}

/*
|--------------------------------------------------------------------------
| Load Patients
|--------------------------------------------------------------------------
*/

void PatientManager::loadPatients()
{
    ifstream file("database/patients.txt");

    if (!file.is_open())
    {
        cout << "[INFO] No patient database found.\n";
        return;
    }

    database.clear();

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        Patient patient;

        getline(ss,
                patient.patientId,
                ',');

        getline(ss,
                patient.name,
                ',');

        getline(ss,
                patient.phone,
                ',');

        getline(ss,
                patient.criticalAllergies,
                ',');

        if (patient.patientId.empty() ||
           patient.name.empty())
    {
    continue;
  }

        database.push_back(patient);
    }

    file.close();

    cout << "[SUCCESS] Patient database loaded.\n";
}