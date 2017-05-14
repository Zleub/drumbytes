# @Author: Debray Arnaud <zleub>
# @Date:   2017-05-02T11:56:38+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-05-15T01:07:53+02:00

NAME = drumbytes
SRC = $(shell find ./src -name "*.cpp") main.cpp
OBJ = $(subst .cpp,.o,$(SRC))

CXX = clang++
CXXFLAGS = -std=c++11  \
	-g -fsanitize=address

LDFLAGS = -L /Volumes/ADEBRAY/.brew/lib \
	-rpath /Volumes/ADEBRAY/.brew/lib \
	-lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

INC = -Iinc \
	-I/Volumes/ADEBRAY/.brew/include

all: depend $(NAME)

depend: $(SRC)
	@ rm -f ./.depend
	@ $(foreach var, $^, $(CC) $(INC) $(CXXFLAGS) -MT $(subst .cpp,.o,$(var)) -MM $(var) >> ./.depend;)

%.o:%.cpp
	@echo $<" -> "$@
	@$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

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
