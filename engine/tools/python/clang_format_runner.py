from auxiliary import *
from commands import CMakeCommand

class ClangFormatRunner:
    TOOL_NAME = "clang-format"
    SCRIPT_FILE_PATH = os.path.join(CMAKE_DIR, 'run_clang_format.cmake')

    def __init__(self):
        is_tool_available(ClangFormatRunner.TOOL_NAME)

        self.script_command = CMakeCommand().append(f"-P {ClangFormatRunner.SCRIPT_FILE_PATH}")
    
    def run(self):
        print(f"Executing clang format runner.", flush=True)
        self.script_command.run()
