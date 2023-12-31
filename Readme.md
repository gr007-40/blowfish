# Blowfish

<!--toc:start-->
- [Blowfish](#blowfish)
  - [Requirements](#requirements)
  - [Build](#build)
  - [Usage](#usage)
  - [Test](#test)
  - [Limitation](#limitation)
  - [TODO](#todo)
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
./blow -h : print this help message
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
00000010: 6f6c 62                                  olb
./blow -m decrypt -k ./key -i ./file
xxd ./file
00000000: 626c 6f77 7b66 6973 685f 6873 6966 7d77  blow{fish_hsif}w
00000010: 6f6c 62                                  olb
```

## Limitation

This implementation does not pad the input to be multiple of 64 bits.
So the leftover block which cannot be made into a block is ignored both while encrypting and decrypting.

## TODO

- Add padding to input before encrypting
- Remove padding from output after decrypting
