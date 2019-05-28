
build:
	@g++ src/wildtetris.cpp -Iheaders -std=c++17 -o bin/wildtetris.exe
	
runtest:
	@g++ src/wildtetris.cpp -Iheaders -std=c++17 -o bin/wildtetris.exe
	@bin/wildtetris.exe

test:
	@g++ tests/wildtetris.cpp -Iheaders -std=c++17 -o bin/tests.exe
	@bin/tests.exe
