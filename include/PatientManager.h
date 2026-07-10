#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include <vector>
#include <string>

#include "Models.h"

using namespace std;

class PatientManager
{
private:
    vector<Patient> database;

public:

    /*
    |--------------------------------------------------------------------------
    | Patient Management
    |--------------------------------------------------------------------------
    */

    void registerPatient(
        string id,
        string name,
        string phone,
        string allergies
    );

    Patient* searchPatient(
        string patientId
    );

    Patient* searchByPhone(
        string phone
    );

    vector<Patient> searchByName(
        string name
    );

    bool updatePatient(
        string patientId,
        string phone,
        string allergies
    );

    bool deletePatient(
        string patientId
    );

    /*
    |--------------------------------------------------------------------------
    | Statistics
    |--------------------------------------------------------------------------
    */

    bool patientExists(
        string patientId
    );

    int totalPatients();

    /*
    |--------------------------------------------------------------------------
    | Display
    |--------------------------------------------------------------------------
    */

    void displayPatients();

    /*
    |--------------------------------------------------------------------------
    | Storage
    |--------------------------------------------------------------------------
    */

    void loadPatients();

    void savePatients();
};

#endif