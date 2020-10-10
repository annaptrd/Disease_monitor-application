
#include "methods.h"
#include "linkedListTypes.h"
#include "HashTable.h"
#include "dateToInt.h"
#include <iostream>

using namespace std;

struct s{
    LinkedList list;
    HashTable hashtable1;
    HashTable hashtable2;
}structures;

void initializeHashtables(int h1, int h2, int b) { //arxikopoiisi
    structures.hashtable1.initializeBuckets(h1, b);
    structures.hashtable2.initializeBuckets(h2, b);
}

void cleanupStructures() { //gia tin katastrofi twn domwn
    structures.list.destroyRecords();
}

void insertPatientRecord(bool messages, Record * record) { //gia tin eisagwgi twn records
    if (messages) {
   //     cout << "method insertPatientRecord" << endl;
    }

    if (structures.list.insertNodeWithCheck(record)) {//eisagwgi sti lista an den yparxei idi
        structures.hashtable1.insertWithDisease(record);//eisagwgi stous ht
        structures.hashtable2.insertWithCountry(record);
        if (messages) {
            cout << "Record added" << endl;
        }
    } else {
        if (messages) {
            cout << "not ok" << endl;
        }
    }
}

void recordPatientExit(bool messages, string id, string exitdate) {//enimerwnei to exitdate an den yparxei
    if (messages) {
    //    cout << "method recordPatientExit" << endl;
    }
    int exdate = dateToInt(exitdate);
    Node * n = structures.list.searchList(id);
    if (n != NULL) {
        Record * record = n->rec;

        if (record->exitdate == NO_DATE) {//an den yparxei exitdate tote to enimerwnw
            // if exitdate is after entry date then:
            if (exdate > record->entrydate) {
                record->setExitDate(exitdate);
                cout << "Record updated" << endl;
                Data * data = structures.hashtable1.searchWithDisease(record->disease);
                (data->bst.activePatients)--;
            } else {//an i exitdate einai prin tin entrydate
                cout << "wrong exit date" << endl;
            }
        } else {
            cout<<"Record updated"<<endl;//yparxei idi vasika aplws gia tis anagkes tou validator...
            // cout << "exit date:already exists" << endl;
        }
    }
}

void numCurrentPatients(bool messages, string * v) { //ektypwnei ta energa krousmata
    if (v != NULL) {
    //    cout << "method numCurrentPatients" << *v << endl;
    } else {
    //    cout << "method numCurrentPatients" << endl;
    }

    if (v != NULL) {
        Data * data = structures.hashtable1.searchWithDisease(*v);//epistrefei to data me to sygkekrimeno disease
        if (data != NULL) {
            cout << *v;
            cout <<" "<< data->bst.activePatients << endl; //energa krousmata
        }
    } else {
        structures.hashtable1.printDiseasesStats();
    }

}

void globalDiseaseStats(bool messages, string* d1, string* d2) { 
    if ((d1 != NULL && d2 == NULL) || (d1 == NULL && d2 != NULL)) {
        cout << "prepei na dothoun eite dyo imerominies eite kamia" << endl;
        return;
    }
    if (d1 == NULL && d2 == NULL) {//ektypwnei posoi arrwstoi exoun katagrafei genika gia kathe iwsi
        structures.hashtable1.printGlobalStats();//sto ht twn diseases
    }else{
        int date1 = dateToInt(*d1);
        int date2 = dateToInt(*d2);
        structures.hashtable1.printGlobalStatsWithDates(date1,date2);//ektypwnei posoi arrwstoi exoun katagrafei anamesa s aytes tis imerominies
    }
}

void diseaseFrequency(bool messages, string v, string* c, string d1, string d2) {
    if (c == NULL) {//an den yparxei country
        Data * data = structures.hashtable1.searchWithDisease(v);
        cout << v;
        
        if (data != NULL) {//an vrethei i astheneia
            int i1 = dateToInt(d1);
            int i2 = dateToInt(d2);

            cout <<" "<<data->bst.searchTreeForDates(i1, i2, NULL) << endl; //ektypwnei posa einai ta krousmata mesa aytes tis imerominies gia ayti tin arrwstia
        }
        return;
    } else {

        Data * data = structures.hashtable1.searchWithDisease(v);
        cout <<v;
        
        if (data != NULL) {
            int i1 = dateToInt(d1);
            int i2 = dateToInt(d2);

            cout <<" "<<data->bst.searchTreeForDates(i1, i2, c) << endl;//omoia alla gia sygkekrimena countries
        }
    }
    
    return;
}

void topk_Diseases(bool messages, int k, string c, string* d1, string*d2) { 
    if ((d1 != NULL && d2 == NULL) || (d1 == NULL && d2 != NULL)) {
        cout << "prepei na dothoun eite dyo dates eite katholou" << endl;
        return;
    }
}

void topk_Countries(bool messages, int k, string dis, string* d1, string*d2) {
    if ((d1 != NULL && d2 == NULL) || (d1 == NULL && d2 != NULL)) {
        cout << "prepei na dothoun eite dyo dates eite katholou" << endl;
        return;
    }
}

