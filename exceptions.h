#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <cstdlib>

using namespace std;

class SettingsFileLockedException : public exception
{
public:
    virtual const char* what() const throw () { return "Settings file is locked!"; }
};

#endif // EXCEPTIONS_H
