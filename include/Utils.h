#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

/*
|--------------------------------------------------------------------------
| String Utilities
|--------------------------------------------------------------------------
*/

// Convert string to lowercase
string toLower(string text);

/*
|--------------------------------------------------------------------------
| Duplicate Detection
|--------------------------------------------------------------------------
*/

// Calculate Levenshtein Distance
int getLevenshteinDistance(
    const string& s1,
    const string& s2
);

/*
|--------------------------------------------------------------------------
| Certificate Security
|--------------------------------------------------------------------------
*/

// Generate Digital Hash
string generateSecureHash(
    const string& data
);


/*
|--------------------------------------------------------------------------
| Validation
|--------------------------------------------------------------------------
*/

bool isValidBloodGroup(
    string group
);

bool isValidPhone(
    string phone
);

bool isEmpty(
    string text
);

bool isPositive(
    int number
);

#endif