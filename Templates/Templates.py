"""Euler Problem Templates."""
import sys
from pathlib import Path

MAIN_PATH = "../EulerMain"
PROBLEM_PATH = "../EulerMain/Solutions"

INCLUDE_STR = '#include "Solutions/Problem{number:04d}.h"'
INIT_STR = '    m_pvProblemList.push_back(new Euler::Problem{number}());'


def write_problem(path, template, number):
    """Write template to target file."""
    template_file = None
    with open(template) as template_f:
        template_file = template_f.read()
    template_file = template_file.replace("{_number_}", str(number))
    template_file = template_file.replace("{_zero_number_}", "{number:04d}".format(number=number))
    with open(path.format(number=number), "w") as problem_f:
        problem_f.write(template_file)

def write_solution(path, number):
    """Write solutions header and cpp files.
    
    TODO: refactor to reuse the function for a single file,
          like the write_problem function.
    """
    # Start with header file
    template_file = None
    with open("Cpp/Problem_Includes.h") as solution_f:
        template_file = solution_f.read()
    # Generate a list of includes
    includes = []
    for problem_num in range(1, number + 1):
        includes.append(INCLUDE_STR.format(number=problem_num))
    with open(path + "/Problem_Includes.h", "w") as solution_f:
        solution_f.write(template_file.replace("{_solutions_}", "\n".join(includes)))
    # Now cpp file
    with open("Cpp/Solutions_Initialize.cpp") as solution_f:
        template_file = solution_f.read()
    # Generate a list of case
    cases = []
    for problem_num in range(1, number + 1):
        cases.append(INIT_STR.format(number=problem_num))
    with open(path + "/Solutions_Initialize.cpp", "w") as solution_f:
        solution_f.write(template_file.replace("{_solutions_}", "\n".join(cases)))

def display_help():
    """Display help text."""
    print("Usage: Template.py NUMBER")
    print("  -h, --help    Display this help text")
    print("")
    print("  NUMBER a new Project Euler problem number to generate.")

def main():
    """Create Problem files from template."""
    if not sys.argv[1:]:
        print("Please provide a problem number")
        return 1
    if sys.argv[1].startswith(("-h", "--help")):
        display_help()
        return 1
    # Convert problem number into an actual number
    try:
        number = int(sys.argv[1])
    except ValueError:
        print("Please provide a problem number")
        return 1

    """TODO: use a single template for `Problem{number:04d}' since
             it is used a lot.
    """

    # Check if files already exists to avoid overwritting and
    # propose a new number if already existent.
    target_file = Path(PROBLEM_PATH + "/Problem{number:04d}.h".format(number=number))
    if target_file.is_file():
        print("Files already exist for Problem{number:04d}".format(number=number))
        while target_file.is_file():
            number += 1
            target_file = Path(PROBLEM_PATH + "/Problem{number:04d}.h".format(number=number))
        user_choice = input("Perhaps generate Problem{number:04d}? (Y/n) ".format(number=number))
        if user_choice != 'Y':
            return 1

    # Now that we have a valid problem number, read templates and create files
    write_problem(PROBLEM_PATH + "/Problem{number:04d}.h", "Cpp/Problem.h", number)
    write_problem(PROBLEM_PATH + "/Problem{number:04d}.cpp", "Cpp/Problem.cpp", number)

    # Update the Solutions header/cpp to add the new problem
    write_solution(MAIN_PATH, number)

    print("Templates for problem {number} created.".format(number=number))


if __name__ == "__main__":
    sys.exit(main())
