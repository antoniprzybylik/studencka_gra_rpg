.PHONY: all clean engine game menu questions-core questions-ui application

all: engine game menu questions-core questions-ui | application

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

application:
	rm -rf application
	mkdir application
	mkdir application/bin
	mkdir application/rc
	cp menu/menu-app application/
	cp menu/rc/* application/rc/
	cp game/game application/bin/

clean:
	make clean -C engine/
	make clean -C game/
	make clean -C menu/
	make clean -C questions_core/
	make clean -C questions_ui/
	rm -rf application
