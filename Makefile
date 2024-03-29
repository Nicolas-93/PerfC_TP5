CC=gcc
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
INCLUDE=-I$(INC_DIR)
LIBS=-lncursesw -lm
CFLAGS=-fdiagnostics-color=always -Wall -std=c17 -g -O0 # -Wno-unused-variable -Wno-unused-but-set-variable
TP_N=5
NOM_ZIP=TP$(TP_N)_SEBAN_POUYANFAR.zip
EXEC=main
CONTENU_ZIP=$(SRC_DIR) $(INC_DIR) .clang-format .clang-tidy Makefile rapport.pdf build/serpent.ini

SOURCES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(INC_DIR)/*.h)

# On récupère tous les fichiers sources .c, et on leurs préfixe
# le chemin de build, et suffixe en .o :
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
#$(info $(OBJS))

all: $(BUILD_DIR)/$(EXEC)

# Assemblage de l'exécutable final
$(BUILD_DIR)/$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Dépendances
main.o: main.c interface.h serpent.h monde.h temps.h ini_parser.h
interface.o: interface.c interface.h list.h types.h
serpent.o: serpent.c types.h list.h
monde.o: monde.c types.h serpent.h pomme.h list.h random.h
pomme.o: pomme.c types.h list.h
temps.o: temps.c temps.h
random.o : random.c random.h
ini_parser.o: ini_parser.c ini_parser.h

# Création des fichiers objets à partir des fichiers sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

rapport: rapport.pdf

rapport.pdf: rapport.md
	@mkdir --parents logos
	@wget --quiet --show-progress --no-clobber -O logos/LogoLIGM.png "https://drive.google.com/uc?export=download&confirm=yes&id=1cZjxS6Rwp8LU4Eyahqz0eUS8aH0_VrVB" || true
	@wget --quiet --show-progress --no-clobber -O logos/namedlogoUGE.png "https://drive.google.com/uc?export=download&confirm=yes&id=1YGm1N7griuDbJhC6rSgBHrrcOsHKM5xg" || true
	pandoc --toc rapport.md -o rapport.pdf

format: $(SOURCES) $(HEADERS)
	clang-format -i --style=file $^
	clang-tidy --fix $^

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(BUILD_DIR)/$(EXEC)
	rm -f $(NOM_ZIP)

zip:
	zip -FSr $(NOM_ZIP) $(CONTENU_ZIP)

rendu:
	@$(MAKE) --no-print-directory rapport
	@$(MAKE) --no-print-directory zip

.PHONY: clean all
