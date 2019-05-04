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

```rust
     May | *    Wander @Nowhere
     Apr | |
     Mar | |
     Feb |_|
2019 Jan |
     Dec |-*    Play Zelda @Texas
     Nov | |
     Oct | |
     Sep | |
     Aug | |-*  Pay Tax @California
     Jul | | |
     Jun | | |
     May | |_|
     Apr | |
     Mar | |
     Feb | |
2018 Jan | |
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
2017 Jan |
```

