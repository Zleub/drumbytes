# @Author: Debray Arnaud <zleub>
# @Date:   2017-05-02T11:56:38+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-05-11T21:00:23+02:00

NAME = drumbytes
SRC = $(shell find . -name "*.cpp")
OBJ = $(subst .cpp,.o,$(SRC))

CXX = clang++
CXXFLAGS = -Iinc -I/Volumes/ADEBRAY/.brew/include \
	-Wall -Wextra -Werror -std=c++11 -g -fsanitize=address
LDFLAGS = -framework CoreAudio -framework CoreFoundation \
	-L /Volumes/ADEBRAY/.brew/lib \
	-rpath /Volumes/ADEBRAY/.brew/lib -lstk -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

all: depend $(NAME)

depend: $(SRC) main.cpp
	@ rm -f ./.depend
	@ $(foreach var, $^, $(CC) $(CXXFLAGS) -MT $(subst .cpp,.o,$(var)) -MM $(var) >> ./.depend;)

%.o:%.cpp
	@echo $<" -> "$@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

include .depend

$(NAME): $(OBJ)
	@echo $^" -> "$@
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(NAME) $^

clean:
	rm -rf main.o
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all re clean fclean depend
