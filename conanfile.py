from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.microsoft import is_msvc, is_msvc_static_runtime, msvc_runtime_flag, VCVars
from collections import namedtuple
import os


class mumuRecipe(ConanFile):
    name = "mumu"
    version = "1.0.0"
    package_type = "library"

    # Optional metadata
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of mumu package here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "cmake/*", "module/*", "external/*"

    # 规定一个树方便导出包配置
    _LibComponent = namedtuple("_LibComponent",
                               # 几项分别是:对应conan的设置,默认值,内部依赖,外部依赖库,自己是否是lib
                               ("option", "default_option", "dependencies", "external_dependencies", "is_lib"))
    _lib_component_tree = {
        "World": _LibComponent(None, False, [], ["gtest::gtest"], True),
        # "Crypto": _LibComponent("enable_crypto", True, ["Utils"], [], True),
        # "Net": _LibComponent("enable_net", True, ["Utils"], [], True),
    }

    def log_work_fun(self, fun_name: str):
        # 记录输出一下函数名
        print("f{self.name}包conan脚本:conan进入:{fun_name}()函数,当前的python工作目录为={os.getcwd()}")

    def requirements(self):
        self.requires("gtest/1.14.0")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.log_work_fun("package_info")
        project_name = self.name
        # 使用默认的项目名来定义吧,注意核对
        self.cpp_info.set_property("cmake_file_name", f"{project_name}")
        self.cpp_info.set_property("cmake_target_name", f"{project_name}::{project_name}")

        self.cpp_info.filenames["cmake_find_package"] = f"{project_name}"
        self.cpp_info.filenames["cmake_find_package_multi"] = f"{project_name}"
        self.cpp_info.names["cmake_find_package"] = f"{project_name}"
        self.cpp_info.names["cmake_find_package_multi"] = f"{project_name}"

        suffix = msvc_runtime_flag(self).lower() \
            if is_msvc(self) and not self.options.shared \
            else ("d" if self.settings.build_type == "Debug" else "")

        # 使用默认的列表里面的default_option来导出库
        for compname, comp in self._lib_component_tree.items():
            if comp.option is None or comp.default_option is True:
                print(f"{project_name}导出包定义:{compname}")
                conan_component = f"{project_name}_{compname.lower()}"
                requires = [f"{project_name}_{dependency.lower()}" for dependency in
                            comp.dependencies] + comp.external_dependencies
                self.cpp_info.components[conan_component].set_property("cmake_target_name",
                                                                       f"{project_name}::{compname}")
                self.cpp_info.components[conan_component].set_property("cmake_file_name", compname)
                self.cpp_info.components[conan_component].names["cmake_find_package"] = compname
                self.cpp_info.components[conan_component].names["cmake_find_package_multi"] = compname
                if comp.is_lib:
                    self.cpp_info.components[conan_component].libs = [f"{project_name}{compname}{suffix}"]
                self.cpp_info.components[conan_component].requires = requires
        # self.cpp_info.libs = ["mumu"]
