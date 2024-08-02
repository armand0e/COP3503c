build:
	g++ -c src/*.cpp \
	-I/mnt/Users/aranr/OneDrive/Documents/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/include \
	-L/mnt/Users/aranr/OneDrive/Documents/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	--std=c++11 \
	-o sfml-app
win:
	g++ -c src/*.cpp \
	-I"C:\Users\aranr\OneDrive\Documents\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include" \
	-L"C:\Users\aranr\OneDrive\Documents\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib" \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	--std=c++11 \
	-o sfml-app.exe
win_run:
	sfml-app.exe config.cfg
win_clean:
	del sfml-app.exe
run:
	./sfml-app config.cfg
clean:
	rm sfml-app
mac:
	g++ -c src/*.cpp \
	-I/opt/homebrew/Cellar/sfml/2.6.1/include \
	-L/opt/homebrew/Cellar/sfml/2.6.1/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	--std=c++11 \
	-o sfml-app