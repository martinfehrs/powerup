# PowerUp!
A general-purpose header-only library extendending the C++14 standard library.

This library is completely standard library based. There are no further dependencies.
Currently this project is in an early development stage. There are only number ranges.
They can be found in the numranges.hpp header.

## Number ranges

### Description

There are two different number range types:

1. InclusiveRange
2. ExclusiveRange

Instead of constructing them directly, you should use one of the following factory functions:

1. inclusive_range
2. exclusive_range
3. index_range

The first two factories simply construct the the corresponding range type. The third
factory constructs an exclusive range for a container.

### Usage

#### Counted loop
Instead of using a traditional for loop, you can use exlusive_range. This allows to use of auto for the counting variable:

```c++
for(auto i : pup::exclusive_range(10))
{
  std::cout << i << ' ';
}
```
```
0 1 2 3 4 5 6 7 8 9
```
The inclusive range is neary identical. The only difference is, that the upper bound is included.

```c++
for(auto i : pup::inclusive_range(10))
{
  std::cout << i << ' ';
}
```
```
0 1 2 3 4 5 6 7 8 9 10
```
