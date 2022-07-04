all: main.cpp Comparable.cpp Infix.cpp Postfix.cpp ComparableOp.h Infix.h Postfix.h Stack.h
	 g++ main.cpp Comparable.cpp Infix.cpp Postfix.cpp ComparableOp.h Infix.h Postfix.h Stack.h -o main

clean:
	rm main