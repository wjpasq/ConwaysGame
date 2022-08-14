# ConwaysGame  

Play Conway's Game of Life, one generation at a time.  
  
Conway's game starts with a grid of cells, some cells are alive (represented by '*') and other cells are dead (represented by '-'). The initial generation is randomly generated but every subsequent generation is based on the following rules:  
1. Any live cell with fewer than two live neighbors dies as if caused by underpopulation.  
2. Any live cell with two or three live neighbors lives on to the next generation.  
3. Any live cell with more than three live neighbors dies, as if by overpopulation.  
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.  
  
Use the Makefile to compile the game:  
>make  
  
Run  
>./run-conway.o  
  
to play the game.  
