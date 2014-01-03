clang -x objective-c++ -std=c++11 -stdlib=libc++ -w -I../.. -c ../phoenix.cpp -DPHOENIX_COCOA
clang -std=c++11 -stdlib=libc++ -w -I../.. -c test.cpp
if [ -d test-cocoa.app ]; then rm -r test-cocoa.app; fi
mkdir test-cocoa.app
mkdir test-cocoa.app/Contents
mkdir test-cocoa.app/Contents/MacOS
clang -std=c++11 -stdlib=libc++ -w -o test-cocoa.app/Contents/MacOS/test-cocoa phoenix.o test.o -lc++ -lobjc -framework Cocoa -framework Carbon
