import os
import argparse


if __name__ == '__main__':
    presentWorkDir = os.getcwd()
    oldPwdDir = os.environ.get('OLDPWD')
    fileDir = os.path.dirname(os.path.realpath(__file__))

    baseOutputdir = fileDir + "/../run/output"

    parser = argparse.ArgumentParser(description='Run the simulation')
    parser.add_argument('-o', '--output', dest='outputDir', action='store', help='Output directory', default="0")
    parser.add_argument('-d', '--debug', dest='debugger', action='store', help='Run with debugger', default=None)

    args = parser.parse_args()

    outputDir = os.path.abspath(os.path.join(baseOutputdir, args.outputDir))

    if not os.path.isdir(outputDir):
        os.makedirs(outputDir)

    print("Output directory: " + outputDir)

    os.chdir(outputDir)

    print ("Running simulation")

    executable = fileDir + "/../bin/runner"

    # test
    
    if args.debugger == "valgrind":
        os.system("valgrind --leak-check=full -s " + executable)

    elif args.debugger == "gdb":
        os.system("gdb " + executable)

    elif args.debugger is None:
        os.system(executable)

    else:
        print("Unknown debugger: " + args.debugger)

    os.chdir(presentWorkDir)

    if oldPwdDir is not None:
        os.environ['OLDPWD'] = oldPwdDir