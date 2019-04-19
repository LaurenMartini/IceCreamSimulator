#!/bin/sh
make -C /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/CMakeScripts/glfw_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
