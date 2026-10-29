# SimBa Recruitment Task
___
## Running project on  Linux
Open folder with all project files in terminal and run <br> 
`g++ *.cpp -o program` <br>
to compile project and then run: <br>
`./program` <br>
to turn on the program.

If you get an error, you probably do not have g++ installed, which is unusal. <br>
It can be fixed by:
`sudo apt install g++`

Note that by default program just runs through all the tests and writes data from them and informs if they are successful or not.
___
## Structure of program
### TelemetryBlackBox.h
Declaration of TelemetryBlackBox class. Apart from functions needed by specification 
it has private properties that are used to keep track of the rocket. These properties
are only validated when data from them is saved in a buffer. Apart from them and buffer
there is also index keeping where in buffer was last element saved.

### TelemetryBlackBox.cpp
Implementation of TelemetryBlackBox class as specified by instructions. It has also non-member function `getStringFromRocketState` used to convert
rocket state to string.

### TelemetryBlackBoxTests.h
Declaration of test functions. All of them are in `TelemetryBlackBoxTests` namespace to not pollute default one.

### TelemetryBlackBoxTests.cpp
Implementation of test functions. Note that these are functional tests and not unit ones, as I didn't know
how to make unit tests of setter functions, as I couldn't access private members. Now when I think about I could have
used inheritance to write unit tests. Oh, well... Luckily type of tests was not specified in documentation.<br>
These tests to my knowledge cover all the paths in my code, except one that returns `0xFFFFFFFF` when checksum
is wrong. To run all the tests use `TelemetryBlackBoxTests::runAllTests()` function.

### main.cpp
Used to run the program. Currently just runs `TelemetryBlackBoxTests::runAllTests()`.

### CMakeLists.txt
Contains specification about run configuration used by me.