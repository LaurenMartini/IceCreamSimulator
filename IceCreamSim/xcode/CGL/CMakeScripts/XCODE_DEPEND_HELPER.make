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


PostBuild.CGL.Release:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Release/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/Release/libCGL.a


PostBuild.CGL.MinSizeRel:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/MinSizeRel/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/MinSizeRel/libCGL.a


PostBuild.CGL.RelWithDebInfo:
/Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/RelWithDebInfo/libCGL.a:
	/bin/rm -f /Users/natkham/Desktop/cs184/projects/p4-clothsim-natkham/xcode/CGL/src/RelWithDebInfo/libCGL.a




# For each target create a dummy ruleso the target does not have to exist
