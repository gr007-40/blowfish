clean:
	rm ./blow || echo $?
	rm file || echo $?
	rm key || echo $?

build: clean
	g++ src/main.cpp src/blowfish.cpp -o blow

test: build
	echo -n 'blow{fish_hsif}wolb' > file
	echo -n 'blowfish' > key
	xxd ./file
	./blow -m encrypt -k ./key -i ./file
	xxd ./file
	./blow -m decrypt -k ./key -i ./file
	xxd ./file
