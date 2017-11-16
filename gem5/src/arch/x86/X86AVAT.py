# Author: Yan Meng

from m5.params import *
from m5.proxy import *

from m5.SimObject import SimObject

class X86AVAT(SimObject):
    type = 'X86AVAT'
    cxx_class = 'ApproxComputing::Avat'
    cxx_header = 'arch/x86/avat.hh'
