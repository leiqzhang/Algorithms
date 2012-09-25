.PNONY : build_lib
build_lib : bin/libtool.a bin/libsort.a

bin/libtool.a : obj/tool.o
	ar -r bin/libtool.a obj/tool.o
bin/libsort.a : obj/sort.o
	ar -r bin/libsort.a obj/sort.o

obj/tool.o : src/tool.c inc/tool.h
	gcc -fpic -Iinc  -c src/tool.c -o obj/tool.o
obj/sort.o : src/sort.c inc/sort.h
	gcc -fpic -Iinc  -c src/sort.c -o obj/sort.o

.PNONY : test
test : bin/sort_test

bin/sort_test : bin/libsort.a obj/sort_test.o
	gcc obj/sort_test.o -Lbin -ltool -lsort -o bin/sort_test

obj/sort_test.o : test/sort_test.c inc/tool.h inc/sort.h
	gcc  -Iinc -c test/sort_test.c  -o obj/sort_test.o

.PNONY:clean
clean:
	rm obj/*.o
	rm bin/*
