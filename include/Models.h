#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

using namespace std;

/*
|--------------------------------------------------------------------------
| Blood Unit
|--------------------------------------------------------------------------
*/

struct BloodUnit
{
    string unitId;
    string bloodGroup;
    int daysToExpiry;

    string fridgeId;
    string shelfId;
    int slotNumber;
};

/*
|--------------------------------------------------------------------------
| Patient
|--------------------------------------------------------------------------
*/

struct Patient
{
    string patientId;
    string name;
    string phone;
    string criticalAllergies;
};


struct Certificate
{
    string certificateId;

    string patientId;

    string patientName;

    string details;

    string digitalHash;
};

/*
|--------------------------------------------------------------------------
| Hospital Graph Edge
|--------------------------------------------------------------------------
*/

struct Edge
{
    int to;

    int baseWeight;

    int trafficDelay;

    bool isBlocked = false;

    int getTotalWeight() const
    {
        return baseWeight + trafficDelay;
    }
};

#endif