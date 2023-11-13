"""Conanfile for LRU cache"""
from conans import CMake, ConanFile

class LRUCache(ConanFile):
    """LRU Cache Conan Class"""
    name = "LRUCache"
    author = "Andrew Hayman"
    url = ""
    description = "A C++11 LRU cache"
    settings = "os", "compiler", "build_type", "arch"
    requires = ()
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {
        "shared": False,
        "fPIC": True,
        "gtest:shared": False,
    }

    scm = {"type": "git", "url": "auto", "revision": "auto", "submodule": "recursive"}
    generators = "cmake_find_package"

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure(source_folder=self.source_folder, build_folder=self.build_folder)
        return cmake
  
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build_requirements(self):
        self.build_requires("gtest/1.13.0")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
