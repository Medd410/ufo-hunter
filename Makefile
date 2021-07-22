ufohunter : main.o game.o entity_list.o entity.o
	gcc main.o game.o entity_list.o entity.o -lSDL2 -lSDL2_ttf -lSDL2_image -o ufohunter
main.o : main.c game.h
	gcc -c main.c
game.o : game.c game.h entity_list.o entity.o
	gcc -c game.c
entity_list.o : entity_list.c entity_list.h entity.o
	gcc -c entity_list.c
entity.o : entity.c entity.h
	gcc -c entity.c
