This Snake Game's development environment is C++ and Xwindow.

Compile this project by following command:

g++ -o $(NAME) $(NAME).cpp Snake.cpp Controller.cpp Block.cpp Fruit.cpp Text.cpp -L/opt/X11/lib -lX11 -lstdc++ $(MAC_OPT) -std=c++14

Or simply using Makefile. It can be run with is "snake" in terminal or in Clion with run button.

The Game has a snake can go up, down, left, right by key press UP/w, DOWN/s, LEFT/a and RIGHT/d respectively. When the snake eats the fruit(shows up at random position), the length of the snake grows up by 1 block(the initial snake length is 5 blocks). When the snake hits itself or the walls, it dies, and you can restart the game.

Snake can change it's directions by key press as described above. At the very beginning, press [b] to begin the game. During the game, press [p] to pause the game, and press [c] to continue. Note: [c] only works when the game is paused. When the snake is dead and enter the "restart screen", press [r] to restart the game(everything will be reset). User can press[q] to quit the game at any time.

The enhancement is adding obstacles that the snake must avoid and gaps on the border that lets the snake wrap around to other side of the screen. The white blocks are obstacles. The one single colourful block is the fruit, and the colourful blocks chain is the snake. The colour of fruit is random, and once snake eaten the fruit, the snake changes to the same colour as fruit, and fruit will be generated in a new random position with a new random colour.
