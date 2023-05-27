.PHONY: all clean engine game menu questions-core questions-ui

all: engine game menu questions-core questions-ui

engine:
	make -C engine/

game: engine
	make -C game/

menu:
	make -C menu/

questions-core:
	make -C questions_core/

questions-ui: questions-core
	make -C questions_ui/

clean:
	make clean -C engine/
	make clean -C game/
	make clean -C menu/
	make clean -C questions_core/
	make clean -C questions_ui/
