from auxiliary import *
from commands import CMakeCommand


class ClangTidyRunner:
    PRESET_NAME = 'ninja-clang-cl'
    TOOL_NAME = 'clang-tidy'

    BUILD_DIR = os.path.join(OUTPUT_DIR, 'build_clang_tidy/')
    SCRIPT_FILE_PATH = os.path.join(CMAKE_DIR, 'run_clang_tidy.cmake')

    def __init__(self):
        is_tool_available(ClangTidyRunner.TOOL_NAME)

        self.configure_command = CMakeCommand() \
            .append(f"--preset {ClangTidyRunner.PRESET_NAME}") \
            .append(f"-B {ClangTidyRunner.BUILD_DIR}") \
            .append(f"-DCMAKE_EXPORT_COMPILE_COMMANDS=ON") \
            .append(f"-DCMAKE_BUILD_TYPE=DebugEditor") \
            .append(f"-DBUILD_CLANG_TIDY=ON") 

        self.script_command = CMakeCommand() \
            .append(f"-DPROJECT_BINARY_DIR={ClangTidyRunner.BUILD_DIR}") \
            .append(f"-P {ClangTidyRunner.SCRIPT_FILE_PATH}")

    @staticmethod
    def _prepare_compile_commands_file():
        compile_commands_filepath = os.path.join(ClangTidyRunner.BUILD_DIR, 'compile_commands.json')

        with open(compile_commands_filepath, 'r') as file:
            data = file.read()

        from re import sub
        modified_data = sub(r"(-I)([^ ]*third_party[/\\][^ ]*)", r"/imsvc \2", data)

        with open(compile_commands_filepath, 'w') as file:
            file.write(modified_data)

    def run(self):
        self.configure_command.run()
        self._prepare_compile_commands_file()
        self.script_command.run()
