from conans import ConanFile

class ValuePtrLiteConan(ConanFile):
    version = "0.1.0"
    name = "value-ptr-lite"
    description = "A C++ smart-pointer with value semantics for C++98, C++11 and later"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/value-ptr-lite.git"
    exports_sources = "include/nonstd/*", "LICENSE.txt"
    build_policy = "missing"    
    author = "Martin Moene"

    def package_info(self):
        self.info.header_only()
