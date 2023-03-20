##
## EPITECH PROJECT, 2023
## MyTeams
## File description:
## Makefile
##

CC	=	gcc --coverage -g3 -I ../include

RM	=	rm -f

TARGET	=	unit-tests

SRCS	=	$(wildcard *.c) \
			$(wildcard ../lib/*.c) \
			$(wildcard ../src/*.c) \

SRCS	:=	$(filter-out ../main.c, $(SRCS))


OB	=	$(SRCS:.c=.o)


CFLAGS	=	-Wall -Wextra


all	:	$(TARGET)
		./$(TARGET)


$(TARGET)	:	$(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lcriterion


clean	:
		$(RM) $(OBJ)


fclean	:	clean
			$(RM) $(TARGET)
			$(RM) $(wildcard ../lib/*.gcno)
			$(RM) $(wildcard ../lib/*.gcda)
			$(RM) $(wildcard ../src/*.gcno)
			$(RM) $(wildcard ../src/*.gcda)
			$(RM) $(wildcard *.gcno)
			$(RM) $(wildcard *.gcda)

re	:	fclean all

.PHONY: all clean fclean re
