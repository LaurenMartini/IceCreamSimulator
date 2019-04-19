# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.glfw.Debug:
PostBuild.glfw_objects.Debug: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Debug/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Debug/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/Debug/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Debug/libglfw.dylib


PostBuild.glfw_objects.Debug:
PostBuild.glfw.Release:
PostBuild.glfw_objects.Release: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Release/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Release/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/Release/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Release/libglfw.dylib


PostBuild.glfw_objects.Release:
PostBuild.glfw.MinSizeRel:
PostBuild.glfw_objects.MinSizeRel: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/MinSizeRel/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/MinSizeRel/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/MinSizeRel/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/MinSizeRel/libglfw.dylib


PostBuild.glfw_objects.MinSizeRel:
PostBuild.glfw.RelWithDebInfo:
PostBuild.glfw_objects.RelWithDebInfo: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/RelWithDebInfo/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/RelWithDebInfo/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/RelWithDebInfo/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/RelWithDebInfo/libglfw.dylib


PostBuild.glfw_objects.RelWithDebInfo:


# For each target create a dummy ruleso the target does not have to exist
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/Debug/glfw_objects.build/libglfw_objects.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/MinSizeRel/glfw_objects.build/libglfw_objects.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/RelWithDebInfo/glfw_objects.build/libglfw_objects.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/GLFW.build/Release/glfw_objects.build/libglfw_objects.a:
