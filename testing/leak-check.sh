gcc -Wall -Wextra -Werror -ggdb ./main.c -fsanitize=address -fno-omit-frame-pointer -L.. -lftprintf && ./a.out
