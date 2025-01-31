from __future__ import annotations

from ._core import __doc__, __version__, add, subtract, loseIt, maxThreads, libxcversion, writeH5File
from .example import addOne, getCompliment

try:
    from ._core import binomial
except ImportError:
    binomial = None

__all__ = ["__doc__", "__version__", "add", "subtract", "loseIt", "maxThreads", "addOne", "getCompliment", "libxcversion", "writeH5File"]

if binomial is not None:
    __all__.append("binomial")