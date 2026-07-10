#include "Utils.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <functional>
#include <vector>

using namespace std;

/*
|--------------------------------------------------------------------------
| Convert String to Lowercase
|--------------------------------------------------------------------------
*/

string toLower(string text)
{
    transform(
        text.begin(),
        text.end(),
        text.begin(),
        ::tolower
    );

    return text;
}

/*
|--------------------------------------------------------------------------
| Levenshtein Distance
|--------------------------------------------------------------------------
*/

int getLevenshteinDistance(
    const string& s1,
    const string& s2)
{
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(
        m + 1,
        vector<int>(n + 1)
    );

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                });
            }
        }
    }

    return dp[m][n];
}

/*
|--------------------------------------------------------------------------
| Secure Hash
|--------------------------------------------------------------------------
*/

string generateSecureHash(
    const string& data)
{
    hash<string> stringHasher;

    size_t hashValue = stringHasher(data);

    stringstream ss;

    ss << hex
       << setw(16)
       << setfill('0')
       << hashValue;

    return ss.str();
}

/*
|--------------------------------------------------------------------------
| Empty String
|--------------------------------------------------------------------------
*/

bool isEmpty(string text)
{
    return text.empty();
}

/*
|--------------------------------------------------------------------------
| Positive Number
|--------------------------------------------------------------------------
*/

bool isPositive(int number)
{
    return number > 0;
}

/*
|--------------------------------------------------------------------------
| Phone Validation
|--------------------------------------------------------------------------
*/

bool isValidPhone(string phone)
{
    if (phone.length() != 10)
        return false;

    for(char c : phone)
    {
        if(!isdigit(c))
            return false;
    }

    return true;
}

/*
|--------------------------------------------------------------------------
| Blood Group Validation
|--------------------------------------------------------------------------
*/

bool isValidBloodGroup(string group)
{
    static const vector<string> groups =
    {
        "A+","A-",
        "B+","B-",
        "AB+","AB-",
        "O+","O-"
    };

    for(const auto& g : groups)
    {
        if(g == group)
            return true;
    }

    return false;
}