# super simple makefile
# call it using 'make NAME=name_of_code_file_without_extension'
# (assumes a .cpp extension)
NAME = snake

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
	g++ -o $(NAME) $(NAME).cpp Snake.cpp Controller.cpp Block.cpp Fruit.cpp Text.cpp -L/opt/X11/lib -lX11 -lstdc++ $(MAC_OPT) -std=c++14

run: all
	@echo "Running..."
	./$(NAME) 

clean:
	rm ./$(NAME)
