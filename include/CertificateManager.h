#ifndef CERTIFICATE_MANAGER_H
#define CERTIFICATE_MANAGER_H

#include <vector>
#include <string>

#include "Models.h"

using namespace std;

class CertificateManager
{
private:

    vector<Certificate> certificates;

public:

    /*
    |--------------------------------------------------------------------------
    | Certificate Management
    |--------------------------------------------------------------------------
    */

    string generateCertificate(
        string certId,
        string patientId,
        string patientName,
        string detail
    );

   bool verifyCertificate(
    string certId,
    string patientName,
    string detail
);

    Certificate* searchCertificate(
        string certId
    );

    bool deleteCertificate(
        string certId
    );

    /*
    |--------------------------------------------------------------------------
    | Statistics
    |--------------------------------------------------------------------------
    */

    int totalCertificates();

    /*
    |--------------------------------------------------------------------------
    | Display
    |--------------------------------------------------------------------------
    */

    void displayCertificates();

    /*
    |--------------------------------------------------------------------------
    | Storage
    |--------------------------------------------------------------------------
    */

    void saveCertificates();

    void loadCertificates();
};

#endif