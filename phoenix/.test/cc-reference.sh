g++ -std=c++11 -Wzero-as-null-pointer-constant -I../.. -O3 -fomit-frame-pointer -c ../phoenix.cpp -DPHOENIX_REFERENCE
g++ -std=c++11 -Wzero-as-null-pointer-constant -I../.. -O3 -fomit-frame-pointer -c test.cpp
g++ -s -o test-reference test.o phoenix.o
rm *.o
