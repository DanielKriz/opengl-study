import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class OpenGLStudy(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeDeps', 'CMakeToolchain'

    def requirements(self):
        self.requires('fmt/10.2.1')
        self.requires('pulseaudio/17.0', override=True)
        self.requires('sdl/[~2.30]', override=True)
        self.requires('imgui/[~1]')
        self.requires('glfw/3.3.8')
        self.requires('freeglut/3.4.0')
        self.requires('argparse/2.9')
        self.requires('gsl-lite/0.41.0')
        self.requires('doctest/2.4.11')
        self.requires('spdlog/1.12.0')
        self.requires('sdl_image/2.6.3')
        self.requires('ktx/4.3.2')
        # Use this for entity component system
        # self.requires('flecs/3.2.11')
        # This needs an update
        # self.requires('joltphysics/3.0.1')

    def configure(self):
        self.options["sdl"].pulse = False

    def generate(self):
        copy(
            self,
            '*glfw*',
            os.path.join(
                self.dependencies['imgui'].package_folder,
                'res',
                'bindings'
            ),
            os.path.join(self.source_folder, 'build', 'bindings'))
        copy(
            self,
            '*opengl3*',
            os.path.join(
                self.dependencies['imgui'].package_folder,
                'res',
                'bindings'
            ),
            os.path.join(self.source_folder, 'build', 'bindings'))
        copy(
            self,
            '*sdl2*',
            os.path.join(
                self.dependencies['imgui'].package_folder,
                'res',
                'bindings'
            ),
            os.path.join(self.source_folder, 'build', 'bindings'))
        copy(
            self,
            '*sdlrenderer2*',
            os.path.join(
                self.dependencies['imgui'].package_folder,
                'res',
                'bindings'
            ),
            os.path.join(self.source_folder, 'build', 'bindings'))

    def layout(self):
        cmake_layout(self)
