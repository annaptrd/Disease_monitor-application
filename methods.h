#ifndef METHODS_H
#define METHODS_H

#include "Record.h"

#include <string>

using namespace std;

void initializeHashtables(int, int, int);

void insertPatientRecord(bool,Record *);

void recordPatientExit(bool,string, string);

void numCurrentPatients(bool,string *);

void globalDiseaseStats(bool,string*, string* );

void diseaseFrequency(bool,string ,string* ,string , string );

void topk_Diseases(bool,int ,string ,string* ,string*);

void topk_Countries(bool,int ,string ,string* ,string*);

void cleanupStructures();

#endif /* METHODS_H */