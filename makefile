CC = g++
CFLAGS = -Wall -std=c++11
INC_PATH = -I /Library/Frameworks/SDL2.framework/Headers -I /Library/Frameworks/SDL2_image.framework/Headers -I /Library/Frameworks/SDL2_ttf.framework/Headers
LDFLAGS = -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0

pathfinding: main.o
	$(CC) $(CFLAGS) $(INC_PATH) $(LDFLAGS) -framework OpengL bin/main.o bin/Game.o bin/Grid.o bin/MazeGenerator.o bin/GridManager.o bin/PathfindingManager.o bin/PathfindingAlgorithm.o bin/DepthFirstSearch.o bin/BreadthFirstSearch.o bin/AStar.o bin/UIManager.o bin/Button.o bin/Label.o bin/DrawingController.o -o play

main.o: main.cpp bin/Game.o bin/Grid.o bin/MazeGenerator.o bin/GridManager.o bin/PathfindingManager.o bin/PathfindingAlgorithm.o bin/DepthFirstSearch.o bin/BreadthFirstSearch.o bin/AStar.o bin/UIManager.o bin/Button.o bin/Label.o bin/DrawingController.o
	$(CC) $(CFLAGS) $(INC_PATH) main.cpp -c -o bin/main.o

bin/Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) $(INC_PATH) Game.cpp -c -o bin/Game.o

bin/Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) $(INC_PATH) Grid.cpp -c -o bin/Grid.o

bin/MazeGenerator.o: MazeGenerator.cpp MazeGenerator.h
	$(CC) $(CFLAGS) $(INC_PATH) MazeGenerator.cpp -c -o bin/MazeGenerator.o

bin/GridManager.o: GridManager.cpp GridManager.h
	$(CC) $(CFLAGS) $(INC_PATH) GridManager.cpp -c -o bin/GridManager.o

bin/DrawingController.o: DrawingController.cpp DrawingController.h
	$(CC) $(CFLAGS) $(INC_PATH) DrawingController.cpp -c -o bin/DrawingController.o

bin/UIManager.o: UIManager.cpp UIManager.h
	$(CC) $(CFLAGS) $(INC_PATH) UIManager.cpp -c -o bin/UIManager.o

bin/Button.o: Button.cpp Button.h
	$(CC) $(CFLAGS) $(INC_PATH) Button.cpp -c -o bin/Button.o

bin/Label.o: Label.cpp Label.h
	$(CC) $(CFLAGS) $(INC_PATH) Label.cpp -c -o bin/Label.o

bin/PathfindingManager.o: Pathfinding/PathfindingManager.cpp Pathfinding/PathfindingManager.h
	$(CC) $(CFLAGS) $(INC_PATH) Pathfinding/PathfindingManager.cpp -c -o bin/PathfindingManager.o

bin/PathfindingAlgorithm.o: Pathfinding/PathfindingAlgorithm.cpp Pathfinding/PathfindingAlgorithm.h
	$(CC) $(CFLAGS) $(INC_PATH) Pathfinding/PathfindingAlgorithm.cpp -c -o bin/PathfindingAlgorithm.o

bin/DepthFirstSearch.o: Pathfinding/DepthFirstSearch.cpp Pathfinding/DepthFirstSearch.h
	$(CC) $(CFLAGS) $(INC_PATH) Pathfinding/DepthFirstSearch.cpp -c -o bin/DepthFirstSearch.o

bin/BreadthFirstSearch.o: Pathfinding/BreadthFirstSearch.cpp Pathfinding/BreadthFirstSearch.h
	$(CC) $(CFLAGS) $(INC_PATH) Pathfinding/BreadthFirstSearch.cpp -c -o bin/BreadthFirstSearch.o

bin/AStar.o: Pathfinding/AStar.cpp Pathfinding/AStar.h
	$(CC) $(CFLAGS) $(INC_PATH) Pathfinding/AStar.cpp -c -o bin/AStar.o

clean :
	-rm *.o bin/*.o play