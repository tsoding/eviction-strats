# Parallel Build Strategy Experiments

Results of the experiments from these sessions:

[![thumbnail-01](./thumbnail-01.png)](https://www.youtube.com/watch?v=nRwGKqU5na0)
[![thumbnail-02](./thumbnail-02.png)](https://www.youtube.com/watch?v=UZt2KnuxRm8)

This repo contains a modified version of [nob.h](https://github.com/tsoding/nob.h) which introduces various process eviction strategies to the asynchronous runner of the commands. The purpose of the repo is to measure how well different strategies perform.

![loopers](./results-at-markov/loopers.png)

## Quick Start

```console
$ cc -o nob nob.c
$ ./nob
```
