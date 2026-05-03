import subprocess

class CMakeCommand:
    def __init__(self):
        self._command = ['cmake']

    def append(self, option: str):
        self._command.extend(option.split())
        return self

    def run(self):
        from auxiliary import PROJECT_ROOT_DIR
        import sys

        print(f"Running {self._command}", flush=True)

        output = subprocess.run(self._command,
                                cwd=PROJECT_ROOT_DIR,
                                capture_output=True,
                                text=True)

        if len(output.stdout) > 0:
            print(output.stdout, flush=True)

        if output.returncode == 0:
            print('\033[32mSuccess.\033[0m\n', flush=True)
        else:
            if len(output.stderr) > 0:
                print(output.stderr, flush=True)
            print(f'\033[31mError. Command returned: {output.returncode}.\n\033[0m', flush=True)

        return output
