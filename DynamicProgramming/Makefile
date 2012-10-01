.PNONY : build_lib
build_lib : bin/libdp.a

bin/libdp.a : obj/dp.o
	ar -r bin/libdp.a obj/dp.o
obj/dp.o : src/dp.c inc/dp.h
	gcc -fpic -Iinc -c src/dp.c -o obj/dp.o

.PNONY : test
test : bin/dp_test

bin/dp_test : bin/libdp.a obj/dp_test.o
	gcc obj/dp_test.o -Lbin -ldp -o bin/dp_test

obj/dp_test.o : test/dp_test.c inc/dp.h
	gcc  -Iinc -c test/dp_test.c  -o obj/dp_test.o

.PNONY:clean
clean:
	rm obj/*.o
	rm bin/*
