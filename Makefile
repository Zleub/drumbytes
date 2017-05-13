# @Author: Debray Arnaud <zleub>
# @Date:   2017-05-02T11:56:38+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-05-13T04:09:54+02:00

NAME = drumbytes
SRC = main.cpp
OBJ = $(subst .cpp,.o,$(SRC))

CXX = clang++
CXXFLAGS = -Iinc \
	-I/Users/adebray/drumbytes/essentia/kiss_fft130 \
	-I/Volumes/ADEBRAY/.brew/include \
	-std=c++11 -Wall -Wextra -Werror \
	-g -fsanitize=address
	# -I/Volumes/ADEBRAY/Downloads/fftw-3.3.6-pl2/api/
LDFLAGS = -framework CoreAudio -framework CoreFoundation \
	-L /Volumes/ADEBRAY/.brew/lib \
	-rpath /Volumes/ADEBRAY/.brew/lib \
	-lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio \
	-lstk \
	# -L /Volumes/ADEBRAY/Downloads/fftw-3.3.6-pl2/api/.libs \
	# -lapi -lkernel

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
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(NAME) $^ /Users/adebray/drumbytes/essentia/kiss_fft130/kiss_fft.o

clean:
	rm -rf main.o
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all re clean fclean depend
