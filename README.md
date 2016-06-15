# trmclr
A [130 lines header](https://github.com/matovitch/trmclr/blob/master/trmclr.hpp) for coloring your terminal outputs

## Example

```c++
#include "trmclr.hpp"
#include <iostream>

int main()
{
    trmclr::Style fancyStyle(trmclr::Background::LIGHT_BLUE    |
                             trmclr::Foreground::WHITE         |
                             trmclr::Attribute::UNDERLINED     |
                             trmclr::Attribute::BOLD);

    trmclr::Style basicStyle(trmclr::Attribute::DEFAULT);

    std::cout << fancyStyle << "Hello " 
              << basicStyle << "World!" << std::endl;

    return 0;
}

/*
Note you can also do things like: 
auto bold = [](trmclr::Style style) { return trmclr::Style(style | trmclr::Attribute::BOLD); };
*/
```
