from conans import ConanFile, CMake
from conans.tools import download, unzip


class CarrotConan(ConanFile):
    name = "carrot"
    version = "0.2.0"
    license = "BSL-1.0"
    url = "https://github.com/qubusproject/carrot"
    description = "A C++ library for rendering expressive diagnostic messages"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_paths"
    requires = "boost/1.73.0", "icu/64.2", "fmt/6.2.1"
    exports_sources = "../*"

    def configure(self):
        if self.settings.compiler != "Visual Studio" and not self.options["boost"].shared:
            self.options["boost"].fPIC = True

        self.options["icu"].data_packaging = "library"

    def build(self):
        cmake = CMake(self)

        cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = "conan_paths.cmake"
        cmake.definitions["CARROT_BUILD_TESTS"] = "True"

        cmake.configure(build_folder="./build")
        cmake.build()

        cmake.test()

        cmake.install()

    def package(self):
        pass

