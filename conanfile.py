import os

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
from conan.tools.env import Environment
from conan.tools.env.environment import EnvVars
from conan.tools.files import copy


class OpenDocumentCoreConan(ConanFile):
    name = "odrcore"
    version = ""
    url = "https://github.com/opendocument-app/OpenDocument.core"
    homepage = "https://opendocument.app/"
    description = "C++ library that translates office documents to HTML"
    topics = "open document", "openoffice xml", "open document reader"
    license = "GPL 3.0"

    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_pdf2htmlEX": [True, False],
        "with_wvWare": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }

    def requirements(self):
        self.requires("pugixml/1.14")
        self.requires("cryptopp/8.9.0")
        self.requires("miniz/3.0.2")
        self.requires("nlohmann_json/3.11.3")
        self.requires("vincentlaucsb-csv-parser/2.3.0")
        self.requires("uchardet/0.0.8")
        self.requires("utfcpp/4.0.4")
        if self.options.get_safe("with_pdf2htmlEX"):
            self.requires("pdf2htmlex/0.18.8.rc1-20240814-git")
        if self.options.get_safe("with_wvWare"):
            self.requires("wvware/1.2.9")

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")

    def validate_build(self):
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, 20)

    exports_sources = ["cli/*", "cmake/*", "src/*", "CMakeLists.txt"]

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

        self.options.with_pdf2htmlEX = self.settings.os not in ["Windows", "Macos"]
        self.options.with_wvWare = self.settings.os != "Windows"

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_PROJECT_VERSION"] = self.version
        tc.variables["ODR_TEST"] = False
        tc.variables["WITH_PDF2HTMLEX"] = self.options.get_safe("with_pdf2htmlEX", False)
        tc.variables["WITH_WVWARE"] = self.options.get_safe("with_wvWare", False)

        # Get runenv info, exported by package_info() of dependencies
        # We need to obtain PDF2HTMLEX_DATA_DIR, POPPLER_DATA_DIR, FONTCONFIG_PATH and WVDATADIR
        runenv_info = Environment()
        deps = self.dependencies.host.topological_sort
        deps = [dep for dep in reversed(deps.values())]
        for dep in deps:
            runenv_info.compose_env(dep.runenv_info)
        envvars = runenv_info.vars(self)
        for v in ["PDF2HTMLEX_DATA_DIR", "POPPLER_DATA_DIR", "FONTCONFIG_PATH", "WVDATADIR"]:
            tc.variables[v] = envvars.get(v)

        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["odr"]
