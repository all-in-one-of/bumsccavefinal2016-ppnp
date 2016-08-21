# This specifies the exe name
TARGET=PPNPQtGui
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT+=gui opengl core

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
	cache()
	DEFINES +=QT5BUILD
}
# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle
# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES+=   $$PWD/src/MainWindow.cpp \
            $$PWD/src/NGLScene.cpp   \
            $$PWD/src/main.cpp \
            $$PWD/src/graph/Lattice.cpp \
            $$PWD/src/graph/Hexagon.cpp \
            $$PWD/src/graph/Square.cpp \
            $$PWD/src/graph/Node.cpp \
            $$PWD/src/graph/sub/Path.cpp \
            $$PWD/src/graph/sub/Dendrite.cpp \
            $$PWD/src/alg/Dijkstra.cpp \
            $$PWD/src/alg/PPNP.cpp \
            $$PWD/src/utils/Logger.cpp \
            $$PWD/src/utils/BoundingBox.cpp \
            $$PWD/src/abstract/WeightFunction.cpp \
            $$PWD/src/functions/DefaultWeightFunction.cpp \
            $$PWD/src/functions/ImageWeightFunction.cpp \

#Forms
FORMS+=     $$PWD/ui/MainWindow.ui \


# same for the .h files
HEADERS+= $$PWD/include/MainWindow.h \
          $$PWD/include/NGLScene.h \
          $$PWD/include/graph/Lattice.h \
          $$PWD/include/alg/Dijkstra.h \
          $$PWD/include/alg/PPNP.h \
          $$PWD/include/graph/Node.h \
          $$PWD/include/graph/sub/Path.h \
          $$PWD/include/graph/sub/Dendrite.h \
          $$PWD/include/graph/Hexagon.h \
          $$PWD/include/graph/Square.h \
          $$PWD/include/abstract/Portable.h \
          $$PWD/include/abstract/WeightFunction.h \
          $$PWD/include/utils/Logger.h \
          $$PWD/include/utils/BoundingBox.h \
          $$PWD/include/utils/glu.h \
          $$PWD/include/functions/DefaultWeightFunction.h \
          $$PWD/include/functions/ImageWeightFunction.h \

# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
# where our exe is going to live (root of project)
DESTDIR=./
# add the glsl shader files
OTHER_FILES+= shaders/*.glsl \
							README.md
# were are going to default to a console app
CONFIG += console
# note each command you add needs a ; as it will be run as a single line
# first check if we are shadow building or not easiest way is to check out against current
!equals(PWD, $${OUT_PWD}){
	copydata.commands = echo "creating destination dirs" ;
	# now make a dir
	copydata.commands += mkdir -p $$OUT_PWD/shaders ;
	copydata.commands += echo "copying files" ;
	# then copy the files
	copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
	# now make sure the first target is built before copy
	first.depends = $(first) copydata
	export(first.depends)
	export(copydata.commands)
	# now add it as an extra target
	QMAKE_EXTRA_TARGETS += first copydata
}
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
	message("including $HOME/NGL")
	include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
	message("Using custom NGL location")
	include($(NGLDIR)/UseNGL.pri)
}
