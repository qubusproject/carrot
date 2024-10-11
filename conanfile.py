from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout

class CarrotConan(ConanFile):
    name = "carrot"
    version = "0.3.0"
    license = "BSL-1.0"
    url = "https://github.com/qubusproject/carrot"
    description = "A C++ library for rendering expressive diagnostic messages"
    settings = "os", "compiler", "build_type", "arch"
    requires = "boost/[>=1.86]", "icu/[~75]", "fmt/[~11]"
    test_requires = "catch2/3.7.1"
    exports_sources = "src/*", "tests/*", "examples/*", "doc/*", "cmake/*", "CMakeLists.txt", "README.md", "LICENSE"
    options = {"with_unicode": [True, False]}
    default_options = {"with_unicode": False}

    def configure(self):
        self.options["icu"].data_packaging = "library"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CARROT_BUILD_TESTS"] = "True"
        tc.variables["CARROT_WITH_UNICODE_SUPPORT"] = self.options["with_unicode"]
        tc.generate()

        deps = CMakeDeps(self)
        deps.build_context_activated = ["catch2"]
        deps.generate()

    def build(self):
        cmake = CMake(self)

        cmake.configure()
        cmake.build()

        cmake.install()

    def layout(self):
        cmake_layout(self)

    def package(self):
        pass
