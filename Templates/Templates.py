"""Euler Problem Templates."""
import sys
from pathlib import Path
from string import Template

def display_help():
    """Display help text."""
    print("Usage: Template.py [--dry-run] NUMBER")
    print("  -h, --help     Display this help text")
    print("      --dry-run  Execute but do not copy files.")
    print("")
    print("  NUMBER a new Project Euler problem number to generate.")

class EulerTemplate:
    """Euler template."""
    def __init__(self, filename):
        with open(filename, "r") as file_f:
            self.template = Template(file_f.read())
        self.text = ""

    def replace(self, arguments):
        """Substitute templates with arguments.

        param: arguments dictionary matching the template variables.
        """
        self.text = self.template.substitute(arguments)

    def write(self, filename):
        """Write new template to file."""
        with open(filename, "w") as file_f:
            file_f.write(self.text)

    def show(self):
        """Show output to STDOUT."""
        print(self.text)


class Application:
    """"Application for templates."""

    MAIN_PATH = "../EulerMain"
    PROBLEM_PATH = "../EulerMain/Solutions"

    def __init__(self):
        self.dry_run = False
        self.number = 0
        self.problem_name = "Problem{:04d}"
        self.target_name = Application.PROBLEM_PATH + "/" + self.problem_name

    def parse_args(self, arguments):
        """Parse command line arguments."""
        while arguments:
            argument = arguments[0]
            arguments.pop(0)
            if argument.startswith(("-h", "--help")):
                display_help()
                return False
            if argument.startswith("--dry-run"):
                self.dry_run = True
            else:
                try:
                    self.number = int(argument)
                except ValueError:
                    print("Please provide a problem number")
                    return False
        return True

    def run(self):
        """Run application."""
        if not self.parse_args(sys.argv[1:]):
            return False
        # Target file
        if self.exists_target_file():
            return False
        # Write template files to destination
        self.write_problem()
        self.write_problem_includes()
        self.write_solutions_initialization()
        print("Templates for problem {number} created.".format(number=self.number))

    def exists_target_file(self):
        """Verify if target file already exists.

        When target file exists, propose a new problem number.
        """
        header_name = self.target_name + ".h"
        target_file = Path(header_name.format(self.number))
        if target_file.is_file():
            print("Files already exist for " + self.problem_name.format(self.number))
            while target_file.is_file():
                self.number += 1
                target_file = Path(header_name.format(self.number))
            user_choice = input("Perhaps generate " +
                                self.problem_name.format(self.number) +
                                "? (Y/n) ")
            if user_choice != 'Y':
                return True
        self.problem_name.format(self.number)
        self.target_name.format(self.number)
        return False

    def write_problem(self):
        """Write problem files."""
        problem_keys = {
            "problem_num": self.number,
            "problem_znum": "{:04d}".format(self.number)
        }
        filenames = [
            "Cpp/Problem.h",
            "Cpp/Problem.cpp"
        ]
        outputs = [
            self.PROBLEM_PATH + self.problem_name + ".h",
            self.PROBLEM_PATH + self.problem_name + ".cpp"
        ]
        self.write_template(filenames, outputs, problem_keys)

    def write_problem_includes(self):
        """Write problem includes file."""
        problem_incl_list = ['#include "Solutions/Problem{:04d}.h"'.format(number)
                             for number in range(1, self.number + 1)]
        problem_incl_keys = {"problem_incl": "\n".join(problem_incl_list)}
        filenames = ["Cpp/Problem_Includes.h"]
        outputs = [self.MAIN_PATH + "/Problem_Includes.h"]
        self.write_template(filenames, outputs, problem_incl_keys)

    def write_solutions_initialization(self):
        """Write solution initialization source file."""
        problem_new = '    m_pvProblemList.push_back(new Euler::Problem{:d}());'
        problem_new_list = [problem_new.format(number)
                            for number in range(1, self.number + 1)]
        problem_new_keys = {"problem_new": "\n".join(problem_new_list)}
        filenames = ["Cpp/Solutions_Initialize.cpp"]
        outputs = [self.MAIN_PATH + "/Solutions_Initialize.cpp"]
        self.write_template(filenames, outputs, problem_new_keys)

    def write_template(self, input_files, output_files, keys):
        """Write a template."""
        for input_file, output_file in zip(input_files, output_files):
            template = EulerTemplate(input_file)
            template.replace(keys)
            if not self.dry_run:
                template.write(output_file)
            else:
                template.show()


def main():
    """Run main application."""
    app = Application()
    return app.run()

if __name__ == "__main__":
    sys.exit(main())
