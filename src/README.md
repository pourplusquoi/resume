# Timeline Generator

Helps to generate "git-branch" like timeline from your experience. The format of input is illustrated in `sample.experience`.

## Usage

In case you want to use it.

```
user$ cd ${parent-dir}/src
user$ make
user$ ./timeline-gen sample.experience [output.timeline]
```

## TODO

- Cuts off timeline that is too long.

## Sample Timeline

```
         |   *          Sleep @Home
     May | * |          Sleep @Home
     Apr | | |
     Mar | |_|
     Feb |_|
2019 Jan |-----------*  Replace Driving Lisence @DMV
         |---*       |  Watch European Champions League @Fondren
     Dec |-* |       |  Play Breath of The Wild @RMC
     Nov | | |       |
     Oct | | |-----*_|  Swim swim swim @IMT
     Sep | | |     |
     Aug | | |---* |    Pay Thousands of Tax @IRS
     Jul | | |   |_|
     Jun | | |   |
     May | | |-*_|      Eat Panda Express @RVA
     Apr | | | |
     Mar | | | |
     Feb | |_| |
2018 Jan | |   |
     Dec | |   |
     Nov | |___|
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

