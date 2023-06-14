# Tests

As testing framework used (latest at the moment of implementing tests)
[`doctest v2.4.11`](https://github.com/doctest/doctest/releases/tag/v2.4.11)

Previously tests was written by using
[`Catch2`](https://github.com/catchorg/Catch2), but it has the next disadvantes:
- From version `3.x` it requires `C++14`, so latest `C++11` compatible version is
  [v2.13.9](https://github.com/catchorg/Catch2/releases/tag/v2.13.9)
- From version `3.x` it distributed as header + source, instead of single-header
- It has lack of 'Check with message' - see https://github.com/catchorg/Catch2/issues/929
