build:
	g++ src/*.cpp \
	-I/opt/homebrew/Cellar/sfml/2.6.1/include \
	-L/opt/homebrew/Cellar/sfml/2.6.1/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	--std=c++11 \
	-o sfml-app
run:
	./sfml-app config.cfg
clean:
	rm sfml-app
