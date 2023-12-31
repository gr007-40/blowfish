clean:
	rm -rf ./blow

build: clean
	g++ src/main.cpp src/blowfish.cpp -o blow

test: build
	xxd ./file
	./blow -m encrypt -k ./key -i ./file
	xxd ./file
	./blow -m decrypt -k ./key -i ./file
	xxd ./file
