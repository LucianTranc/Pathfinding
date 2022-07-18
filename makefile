CC = g++
CFLAGS = -Wall -std=c++11
INC_PATH = -I /Library/Frameworks/SDL2.framework/Headers -I /Library/Frameworks/SDL2_image.framework/Headers -I /Library/Frameworks/SDL2_ttf.framework/Headers
LDFLAGS = -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0

pathfinding: main.o
	$(CC) $(CFLAGS) $(INC_PATH) $(LDFLAGS) -framework OpengL bin/main.o bin/Game.o bin/Grid.o -o play

main.o: main.cpp bin/Game.o bin/Grid.o
	$(CC) $(CFLAGS) $(INC_PATH) main.cpp -c -o bin/main.o

bin/Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) $(INC_PATH) Game.cpp -c -o bin/Game.o

bin/Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) $(INC_PATH) Grid.cpp -c -o bin/Grid.o

clean :
	-rm *.o bin/*.o play