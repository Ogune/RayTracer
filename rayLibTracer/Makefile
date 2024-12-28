all: rayTracer
rayTracer: *.c
	cc -I./raylib/src *.c -o rayTracer ./raylib/src/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
clean:
	rm -rf rayTracer
re: clean rayTracer
