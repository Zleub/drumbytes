# @Author: Debray Arnaud <zleub>
# @Date:   2017-05-02T11:56:38+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-06-08T02:18:37+02:00

NAME = drumbytes
SRC = $(shell find ./src -name "*.cpp") main.cpp
OBJ = $(subst .cpp,.o,$(SRC))

CXX = clang++
CXXFLAGS = -O3 -std=c++11 -g -fsanitize=address

LDFLAGS = -rpath sfml/Frameworks -F sfml/Frameworks -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio

INC = -Iinc \
	-Isfml/include

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
