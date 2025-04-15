#!/usr/bin/env python
import os
import sys

env = SConscript("vendor/godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.

libname = "libgdexample"
...
def find_directories(directory):
    directories = ["src/"]
    for root, dirs, files in os.walk(directory):
        directories.extend(["src/" + os.path.relpath(os.path.join(root, d), directory).replace("\\", "/") + "/" for d in dirs])
    return directories

source_dirs = find_directories("src/")
env.Append(CPPPATH=source_dirs)
...
sources = []
for d in source_dirs:
    sources.append(Glob(d + "*.cpp"))

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "project/bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "project/bin/libgdexample.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "project/bin/libgdexample.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "project/bin/libgdexample{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
