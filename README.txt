DynamicLibraryClient - Example Program space
2024-02-18, Sunday
--------------------------------


PURPOSE: Intent is to prototype a single 'main.cpp' driver program that can:
    - Link against multiple different dynamic libraries implementing common interface to provide different behavior.
    - Different libraries can BUILD and INSTALL.
    - Different driver-programs (from same main.cpp) can BUILD, carrying their depnedencies with them, and run.
    - Different driver-programs (from same main.cpp) can INSTALL, carrying their depnedencies with them, and run.


 SOURCE TREEE                BUILD TREE                             INSTALL TREEE
-----------------           -----------------                       -----------------
./CMakeLists.txt            ./_build/                               /opt/rubix/                     ('rubix' is a placeholder name)
./src/main.cpp              ./_build/bin/FooDriver.exe              /opt/rubix/bin/FooDriver.exe
                            ./_build/bin/BarDriver.exe              /opt/rubix/bin/BarDriver.exe
                            ./_build/bin/*.dll                      /opt/rubix/bin//bin/*.dll

./FooLib/                   ./FooLib/                               /opt/rubix/FooLib/              (not needed is it? why would these libraries be installed 
./FooLib/include/           <no headers>                            /opt/rubix/FooLib/include/       for a developer outside of the main solution?)
./FooLib/lib/               ./FooLib/lib/ ( n/a for shared libs)    /opt/rubix/FooLib/lib/
./FooLib/src/               ./FooLib/bin/ ( .dll or .so)            /opt/rubix/FooLib/bin/

./BarLib/                   ./BarLib/                               /opt/rubix/BarLib/
./BarLib/include/           <no headers>                            /opt/rubix/BarLib/include/      (not needed is it? ...)
./BarLib/lib/               ./BarLib/lib/ ( n/a for shared libs)    /opt/rubix/BarLib/lib/
./BarLib/src/               ./BarLib/bin/ ( .dll or .so)            /opt/rubix/BarLib/bin/
