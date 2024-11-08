# Example Package

This is a simple example package. You can use
[GitHub-flavored Markdown](https://guides.github.com/features/mastering-markdown/)
to write your content.

`example` and `_core` are two submodules of `example_package_JonSnowPatrol`. Example usage:

```
from example_package_JonSnowPatrol import _core as core
from example_package_JonSnowPatrol import example as ex

ex.get_compliment()
core.loseIt()
core.maxThreads()
```

or alternatively
```
from example_package_JonSnowPatrol() import *
get_compliment()
loseIt()
maxThreads()
```

Requirements are pybind11, OpenMP and now also Boost.