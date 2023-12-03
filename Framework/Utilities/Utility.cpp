#include "Framework.h"

string Utility::ToString(wstring str)
{
    string temp;
    temp.assign(str.begin(), str.end());

    return temp;
}

wstring Utility::ToWString(string str)
{
    wstring temp;
    temp.assign(str.begin(), str.end());

    return temp;
}

vector<string> Utility::SplitString(string origin, const string& tok)
{
    vector<string> result;

    size_t cutAt = 0;

    while((cutAt = origin.find_first_of(tok)) != origin.npos)
    {
        if (cutAt > 0)
            result.push_back(origin.substr(0, cutAt));
        
        origin = origin.substr(cutAt + 1);
    }

    if (origin.size() > 0)
        result.push_back(origin);

    return result;
}
