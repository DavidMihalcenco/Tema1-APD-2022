build:
	g++ tema1.cpp helper.cpp -o tema1 -lpthread
build_debug:
	g++ tema1.cpp helper.cpp -o tema1 -lpthread -O0 -g3 -DDEBUG -Wall -Werror
clean:
	rm tema1