import os
import sys
import argparse


if __name__ == '__main__':
    presentWorkDir = os.getcwd()
    oldPwdDir = os.environ.get('OLDPWD')
    fileDir = os.path.dirname(os.path.realpath(__file__))

    baseOutputdir = fileDir + "/../run/output"

    buildMode = "Release"

    parser = argparse.ArgumentParser(description='Run the simulation')
    parser.add_argument('-o', '--output', dest='outputDir', action='store', help='Output directory', default="0")
    parser.add_argument('-d', '--debug', dest='debug', action='store_true', help='Run with gdb', default=False)

    args = parser.parse_args()

    outputDir = os.path.join(baseOutputdir, args.outputDir)

    if not os.path.isdir(outputDir):
        os.makedirs(outputDir)

    os.chdir(outputDir)

    if args.debug:
        os.system("gdb " + fileDir + "/../config/exec/runnerLink")
    else:
        print ("Running simulation")
        os.system(fileDir + "/../config/exec/runnerLink")

    os.chdir(presentWorkDir)

    if oldPwdDir is not None:
        os.environ['OLDPWD'] = oldPwdDir