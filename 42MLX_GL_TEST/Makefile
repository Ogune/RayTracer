all: anRayTracer

anRayTracer: *.c
	cc -o anRayTracer *.c MLX42/build/libmlx42.a -g  -ldl -lglfw -pthread -lm -I cglm/include/cglm/
clean:
	rm -f anRayTracer

re: clean all
