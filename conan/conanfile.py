from conans import ConanFile, CMake
from conans.tools import download, unzip

class CarrotConan(ConanFile):
    name = "carrot"
    version = "0.2.0"
    license = "BSL-1.0"
    url = "https://github.com/qubusproject/carrot"
    description = "A C++ library for rendering expressive diagnostic messages"
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    generators = "cmake_paths"
    build_requires = "gtest/1.9.0@qubusproject/dev"
    requires = "boost/1.67.0@qubusproject/stable"

    def configure(self):
        if self.settings.compiler != "Visual Studio" and not self.options["boost"].shared:
            self.options["boost"].fPIC = True

    def build(self):
        cmake = CMake(self)

        cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = "conan_paths.cmake"

        cmake.configure(source_folder=".")
        cmake.build()

        cmake.install()

    def package(self):
        pass

