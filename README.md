# qt-examples
Some examples of Qt projects
*all project names were generated with [Superhero Name generator] (http://online-generator.com/name-generator/superhero-name-generator.php)*

## BetaEagle

**BetaEagle** app shows how to use unit tests. The project consists of two parts:
 - the application itself. It reads a text file with integer numbers an print the biggest one.
 - the unit tests. App code has two classes and both can be tested.

 To run the application
```
$ ./app/build/bin/a01app ./app/testData/f01.txt
Max value is  2014
$
```
For tests
```
u1(00:07:13):$ ./test/build/bin/testApp
********* Start testing of TestDataProcessor *********
Config: Using QtTest library 5.7.0, Qt 5.7.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 4.9.1 20140922 (Red Hat 4.9.1-10))
PASS   : TestDataProcessor::initTestCase()
PASS   : TestDataProcessor::process_BasicA()
PASS   : TestDataProcessor::process_Equal()
PASS   : TestDataProcessor::process_BasicB()
PASS   : TestDataProcessor::cleanupTestCase()
Totals: 5 passed, 0 failed, 0 skipped, 0 blacklisted, 0ms
********* Finished testing of TestDataProcessor *********
********* Start testing of TestFileLoader *********
Config: Using QtTest library 5.7.0, Qt 5.7.0 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 4.9.1 20140922 (Red Hat 4.9.1-10))
PASS   : TestFileLoader::initTestCase()
PASS   : TestFileLoader::getErrorMessage_A()
PASS   : TestFileLoader::loadFile_ErrA()
PASS   : TestFileLoader::cleanupTestCase()
Totals: 4 passed, 0 failed, 0 skipped, 0 blacklisted, 0ms
********* Finished testing of TestFileLoader *********
$
```

## BetaFalcon

**BetaFalcon** is same as *BetaEagle* but it stores test data in files, instead of hardcoding it inside test sources. It's an overengineered solution for such simple class but becomes useful in real projects with more sophisticated data structures.

Also it shows hot to use the [Qt Resource System](http://doc.qt.io/qt-5/resources.html).
