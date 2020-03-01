<h1 style="display:inline"><img style="display:inline" width="30px" src="https://github.com/martinfehrs/powerup/blob/master/res/Retro-Block-Exclamation-icon.png">&nbsp;PowerUp</h1>

A general-purpose header-only library extendending the C++14 standard library.

This library is completely standard library based. There are no further dependencies.
Currently this project is in an early development stage. There are only number ranges.
They can be found in the numranges.hpp header.

## Number ranges

### Description

There are two different number range types and a corresponding iterator type:

1. InclusiveRange
2. ExclusiveRange
3. RangeIterator

Most of the time you aren't using these types directly, but of the following factory functions:

1. inclusive_range
2. exclusive_range
3. index_range

The first two factories simply construct the the corresponding range type. The third
factory constructs a range of container indices.

### Usage

For the sake of convenience all the following examples show only exclusive_range and index_range,
because inclusive_range behaves like exclusive_range with the upper bound included.

#### Counted loop
Instead of using a traditional for loop, you can use exlusive_range. This allows to use of auto for
the counting variable:

```c++
for(auto i : pup::exclusive_range(10))
    std::cout << i << ' ';
```
```
0 1 2 3 4 5 6 7 8 9
```
If you want you can specify a lower bound:

```c++
for(auto i : pup::exclusive_range(1, 10))
    std::cout << i << ' ';
```
```
1 2 3 4 5 6 7 8 9
```
And you can specify a step size:
```c++
for(auto i : pup::exclusive_range(1, 10, 2))
    std::cout << i << ' ';
```
```
1 3 5 7 9
```
Finally you can count downwards:
```c++
for(auto i : pup::exclusive_range(10, 1, -2))
    std::cout << i << ' ';
```
```
10 8 6 4 2
```
Be careful! If you don't specify the step it defaults to 1. Because of this the following code
is invalid. It leads to an assertion as long as NDEBUG isn't defined. Otherwise it runs for a long
time, depending on the type's size:
```c++
for(auto i : pup::exclusive_range(10, 1))
    std::cout << i << ' ';
```
```
Assertion `step > 0 && last >= first || step < 0 && last <= first' failed
```
But what is the index's type? It has the same type as the passed in lower and upper bound. And what
if they have different types? They cannot. If the types aren't equal the code isn't compilable.
```c++
for(auto i : pup::exclusive_range('a', 10))
    std::cout << i << ' ';
```
```
error: no matching function for call to ‘inclusive_range(char, int)’
     for(const auto i : pup::inclusive_range('a', 10))
...
```
The step type can be different, but it isn't allowed to mix signed and unsigned types.
```c++
for(auto i : pup::exclusive_range(1, 10, 1U))
    std::cout << i << ' ';
```
```
error: no matching function for call to ‘inclusive_range(int, int, unsigned int)’
     for(const auto i : pup::inclusive_range(1, 10, 1U))
...
```
You can produces container indices while use exclusive_range:
```c++
std::vector<int> vec{ 1, 2, 3, 4, 5 };

for(auto i : pup::exclusive_range(vec.size())
    std::cout << i << ' ';
```
```
0 1 2 3 4
```
The same can be achieved with the shortcut index_range:
```c++
std::vector<int> vec{ 1, 2, 3, 4, 5 };

for(auto i : pup::index_range(vec))
    std::cout << i << ' ';
```
```
0 1 2 3 4
```
