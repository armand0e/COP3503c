make:
	g++ \
	-c src/*.cpp \
	-I/mnt/c/Users/aranr/SFML-2.5.1/include \
	-L/mnt/c/Users/aranr/SFML-2.5.1/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	--std=c++11 \
	-o sfml-app

run:
	./sfml-app config.cfg
clean:
	rm sfml-app
mac:
	g++ \
	-c src/*.cpp \
	-I/opt/homebrew/Cellar/sfml/2.6.1/include \
	-L/opt/homebrew/Cellar/sfml/2.6.1/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	--std=c++11 \
	-o sfml-app