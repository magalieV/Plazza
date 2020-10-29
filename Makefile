##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

NAME	=	plazza

all:	$(NAME)

$(NAME):
	mkdir -p build
	cd build && cmake .. && cd -
	make -C build/
	cp build/$(NAME) .

clean:
	rm -rf build/

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY	:	all clean fclean re