# Blowfish

<!--toc:start-->
- [Blowfish](#blowfish)
  - [Requirements](#requirements)
  - [Build](#build)
  - [Usage](#usage)
  - [Test](#test)
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
rm -rf ./blow
g++ src/main.cpp src/blowfish.cpp -o blow
xxd ./file
00000000: 626c 6f77 7b66 6973 685f 6873 6966 7d77  blow{fish_hsif}w
00000010: 6f6c 62                                  olb
./blow -m encrypt -k ./key -i ./file
xxd ./file
00000000: 2fb6 7d0b 0afb 1144 44b8 e6d5 c2b1 6490  /.}....DD.....d.
00000010: 8160 9379 8d0a 0a6e                      .`.y...n
./blow -m decrypt -k ./key -i ./file
xxd ./file
00000000: 626c 6f77 7b66 6973 685f 6873 6966 7d77  blow{fish_hsif}w
00000010: 6f6c 62                                  olb
```

## Modification

- Added padding with `0x00` at the end of plain text before encryption to make block size multiple of 64 bits.
- Removes all `0x00` at the end of cipher text after decryption assuming it to be padding.

## Limitation

- If the end of the plain text contains `0x00` it will be removed as padding after decryption even though it should not be removed.

## TODO

- Fix the limitation.

