CFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3
all: myShell testArgs testOutput testSTDIN dpArgs testSTDERR testAllRedir
myShell: myShell.cpp
	g++  $(CFLAGS) -o myShell myShell.cpp

testAllRedir: testAllRedir.cpp
	g++  $(CFLAGS) -o testAllRedir testAllRedir.cpp

testArgs: testArgs.cpp
	g++  $(CFLAGS) -o testArgs testArgs.cpp 
testOutput: testOutput.cpp
	g++  $(CFLAGS) -o testOutput testOutput.cpp 
testSTDIN: testSTDIN.cpp
	g++  $(CFLAGS) -o testSTDIN testSTDIN.cpp
testSTDERR: testSTDERR.cpp
	g++ $(CFLAGS) -o testSTDERR testSTDERR.cpp
dpArgs: dpArgs.cpp
	g++  $(CFLAGS) -o dpArgs dpArgs.cpp

clean:
	rm myShell *~
