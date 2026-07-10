#ifndef HOSPITAL_SERVICE_H
#define HOSPITAL_SERVICE_H

#include "PatientManager.h"
#include "BloodBankManager.h"
#include "HospitalRouter.h"
#include "CertificateManager.h"

class HospitalService
{
private:

    PatientManager patientManager;

    BloodBankManager bloodBankManager;

    HospitalRouter hospitalRouter;

    CertificateManager certificateManager;

public:

    HospitalService();

    /*
    |--------------------------------------------------------------------------
    | Getters
    |--------------------------------------------------------------------------
    */

    PatientManager& patients();

    BloodBankManager& bloodBank();

    HospitalRouter& router();

    CertificateManager& certificates();

    /*
    |--------------------------------------------------------------------------
    | System
    |--------------------------------------------------------------------------
    */

    void loadSystem();

    void saveSystem();

    void displayDashboard();
};

#endif