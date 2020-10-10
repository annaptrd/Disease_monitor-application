#include <iostream>
#include <cstdlib>
#include <string>

#include "Record.h"
using namespace std;

int dateToInt(string d) {//metatrepw to date se int ("06-02-2016"->20160206) 
    int day, month, year;

    if (d == "" || d == "-") {
        return NO_DATE;
    }

    day = (d[0] - 48)*10 + d[1] - 48;
    month = (d[3] - 48)*10 + d[4] - 48;
    year = (d[6] - 48)*1000 + (d[7] - 48)*100 + (d[8] - 48)*10 + (d[9] - 48);

    int temp;
    temp = year * 10000 + month * 100 + day;
    return temp;
}
