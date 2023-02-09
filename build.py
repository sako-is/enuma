import fnmatch,os, sys
from pathlib import Path

cc = "clang"
cflags = "-std=gnu18 -g"
include = f"-Iengine/ -I{os.environ['VULKAN_SDK']}\\Include\\ -I{os.environ['GLFW']}\\include"
libs = f"-L{os.environ['VULKAN_SDK']}\\Lib\\ -lvulkan-1 -L{os.environ['GLFW']}\\build\\src\\Release\\ -lglfw3dll"
defines = "-DENM_EXPORT" # -D_CRT_SECURE_NO_WARNINGS 

files = ""
for root, dirnames, filenames in os.walk('engine'):
    for filename in fnmatch.filter(filenames, '*.c'):
        files+= ".\\" + os.path.join(root, filename) + " "

print(f'{cc} {cflags} {include} {libs} {defines} {files}-o  bin\enuma.exe')

os.system(f'{cc} {cflags} {include} {libs} {defines} {files} -o bin\enuma.exe')