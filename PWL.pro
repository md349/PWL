isEqual(QT_MAJOR_VERSION, 5) {cache() }
QMAKE_CXXFLAGS+=-Wthread-safety
#use built in Qt lib template
TEMPLATE = lib
CONFIG += staticlib
QT += gui
QT += opengl
QT += core
QT -= xml

TARGET = $$(HOME)/PWL/lib/PWL
#this is where we want to put the intermediate build files
OBJECTS_DIR  = $$(HOME)/PWL/obj
QMAKE_LFLAGS-= -headerpad_max_install_names
QMAKE_LFLAGS_SHLIB -= -single_module
QMAKE_LFLAGS_VERSION =
QMAKE_LFLAGS_COMPAT_VERSION =
QMAKE_LFLAGS_SONAME =
INCLUDEPATH+=include
INCLUDEPATH+=/usr/local/include/

# use this to suppress some warning from boost
QMAKE_CXXFLAGS_WARN_ON += "-Wno-unused-parameter"
# basic compiler flags (not all appropriate for all platforms)
QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/Cellar/boost/1.56.0/include
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native
# define the _DEBUG flag for the graphics lib
DEFINES +=NGL_DEBUG

unix:LIBS += -L/usr/local/lib
# add the ngl lib
unix:LIBS += -L/$(HOME)/NGL/lib -l NGL
INCLUDEPATH += $$(HOME)/NGL/include/

#add sdl
unix:LIBS += /usr/local/Cellar/sdl/1.2.15/lib -l SDL
INCLUDEPATH += /usr/local/Cellar/sdl/1.2.15/include

macx:{
        QMAKE_CXXFLAGS+=  -fPIC
        LIBS+= -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework OpenGL
        LIBS+=  -Wl,-framework,Cocoa
        DEFINES += DARWIN

}

# in this case unix is also mac so we need to exclude mac from the unix build
win32|unix:!macx{
        # now define some linux specific flags
        unix:QMAKE_CXXFLAGS+=  -march=native
        unix:DEFINES += LINUX
        unix:LIBS+= -L/usr/lib64 -lGL -lGLU -lX11

}

# The windows configuration is very frustrating however I seem to have it working now
# you will need to install boost in the path below
# once you have done this set the PATH environment variable to look in
# c:/NGL/lib to find the DLL
win32{
                                message("Using Windows check to see what needs to be installed")
                                CONFIG+=staticlib
                                INCLUDEPATH +=C:/boost/
                                DEFINES+=_USE_MATH_DEFINES
                                # Silence some boost warnings
                                DEFINES+= _SCL_SECURE_NO_WARNINGS
                                DESTDIR=c:/
                                DEFINES += NO_DLL
}

SOURCES+= $$PWD/src/*.cpp \
          $$PWD/lodepng/*.cpp

isEqual(QT_MAJOR_VERSION, 4) {
                        OBJECTIVE_SOURCES += $$SRC_DIR/setGL32VisualMac.mm
}

HEADERS+=$$PWD/include/*.h \
         $$PWD/lodepng/*.h

