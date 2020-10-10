#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "BucketNode.h"
#include "methods.h"
#include "inbetweenDates.h"
#include "BST.h"
using namespace std;

int main(int argc, char * argv[]) {
    int h1, h1i, h2, h2i, b, bi;

    if (argc != 9) {
        printf("lathos parametroi \n");
        printf("prepei na einai: -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize \n");
        return 0;
    }
//elegxos gia orismata
    if (string(argv[1]) == "-h1") {
        h1 = atoi(argv[2]);
        h1i = 1;
    }//h thesh tou h1
    else if (string(argv[3]) == "-h1") {
        h1 = atoi(argv[4]);
        h1i = 3;
    } else if (string(argv[5]) == "-h1") {
        h1 = atoi(argv[6]);
        h1i = 5;
    } else if (string(argv[7]) == "-h1") {
        h1 = atoi(argv[8]);
        h1i = 7;
    } else {
        printf("lathos parametroi \n");
        printf("prepei na einai: -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize \n");
        return 0;
    }
    if (string(argv[1]) == "-h2") {
        h2 = atoi(argv[2]);
        h2i = 1;
    } else if (string(argv[3]) == "-h2") {
        h2 = atoi(argv[4]);
        h2i = 3;
    } else if (string(argv[5]) == "-h2") {
        h2 = atoi(argv[6]);
        h2i = 5;
    } else if (string(argv[7]) == "-h2") {
        h2 = atoi(argv[8]);
        h2i = 7;
    } else {
        printf("lathos parametroi \n");
        printf("prepei na einai: -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize \n");
        return 0;
    }
    if (string(argv[1]) == "-b") {
        b = atoi(argv[2]);
        bi = 1;
    } else if (string(argv[3]) == "-b") {
        b = atoi(argv[4]);
        bi = 3;
    } else if (string(argv[5]) == "-b") {
        b = atoi(argv[6]);
        bi = 5;
    } else if (string(argv[7]) == "-b") {
        b = atoi(argv[8]);
        bi = 7;
    } else {
        printf("lathos parametroi \n");
        printf("prepei na einai: -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize \n");
        return 0;
    }
    int q = 16 - bi - h1i - h2i + 1;
    int bucketsize = (b - sizeof (BucketNode*) - sizeof (Data*)) / (sizeof (Data));
    bool messages = true;

   // printf("b = %d \n", b);
   // printf("h1 = %d \n", h1);
 //   printf("h2 = %d \n", h2);
//   printf("bucketsize = %d \n", bucketsize);

    initializeHashtables(h1, h2, bucketsize); //arxikopoiisi

    ifstream recordsfile(argv[q]); //anoigei to arxeio gia ta records
    if (recordsfile.is_open() && recordsfile.good()) {
        string line = "";
        int l = 0;
        while (getline(recordsfile, line)) {
            stringstream command(line);
            string names[7] = {"ID", "firstname", "lastname", "disease", "country", "entrydate", "exitdate"};
            string data[7] = {"", "", "", "", "", "", ""};
            command >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6] >> data[7];

            for (int i = 0; i < 7; i++) {
                if (data[i] == "") {
                    cout << names[i] << " is missing in line " << l << endl;
                    cout << "cannot proceed with incorrect file" << endl;
                    return 0;
                }
            }

            Record * record = new Record(data);

           // cout << record->id << " " << record->firstname << " " << record->lastname << " " << record->disease << " " <<
             //       record->country << " " << record->entrydate << " " << record->exitdate << endl;

            insertPatientRecord(false, record); //eisagwgi twn records apo to arxeio
            l++;
        }

    } else {
        cout << "Failed to open file..";
    }

    string line = "";

    
    
    bool error;
    while (true) {
        error = false;
       // cout << "dose entoli: ";

        if (getline(cin, line)) { //dexetai entoles
            if (line == "exit" || line == "/exit") {
                cout<<"exiting"<<endl;
                cleanupStructures();
                break;
            }
            
            stringstream command(line);
            string entoli;

            string names[8] = {"ID", "firstname", "lastname", "disease", "country", "entrydate", "exitdate"};
            string data[8] = {"", "", "", "", "", "", "", ""};

            command >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6] >> data[7];

           // cout << "you typed: " << data[0] << endl;

            if (data[0] == "insertPatientRecord" || data[0] == "/insertPatientRecord") {
                for (int i = 1; i < 7; i++) {
                    if (data[i] == "") {
                        cout << names[i] << " is missing " << endl;
                        cout << "cannot proceed with incorrect file" << endl;
                        error = true;
                    }
                }
                if (!error) {
                    if (data[7] == "") {
                        data[7] = "-";
                    }
                    string data2[7] = {data[1], data[2], data[3], data[4], data[5], data[6], data[7]};
                    Record * record = new Record(data2);
                    insertPatientRecord(messages, record);
                }
            } else if (data[0] == "/globalDiseaseStats" || data[0] == "globalDiseaseStats") {
                if ((data[1] == "" && data[2] != "") || (data[1] != "" && data[2] == "")) {
                    cout << "error: You have to enter either two dates or no dates at all" << endl;
                } else {
                    if (data[1] == "") {
                        globalDiseaseStats(messages, NULL, NULL);
                    } else {
                        globalDiseaseStats(messages, &data[1], &data[2]);
                    }
                }
            } else if (data[0] == "/diseaseFrequency" || data[0] == "diseaseFrequency") {
                if (data[1] == "" || data[3] == "" || data[2] == "") {
                    cout << "error: you have to enter one virus name,(maybe a country-optional) and two dates" << endl;
                } else {
                    if (data[4] == "") {
                        diseaseFrequency(messages, data[1], NULL, data[2], data[3]);
                    } else {
                        diseaseFrequency(messages, data[1], &data[4], data[3], data[2]);
                    }
                }

            } else if (data[0] == "/topk-Diseases" || data[0] == "topk-Diseases") {
                if (data[1] == "" || data[2] == "" || (data[3] == "" && data[4] != "") || (data[3] != "" && data[4] == "")) {
                    cout << "error: you have to enter a number(top k), a country and either two dates or no dates at all" << endl;
                } else {
                    if (data[3] == "") {
                        cout<<"1"<<endl;
                        //                        topk_Diseases(true, atoi(data[1].c_str()), data[2], NULL, NULL);
                    } else {
                       cout<<"1"<<endl;
                        //                        topk_Diseases(true, atoi(data[1].c_str()), data[2], &data[3], &data[4]);
                    }
                }
            } else if (data[0] == "/topk-Countries" || data[0] == "topk-Countries") {
                if (data[1] == "" || data[2] == "" || (data[3] == "" && data[4] != "") || (data[3] != "" && data[4] == "")) {
                    cout << "error: you have to enter a number(top k), a disease and either two dates or no dates at all" << endl;
                } else {
                    //int x;

                    if (data[3] == "") {
                        cout<<"1"<<endl;
                        //                        topk_Countries(true, atoi(data[1].c_str()), data[2], NULL, NULL);
                    } else {
                        cout<<"1"<<endl;
                        //                        topk_Countries(true, atoi(data[1].c_str()), data[2], &data[3], &data[4]);
                    }
                }
            } else if (data[0] == "/recordPatientExit" || data[0] == "recordPatientExit") {
                if (data[1] == "" || data[2] == "") {
                    cout << "error:you have to enter recordId and exitdate" << endl;
                } else {
                    recordPatientExit(messages, data[1], data[2]);
                }
            } else if (data[0] == "/numCurrentPatients" || data[0] == "numCurrentPatients") {
                if (data[1] == "") {
                    numCurrentPatients(messages, NULL);
                } else {
                    numCurrentPatients(messages, &data[1]);
                }
            } else {
                cout << "Invalid Command" << endl;
                cout << "You can use one of the following:" << endl;
                cout << "exit" << endl;
                cout << "insertPatientRecord" << endl;
                cout << "recordPatientExit" << endl;
                cout << "numCurrentPatients" << endl;
                cout << "globalDiseaseStats" << endl;
                cout << "diseaseFrequency" << endl;
                cout << "topk_Diseases" << endl;
                cout << "topk_Countries" << endl;

            }
        }else{ //an vrei eof
                cleanupStructures();
                break;
        }

    }

    return 0;
}
