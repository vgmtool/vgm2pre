include ../nall/Makefile
include ../phoenix/Makefile

application := vgm2pre
flags := -O3 -fomit-frame-pointer -I..
link := -s
objects := obj/phoenix.o obj/$(application).o

ifeq ($(platform),windows)
  ifeq ($(arch),x86)
    flags += -m32
    link += -m32
    rlink += --target=pe-i386
  endif
  link += -mwindows -static
  objects += obj/resource.o
endif

all: $(objects)
	$(compiler) -o $(application) $(objects) $(link) $(phoenixlink)

#obj/resource.o: ../phoenix/windows/phoenix.rc
#	windres ../phoenix/windows/phoenix.rc obj/resource.o

obj/resource.o: app.rc
	windres $(rlink) app.rc obj/resource.o

obj/phoenix.o: ../phoenix/phoenix.cpp
	$(compiler) $(phoenixflags) -o obj/phoenix.o -c ../phoenix/phoenix.cpp

obj/$(application).o: $(application).cpp *.cpp *.hpp ui/*.hpp
	$(compiler) $(cppflags) $(flags) -o obj/$(application).o -c $(application).cpp

install:
	sudo cp $(application) /usr/local/bin/$(application)

clean:
	$(call delete,obj/*.o)
