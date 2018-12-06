#ifndef __ENVIRONS_H__
#define __ENVIRONS_H__
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <map>
using namespace std;
// This class is used to store the PATH variable.
// It seems unnecessary as it was simplied during the work.
// I do not have enought time to delete this class
class Environs{
public:
	vector<string> envValue;
};

#endif