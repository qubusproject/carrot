from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class CarrotConan(ConanFile):
    name = "carrot"
    version = "0.3.0"
    license = "BSL-1.0"
    url = "https://github.com/qubusproject/carrot"
    description = "A C++ library for rendering expressive diagnostic messages"
    settings = "os", "compiler", "build_type", "arch"
    requires = "boost/1.86.0", "icu/[~75]", "fmt/[~11]"
    exports_sources = "../*"
    generators = "CMakeDeps", "CMakeToolchain"
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

        cmake.install()

    def layout(self):
        cmake_layout(self)

    def package(self):
        pass
