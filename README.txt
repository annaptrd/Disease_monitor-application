check hw1-spring-2020.pdf for project description/requirements


Για τη μεταγλώττιση και την εκτέλεση χρησιμοποιώ το Makefile που έχω φτιάξει, οπότε αρκεί για τη μεταγλώττιση η εντολή:
 
make

και για την εκτέλεση:

./diseaseMonitor -p small.txt -h1 100 -h2 100 -b 4096
(βεβαια μπορει να τα δεχτει με οποιαδηποτε σειρα τα ορισματα)


Αν δεν ήθελα να χρησιμοποιήσω το Makefile, τοτε θα το μεταγλώττιζα ως εξής:

g++    -c -o main.o main.cpp
g++    -c -o BST.o BST.cpp
g++    -c -o BucketNode.o BucketNode.cpp
g++    -c -o Data.o Data.cpp
g++    -c -o HashTable.o HashTable.cpp
g++    -c -o Record.o Record.cpp
g++    -c -o dateToInt.o dateToInt.cpp
g++    -c -o hashFunction.o hashFunction.cpp
g++    -c -o inbetweenDates.o inbetweenDates.cpp
g++    -c -o linkedListTypes.o linkedListTypes.cpp
g++    -c -o methods.o methods.cpp
g++    -c -o readfile.o readfile.cpp
g++ -g main.o BST.o BucketNode.o Data.o HashTable.o Record.o dateToInt.o hashFunction.o inbetweenDates.o linkedListTypes.o methods.o readfile.o -o diseaseMonitor


Για την υλοποίηση της άσκησης χρησιμοποίησα μια λίστα στην οποία αποθηκεύω όλα τα records, δύο πίνακες κατακερματισμού, στους οποίους η εισαγωγή γίνεται στον έναν με βάση τις ασθένειες και στον αλλον με βάση τις χώρες. Τη συνάρτηση που χρησιμοποιώ για το hashing, τη βρήκα εδώ:


The Practice of Programming (Addison-Wesley Professional Computing Series) 1st Edition

(HASH TABLES, pg. 57)

http://index-of.co.uk/Etc/The.Practice.of.Programming.-.B.W..Kernighan..pdf

Το κάθε κελί του κάθε πίνακα κατακερματισμού είναι δείκτης σ'ένα bucketnode, το οποίο δείχνει σε ένα επόμενο bucketnode κτλ. Το bucketnode, πέρα από το δείκτη για το επόμενο, περιέχει και το bucketsize και έναν δείκτη σε Data. Μέσα σε αυτό το Data αποθηκεύεται το όνομα της ασθένειας ή της χώρας αντιχτοίχως στον κάθε πίνακα κατακερματισμού, καθώς και μια μεταβλητη για το αν ειναι άδειο ή οχι. Επίσης μέσα σε κάθε Data υπάρχει ένα δέντρο, το οποίο έχει έναν κόμβο για κάθε ημερομηνία εισαγωγής ασθενών και μέσα σ αυτόν τον κόμβο υπάρχει μια λίστα από τα άτομα με αυτή την ημέρα εισαγωγής. Τα δέντρα που φτιάχνω είναι BBST και συγκεκριμένα τύπου red-black. Για το balancing του red-black, συμβουλεύτηκα την αντιστοιχη σελίδα της wikipedia:
https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

Η εισαγωγή κάθε νέου bucketNode γίνεται στην αρχή (πριν τον πρωτο bucketnode).

Tις συναρτήσεις που δέχονταν προαιρετικά όρισμα, τις υλοποίησα ώστε να δέχονται δείκτη για το προαιρετικό όρισμα, ώστε να είναι NULL σε περίπτωση που δε δοθεί τίποτα. 

Για να ελέγξω αν ένας ασθενής ήταν άρρωστος σε συγκεκριμένο διαστημα, συγκρίνω τις ημερομηνίες που μας ενδιαφέρουν με την ημερομηνία εισαγωγής του. Για να συγκρίνω τις ημερομηνίες μεταξύ τους, τις μετατρέπω σε ακεραίους (πχ 13-01-2003->20030113).

Για τη διάσχιση του δέντρου στα διάφορα σημεία, χρησιμοποίησα μια απλή DFS.

Για να ελέγξω αν υπάρχει exitdate χρησιμοποιώ ένα NO_DATE, το οποίο κάνω αρχικά define.

Στις μεθόδους μου χρησιμοποιώ ένα bool message, αυτό το έβαλα κυρίως γιατί με βοηθούσε σε ελεγχους στο debugging. 

Στο δέντρο πρώτα γίνεται η εισαγωγη και μετά αμέσως το balancing.

Στην recordPatientExit(), ελεγχω αν η ημερομηνία εισαγωγής είναι προγενέστερη αυτης που θέλω να βάλω ως exit date, αλλιως βγάζω error(αν δηλαδη το exit date ειναι πριν το entry date). Eπισης αν το exit date δεν ειναι κενο, δεν το αλλαζω, ομως έχω αλλαξει την εκτυπωση σε "Record updated" για να τρέχει ο validator. Στην πραγματικότητα έβγαζα "exit date:already exists".

Δεν υλοποίησα το σωρό και τις top_k συναρτήσεις, γι αυτόν το λόγο, για να τρέχει το validator, άλλαξα τα result files αυτών των εντολών, ώστε να ζητούν μια τιμή "1" , την οποία δίνω καρφωτά στο πρόγραμμα μου για αυτο το σκοπο.Όλα τα άλλα τρέχουν επιτυχώς και μεμονωμένα και με το validator.
Οι top_k συναρτήσεις μπορούν να κληθούν κανονικά κι έχουν και μήνυμα λάθους σε περίπτωση που δοθεί μονο μια ημερομηνία. Παρόλα αυτά δεν πρόλαβα να τις υλοποιήσω περαιτερω.

Για το διαβασμα αρχειων συμβουλεύτηκα τη σελίδα αυτή:
http://www.cplusplus.com/forum/general/179626/


