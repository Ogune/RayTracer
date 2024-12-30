all: rayTracer
rayTracer: *.c
	cc -I./raylib/src/ main.c -o ray ./raylib/src/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
clean:
	rm -rf ray
re: clean rayTracer
