# Timeline Generator

Helps to generate "git-branch" like timeline from your experience. Sample code is in `main.cc`.

## Usage

In case you want to use it.

```
user$ cd ${parent-dir}/src
user$ make
user$ ./timeline-gen
```

## TODO

- Cuts off timeline that is too long.

- Supports reading experience from file, writting timeline to file (or stdout).

## Sample Timeline

```
         |   *            5  Sleep @Home
     May | * |            4  Sleep @Home
     Apr | | |
     Mar | | |
     Feb |_|_|
2019 Jan |-----*          7 Play Zelda @Texas
     Dec |-*   |          8 Play Zelda @Texas
     Nov | |   |
     Oct | |   |
         | |   |-------*  2  Pay Tax @California
     Sep | |-* |       |  6  Play Zelda @Texas
         | | | |-----* |  1  Pay Tax @California
     Aug | | |_|---* | |  0  Pay Tax @California
     Jul | | |---* | | |  3  Pay Tax @California
     Jun | | |   | | |_|
     May | | |-* |_|_|    9 Test @Production
     Apr | | | |_|
     Mar | |_| |
     Feb | |   |
2018 Jan | |___|
     Dec | |
     Nov | |
     Oct | |
     Sep | |
     Aug | |
     Jul | |
     Jun | |
     May | |
     Apr | |
     Mar | |
     Feb | |
2017 Jan | |
     Dec | |
     Nov | |
     Oct | |
     Sep | |
     Aug |_|
     Jul |
     Jun |
     May |
     Apr |
     Mar |
     Feb |
2016 Jan |
```

