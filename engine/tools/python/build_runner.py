from auxiliary import *
from commands import CMakeCommand
from typing import NamedTuple

class Config(NamedTuple):
    generator: str
    c_compiler: str
    cxx_compiler: str
    build_type: str

class BuildRunner:
    CONFIGS = [Config(generator='Ninja', c_compiler='clang', cxx_compiler='clang++', build_type='Debug'),
               Config(generator='Ninja', c_compiler='clang', cxx_compiler='clang++', build_type='Release')]

    def __init__(self):
        self.arguments = []

        for config in BuildRunner.CONFIGS:
            skip = (
                    not is_tool_available(config.generator, mandatory=False)
                    or not is_tool_available(config.c_compiler, mandatory=False)
                    or not is_tool_available(config.cxx_compiler, mandatory=False)
            )

            if skip:
                continue

            config_postfix = f"{config.c_compiler}_{config.build_type.lower()}"
            build_dir = os.path.join(OUTPUT_DIR, f"build_{config_postfix}")

            argument = {'configure_command': CMakeCommand(),
                        'build_command': CMakeCommand() }
            
            argument['configure_command'].append(f"-S .")\
                                         .append(f"-B {build_dir}")\
                                         .append(f"-G {config.generator}")\
                                         .append(f"-DCMAKE_C_COMPILER={config.c_compiler}")\
                                         .append(f"-DCMAKE_CXX_COMPILER={config.cxx_compiler}")\
                                         .append(f"-DCMAKE_BUILD_TYPE={config.build_type}")

            argument['build_command'].append(f"--build {build_dir}")\
                                     .append(f"--parallel")

            self.arguments.append(argument)

        if not self.arguments:
            raise Exception('Cannot execute any of the configurations.')
                
    def run(self):
        for argument in self.arguments:
            argument['configure_command'].run()
            
            argument['build_command'].run()
