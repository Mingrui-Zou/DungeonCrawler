CXX=g++
XXFLAGS=-Wall -MMD
EXEC=cc3k
OBJECTS=cc3k.o wlinefill.o map.o displaymap.o chamber.o gameobject.o cell.o floor.o wall.o passage.o door.o stair.o character.o potion.o restorehealth.o poison.o boostatk.o woundatk.o boostdef.o wounddef.o player.o human.o elf.o dwarf.o ork.o npc.o goblin.o vampire.o werewolf.o troll.o phoenix.o merchant.o owlbear.o dragon.o treasure.o dragonhoard.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC} -lncurses
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC}
