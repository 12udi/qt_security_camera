from conans import ConanFile, CMake

class QtConan(ConanFile):
    name = "qt-conan"
    settings = "os", "compiler", "build_type", "arch"

    requires = "qt/6.4.1"
    default_options = {"qt:shared": True,
                       "qt:qtdeclarative": True,
                       "qt:qtshadertools": True
                       }

    generators = "cmake_find_package", "cmake_paths"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
