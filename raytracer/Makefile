UNAME_S :=$(shell uname -s)

BOLD := \033[1m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
BLUE := \033[0;34m
NC := \033[0m
all: rayTracer
rayTracer: *.c
	@printf "$(BLUE)$(BOLD)Compiling for $(UNAME_S)...  $(NC)"
ifeq ($(UNAME_S), Linux)
	@cc -O3 -fopenmp -I./raylib/src/ main.c -o ray ./raylib/src/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
	@printf "$(GREEN)$(BOLD)Building is done!$(NC)\n"
else ifeq ($(UNAME_S), Darwin)
	@cc -O3 -I./raylib/src/ main.c -o ray ./raylib/src/libraylib.a -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	@printf "$(GREEN)$(BOLD)Building is done!$(NC)\n"
else
	@$(error Unsupported operating system)
	@printf "$(RED)$(BOLD)Unsupported operating system$(NC)\n"
endif
clean:
	@rm -rf ray
	@printf "$(YELLOW)$(BOLD)Cleaning up...$(NC)\n"
re: clean rayTracer
