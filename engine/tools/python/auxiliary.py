import os

ENGINE_ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../'))
PROJECT_ROOT_DIR = os.path.join(ENGINE_ROOT_DIR, '../')
OUTPUT_DIR = os.path.join(PROJECT_ROOT_DIR, 'build/')
CMAKE_DIR = os.path.join(ENGINE_ROOT_DIR, 'tools/cmake/')

def is_tool_available(tool: str, mandatory: bool = True):
    from shutil import which
    result = which(tool.lower()) is not None

    if result == False and mandatory:
        raise Exception(f"{tool} is not available")

    return result
