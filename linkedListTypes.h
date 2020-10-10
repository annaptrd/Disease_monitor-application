#ifndef LINKEDLISTTYPES_H
#define LINKEDLISTTYPES_H
#include <string>

using namespace std;

#include "Record.h"


using namespace std;

class Node {
public:
    Record * rec;
    Node* next;
};

class LinkedList {
public:
    LinkedList();
    void insertNode(Record *);
    bool insertNodeWithCheck(Record *);
    void deleteNode(string); //record
    Node* searchList(string);
    void printList();
    ~LinkedList();
    void destroyRecords();
    int searchForCountry(string c);
    Node* head;
   
};


#endif //MYCLASSES_Η
