# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.CGL.Debug:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Debug/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Debug/libCGL.a


PostBuild.clothsim.Debug:
PostBuild.CGL.Debug: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Debug/clothsim
PostBuild.nanogui.Debug: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Debug/clothsim
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Debug/clothsim:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Debug/libCGL.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Debug/libnanogui.dylib\
	/usr/local/lib/libfreetype.dylib
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Debug/clothsim


PostBuild.glfw.Debug:
PostBuild.glfw_objects.Debug: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Debug/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Debug/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/Debug/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Debug/libglfw.dylib


PostBuild.glfw_objects.Debug:
PostBuild.nanogui.Debug:
PostBuild.nanogui-obj.Debug: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Debug/libnanogui.dylib
PostBuild.glfw_objects.Debug: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Debug/libnanogui.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Debug/libnanogui.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/Debug/nanogui-obj.build/libnanogui-obj.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/Debug/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Debug/libnanogui.dylib


PostBuild.nanogui-obj.Debug:
PostBuild.CGL.Release:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Release/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Release/libCGL.a


PostBuild.clothsim.Release:
PostBuild.CGL.Release: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Release/clothsim
PostBuild.nanogui.Release: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Release/clothsim
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Release/clothsim:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Release/libCGL.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Release/libnanogui.dylib\
	/usr/local/lib/libfreetype.dylib
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/Release/clothsim


PostBuild.glfw.Release:
PostBuild.glfw_objects.Release: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Release/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Release/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/Release/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/Release/libglfw.dylib


PostBuild.glfw_objects.Release:
PostBuild.nanogui.Release:
PostBuild.nanogui-obj.Release: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Release/libnanogui.dylib
PostBuild.glfw_objects.Release: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Release/libnanogui.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Release/libnanogui.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/Release/nanogui-obj.build/libnanogui-obj.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/Release/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Release/libnanogui.dylib


PostBuild.nanogui-obj.Release:
PostBuild.CGL.MinSizeRel:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/MinSizeRel/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/MinSizeRel/libCGL.a


PostBuild.clothsim.MinSizeRel:
PostBuild.CGL.MinSizeRel: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/MinSizeRel/clothsim
PostBuild.nanogui.MinSizeRel: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/MinSizeRel/clothsim
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/MinSizeRel/clothsim:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/MinSizeRel/libCGL.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/MinSizeRel/libnanogui.dylib\
	/usr/local/lib/libfreetype.dylib
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/MinSizeRel/clothsim


PostBuild.glfw.MinSizeRel:
PostBuild.glfw_objects.MinSizeRel: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/MinSizeRel/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/MinSizeRel/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/MinSizeRel/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/MinSizeRel/libglfw.dylib


PostBuild.glfw_objects.MinSizeRel:
PostBuild.nanogui.MinSizeRel:
PostBuild.nanogui-obj.MinSizeRel: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/MinSizeRel/libnanogui.dylib
PostBuild.glfw_objects.MinSizeRel: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/MinSizeRel/libnanogui.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/MinSizeRel/libnanogui.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/MinSizeRel/nanogui-obj.build/libnanogui-obj.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/MinSizeRel/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/MinSizeRel/libnanogui.dylib


PostBuild.nanogui-obj.MinSizeRel:
PostBuild.CGL.RelWithDebInfo:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/RelWithDebInfo/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/RelWithDebInfo/libCGL.a


PostBuild.clothsim.RelWithDebInfo:
PostBuild.CGL.RelWithDebInfo: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/RelWithDebInfo/clothsim
PostBuild.nanogui.RelWithDebInfo: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/RelWithDebInfo/clothsim
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/RelWithDebInfo/clothsim:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/RelWithDebInfo/libCGL.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/RelWithDebInfo/libnanogui.dylib\
	/usr/local/lib/libfreetype.dylib
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/RelWithDebInfo/clothsim


PostBuild.glfw.RelWithDebInfo:
PostBuild.glfw_objects.RelWithDebInfo: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/RelWithDebInfo/libglfw.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/RelWithDebInfo/libglfw.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/RelWithDebInfo/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/RelWithDebInfo/libglfw.dylib


PostBuild.glfw_objects.RelWithDebInfo:
PostBuild.nanogui.RelWithDebInfo:
PostBuild.nanogui-obj.RelWithDebInfo: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/RelWithDebInfo/libnanogui.dylib
PostBuild.glfw_objects.RelWithDebInfo: /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/RelWithDebInfo/libnanogui.dylib
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/RelWithDebInfo/libnanogui.dylib:\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/RelWithDebInfo/nanogui-obj.build/libnanogui-obj.a\
	/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/RelWithDebInfo/glfw_objects.build/libglfw_objects.a
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/RelWithDebInfo/libnanogui.dylib


PostBuild.nanogui-obj.RelWithDebInfo:


# For each target create a dummy ruleso the target does not have to exist
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Debug/libCGL.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/MinSizeRel/libCGL.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/RelWithDebInfo/libCGL.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Release/libCGL.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/Debug/nanogui-obj.build/libnanogui-obj.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/MinSizeRel/nanogui-obj.build/libnanogui-obj.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/RelWithDebInfo/nanogui-obj.build/libnanogui-obj.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ClothSim.build/Release/nanogui-obj.build/libnanogui-obj.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Debug/libnanogui.dylib:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/MinSizeRel/libnanogui.dylib:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/RelWithDebInfo/libnanogui.dylib:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/Release/libnanogui.dylib:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/Debug/glfw_objects.build/libglfw_objects.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/MinSizeRel/glfw_objects.build/libglfw_objects.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/RelWithDebInfo/glfw_objects.build/libglfw_objects.a:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/ext/nanogui/ext_build/glfw/src/ClothSim.build/Release/glfw_objects.build/libglfw_objects.a:
/usr/local/lib/libfreetype.dylib:
