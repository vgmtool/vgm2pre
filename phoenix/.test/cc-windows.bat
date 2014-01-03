windres ../windows/phoenix.rc phoenix-resource.o
g++ -std=c++11 -I../.. -g -c ../phoenix.cpp -DPHOENIX_WINDOWS
g++ -std=c++11 -I../.. -g -c test.cpp
g++ -mconsole -o test-windows test.o phoenix.o phoenix-resource.o -lkernel32 -luser32 -lgdi32 -ladvapi32 -lcomctl32 -lcomdlg32 -luxtheme -lmsimg32 -lshell32 -lole32 -lshlwapi
::@pause
@del *.o
