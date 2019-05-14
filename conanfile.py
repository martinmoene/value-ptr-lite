from conans import ConanFile, CMake

class ValuePtrLiteConan(ConanFile):
    version = "0.2.1"
    name = "value-ptr-lite"
    description = "A C++ smart-pointer with value semantics for C++98, C++11 and later"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/value-ptr-lite.git"
    exports_sources = "include/nonstd/*", "CMakeLists.txt", "cmake/*", "LICENSE.txt"
    settings = "compiler", "build_type", "arch"
    build_policy = "missing"
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Run CMake install"""
        cmake = CMake(self)
        cmake.definitions["VALUE_PTR_LITE_OPT_BUILD_TESTS"] = "OFF"
        cmake.definitions["VALUE_PTR_LITE_OPT_BUILD_EXAMPLES"] = "OFF"
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.info.header_only()
