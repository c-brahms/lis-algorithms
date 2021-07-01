# lis-algorithms

This repository contains algorithm implementations for the following paper:

* Antti Laaksonen & Kjell Lemström: [Discovering distorted repeating patterns in polyphonic music through longest increasing subsequences](https://doi.org/10.1080/17459737.2021.1896811) (Journal of Mathematics and Music, 2021)

The file algo.cpp implements the unrestricted and windowed time-warp invariant algorithm, and the file exact.cpp implements the exact algorithm. The file test.in contains a small example data set.

The algorithms assume that the first input line has an integer `n`: the number of notes. After that, there are `n` lines each of which describes a note. Each line has two integers `t` and `p`: the onset time of a note is `t` and the pitch is `p`.
