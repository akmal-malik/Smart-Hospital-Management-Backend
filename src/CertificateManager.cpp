#include "CertificateManager.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/*
|--------------------------------------------------------------------------
| Generate Certificate
|--------------------------------------------------------------------------
*/

string CertificateManager::generateCertificate(
    string certId,
    string patientId,
    string patientName,
    string detail)
{
    string content =
        certId +
        "|" +
        patientId +
        "|" +
        patientName +
        "|" +
        detail;

    string hash = generateSecureHash(content);

    Certificate certificate;

    certificate.certificateId = certId;
    certificate.patientId = patientId;
    certificate.patientName = patientName;
    certificate.details = detail;
    certificate.digitalHash = hash;

    certificates.push_back(certificate);

    return hash;
}

/*
|--------------------------------------------------------------------------
| Search Certificate
|--------------------------------------------------------------------------
*/

Certificate* CertificateManager::searchCertificate(
    string certId)
{
    for (auto& certificate : certificates)
    {
        if (certificate.certificateId == certId)
        {
            return &certificate;
        }
    }

    return nullptr;
}

/*
|--------------------------------------------------------------------------
| Verify Certificate
|--------------------------------------------------------------------------
*/

bool CertificateManager::verifyCertificate(
    string certId,
    string patientName,
    string detail,
    string originalHash)
{
    Certificate* certificate =
        searchCertificate(certId);

    if (certificate == nullptr)
    {
        return false;
    }

    string content =
        certId +
        "|" +
        certificate->patientId +
        "|" +
        patientName +
        "|" +
        detail;

    string currentHash =
        generateSecureHash(content);

    return currentHash == originalHash;
}

/*
|--------------------------------------------------------------------------
| Delete Certificate
|--------------------------------------------------------------------------
*/

bool CertificateManager::deleteCertificate(
    string certId)
{
    for (auto it = certificates.begin();
         it != certificates.end();
         it++)
    {
        if (it->certificateId == certId)
        {
            certificates.erase(it);
            return true;
        }
    }

    return false;
}

/*
|--------------------------------------------------------------------------
| Total Certificates
|--------------------------------------------------------------------------
*/

int CertificateManager::totalCertificates()
{
    return static_cast<int>(certificates.size());
}

/*
|--------------------------------------------------------------------------
| Display Certificates
|--------------------------------------------------------------------------
*/

void CertificateManager::displayCertificates()
{
    cout << "\n========== CERTIFICATES ==========\n";

    if (certificates.empty())
    {
        cout << "No certificates found.\n";
        return;
    }

    for (const auto& certificate : certificates)
    {
        cout << "---------------------------------\n";
        cout << "Certificate ID : "
             << certificate.certificateId
             << endl;

        cout << "Patient ID     : "
             << certificate.patientId
             << endl;

        cout << "Patient Name   : "
             << certificate.patientName
             << endl;

        cout << "Details        : "
             << certificate.details
             << endl;

        cout << "Digital Hash   : "
             << certificate.digitalHash
             << endl;
    }

    cout << "---------------------------------\n";
}

/*
|--------------------------------------------------------------------------
| Save Certificates
|--------------------------------------------------------------------------
*/

void CertificateManager::saveCertificates()
{
    ofstream file("database/certificates.txt");

    if (!file.is_open())
    {
        cout << "[ERROR] Unable to save certificates.\n";
        return;
    }

    for (const auto& certificate : certificates)
    {
        file << certificate.certificateId << ","
             << certificate.patientId << ","
             << certificate.patientName << ","
             << certificate.details << ","
             << certificate.digitalHash
             << "\n";
    }

    file.close();

    cout << "[SUCCESS] Certificates saved.\n";
}

/*
|--------------------------------------------------------------------------
| Load Certificates
|--------------------------------------------------------------------------
*/

void CertificateManager::loadCertificates()
{
    ifstream file("database/certificates.txt");

    if (!file.is_open())
    {
        cout << "[INFO] No certificates found.\n";
        return;
    }

    certificates.clear();

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        Certificate certificate;

        getline(ss,
                certificate.certificateId,
                ',');

        getline(ss,
                certificate.patientId,
                ',');

        getline(ss,
                certificate.patientName,
                ',');

        getline(ss,
                certificate.details,
                ',');

        getline(ss,
                certificate.digitalHash,
                ',');

        certificates.push_back(certificate);
    }

    file.close();

    cout << "[SUCCESS] Certificates loaded.\n";
}