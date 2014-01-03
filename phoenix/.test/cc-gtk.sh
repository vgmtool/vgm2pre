g++ -std=c++11 -I../.. -g -c ../phoenix.cpp -DPHOENIX_GTK `pkg-config --cflags gtk+-2.0`
g++ -std=c++11 -I../.. -g -c test.cpp
g++ -o test-gtk test.o phoenix.o `pkg-config --libs gtk+-2.0` -lX11
rm *.o
