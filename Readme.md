# Blowfish

<!--toc:start-->
- [Blowfish](#blowfish)
  - [Requirements](#requirements)
  - [Build](#build)
  - [Usage](#usage)
  - [Test](#test)
  - [Modification](#modification)
<!--toc:end-->

This repository contains my c++ implementation of the blowfish cipher algorithm.
This implementation is heavily motivated by [ddokkaebi](https://github.com/ddokkaebi/Blowfish)'s implementation of blowfish algorithm.

## Requirements
`git`
`g++`
`make`

## Build
Make sure the required packages are installed.
```sh
git clone https://github.com/gr007-40/blowfish.git
cd blowfish
make build
```

## Usage
```sh
❯ ./blow -h
Usage:
./blow -m <encrypt|decrypt> -k <key_file> -i <input_file>
-h : print this help message
-m : cipher mode [encrypt|decrypt]
-k : key filename
-i : input filename
```

## Test
```sh
❯ make test
rm ./blow
rm file
rm key
g++ src/main.cpp src/blowfish.cpp -o blow
echo -n 'blow{fish_hsif}wolb' > file
echo -n 'blowfish' > key
xxd ./file
00000000: 626c 6f77 7b66 6973 685f 6873 6966 7d77  blow{fish_hsif}w
00000010: 6f6c 62                                  olb
./blow -m encrypt -k ./key -i ./file
xxd ./file
00000000: da33 3454 b10e 45c6 3375 f418 fefd 49ae  .34T..E.3u....I.
00000010: 889a 9f70 3daa 6e8d                      ...p=.n.
./blow -m decrypt -k ./key -i ./file
xxd ./file
00000000: 626c 6f77 7b66 6973 685f 6873 6966 7d77  blow{fish_hsif}w
00000010: 6f6c 6200 0000 0000                      olb.....
```

## Modification

- Added padding with `0x00` at the end of plain text before encryption to make block size multiple of 64 bits.

