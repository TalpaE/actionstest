# Example Package

This is a simple example package. You can use
[GitHub-flavored Markdown](https://guides.github.com/features/mastering-markdown/)
to write your content.

Now with more C++ dependencies!

If you don't have scikit-build-core installed, do `pip install -i https://test.pypi.org/simple/ --extra-index-url https://pypi.org/simple example-package-JonSnowPatrol`

`example` and `_core` are two submodules of `example_package_JonSnowPatrol`. Example usage:

```
from example_package_JonSnowPatrol import _core as core
from example_package_JonSnowPatrol import example as ex

ex.getCompliment()
core.loseIt()
core.maxThreads()
```

or alternatively
```
from example_package_JonSnowPatrol() import *
getCompliment()
loseIt()
maxThreads()
libxcversion()
writeH5File("myFile")
```

Requirements are pybind11, OpenMP and now also Boost.