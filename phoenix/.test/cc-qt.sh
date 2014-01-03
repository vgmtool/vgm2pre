moc -i -o ../qt/platform.moc ../qt/platform.moc.hpp
g++ -std=c++11 -I../.. -g -c ../phoenix.cpp `pkg-config --cflags QtCore QtGui` -DPHOENIX_QT
g++ -std=c++11 -I../.. -g -c test.cpp
g++ -o test-qt test.o phoenix.o `pkg-config --libs QtCore QtGui`
rm *.o
