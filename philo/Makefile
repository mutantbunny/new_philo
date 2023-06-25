CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lpthread
RM = rm -rf

MANDATORY_DIR = .
NAME = ${MANDATORY_DIR}/philo
INC_DIR = ${MANDATORY_DIR}/inc
INC_FILES = ${INC_DIR}/philo.h
SRC_DIR = ${MANDATORY_DIR}/src
SRC_FILES = ${addprefix ${SRC_DIR}/, checker_thread.c cleanup.c ft_atoi.c init.c}
SRC_FILES += ${addprefix ${SRC_DIR}/, mutex_ops.c philo_thread.c philo.c time.c utils.c}
OBJ_DIR = ${MANDATORY_DIR}/obj
OBJ_FILES = ${addprefix ${OBJ_DIR}/, ${notdir ${SRC_FILES:.c=.o}}}

all: ${NAME}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${NAME}: ${OBJ_FILES}
	${CC} ${CFLAGS} ${OBJ_FILES} ${LIBFLAGS} -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INC_FILES} | ${OBJ_DIR}
	${CC} ${CFLAGS} -I${INC_DIR} -c $< -o $@

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
