#include "HospitalService.h"

#include <iostream>

using namespace std;

/*
|--------------------------------------------------------------------------
| Constructor
|--------------------------------------------------------------------------
*/

HospitalService::HospitalService()
{
    hospitalRouter.initializeGraph(5);
}

/*
|--------------------------------------------------------------------------
| Get Patient Manager
|--------------------------------------------------------------------------
*/

PatientManager&
HospitalService::patients()
{
    return patientManager;
}

/*
|--------------------------------------------------------------------------
| Get Blood Bank Manager
|--------------------------------------------------------------------------
*/

BloodBankManager&
HospitalService::bloodBank()
{
    return bloodBankManager;
}

/*
|--------------------------------------------------------------------------
| Get Hospital Router
|--------------------------------------------------------------------------
*/

HospitalRouter&
HospitalService::router()
{
    return hospitalRouter;
}

/*
|--------------------------------------------------------------------------
| Get Certificate Manager
|--------------------------------------------------------------------------
*/

CertificateManager&
HospitalService::certificates()
{
    return certificateManager;
}

/*
|--------------------------------------------------------------------------
| Load Entire System
|--------------------------------------------------------------------------
*/

void HospitalService::loadSystem()
{
    patientManager.loadPatients();

    bloodBankManager.loadInventory();

    certificateManager.loadCertificates();

    hospitalRouter.loadMap();

    cout << "[SYSTEM] All modules loaded successfully.\n";
}

/*
|--------------------------------------------------------------------------
| Save Entire System
|--------------------------------------------------------------------------
*/

void HospitalService::saveSystem()
{
    patientManager.savePatients();

    bloodBankManager.saveInventory();

    certificateManager.saveCertificates();

    hospitalRouter.saveMap();

    cout << "[SYSTEM] All modules saved successfully.\n";
}

/*
|--------------------------------------------------------------------------
| Dashboard
|--------------------------------------------------------------------------
*/

void HospitalService::displayDashboard()
{
    cout << "\n";
    cout << "=============================================\n";
    cout << "         HOSPITAL MANAGEMENT DASHBOARD\n";
    cout << "=============================================\n";

    cout << "Total Patients      : "
         << patientManager.totalPatients()
         << endl;

    cout << "Total Blood Units   : "
         << bloodBankManager.getTotalInventory()
         << endl;

    cout << "Total Certificates  : "
         << certificateManager.totalCertificates()
         << endl;

    cout << "=============================================\n";
}