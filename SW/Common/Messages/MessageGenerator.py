
import sys
import os
import subprocess

if __name__ == '__main__':
    filesToCompile = []

    for thisFile in filesToCompile:
        print("Compiling " + thisFile)
        subprocess.call(f"xsd {thisFile} -o .", shell=True)
        
    print("Done")