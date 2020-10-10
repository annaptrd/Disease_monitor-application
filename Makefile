objects = main.o BST.o BucketNode.o Data.o HashTable.o Record.o dateToInt.o hashFunction.o inbetweenDates.o linkedListTypes.o methods.o readfile.o

diseaseMonitor: $(objects)
	g++ -g $(objects) -o diseaseMonitor

main.o: BucketNode.h methods.h inbetweenDates.h BST.h
methods.o: methods.h linkedListTypes.h HashTable.h dateToInt.h
linkedListTypes.o: linkedListTypes.h
inbetweenDates.o: dateToInt.h
hashFunction.o: hashFunction.h
dateToInt.o: Record.h
Record.o: Record.h dateToInt.h
HashTable.o: HashTable.h hashFunction.h
Data.o: Data.h
BucketNode.o: BucketNode.h
BST.o: BST.h dateToInt.h inbetweenDates.h linkedListTypes.h

clean :
		rm diseaseMonitor $(objects)
