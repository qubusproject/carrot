from conans import ConanFile, CMake
from conans.tools import download, unzip

class CarrotConan(ConanFile):
    name = "carrot"
    version = "0.2.0"
    license = "BSL-1.0"
    url = "https://github.com/qubusproject/carrot"
    description = "A C++ library for rendering expressive diagnostic messages"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package_multi"
    requires = "boost/1.74.0", "icu/67.1", "fmt/7.0.3"
    exports_sources = "../*"
    options = {"with_unicode": [True, False]}
    default_options = {"with_unicode": False}

    def configure(self):
        self.options["icu"].data_packaging = "library"

    def build(self):
        cmake = CMake(self)

        cmake.definitions["CARROT_BUILD_TESTS"] = "True"

        cmake.definitions["CARROT_WITH_UNICODE_SUPPORT"] = self.options["with_unicode"]

        cmake.configure(build_folder="./build")
        cmake.build()

        cmake.test()

        cmake.install()

    def package(self):
        pass

