#
# ExtPlane plugin build configuration
#
# Change to -DXPLM200=1 for SDK 2.0.0 (X-Plane 9)
QMAKE_CXXFLAGS += -DXPLM210=1
QMAKE_CXXFLAGS += -DXPLM200=1

# If your X-Plane SDK is in another directory, add or change it here:
INCLUDEPATH += XPSDK201/SDK/CHeaders/XPLM
INCLUDEPATH += $$(HOME)/SDK/CHeaders/XPLM
INCLUDEPATH += ../XPlaneSDK/CHeaders/XPLM
INCLUDEPATH += SDK/CHeaders/XPLM
INCLUDEPATH += ../XPlane-SDK/CHeaders/XPLM

# You should not need to touch anything below this for normal build

# Detailed X-Plane plugin build instructions here:
# http://www.xsquawkbox.net/xpsdk/mediawiki/BuildInstall

QT       += core network
QT       -= gui

CONFIG   += console warn_on release shared
CONFIG   -= app_bundle

TEMPLATE = lib

TARGET = extplane-plugin

#QMAKE_CXXFLAGS += -fPIC
#QMAKE_LFLAGS += -shared -fPIC
#  -static-libgcc  <- fails on mac

CONFIG(debug, debug|release) {
    # Debug
    message("Ext-Plane Debug Build")
} else {
    # Release
    message("Ext-Plane Release Build")
    DEFINES += QT_NO_DEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
}

unix:!macx {
     DEFINES += APL=0 IBM=0 LIN=1
}

macx {
     DEFINES += APL=1 IBM=0 LIN=0
     QMAKE_LFLAGS += -dynamiclib
     # -flat_namespace -undefined warning <- not needed or recommended anymore.

     # Build for multiple architectures.
     # The following line is only needed to build universal on PPC architectures.
     # QMAKE_MAC_SDK=/Devloper/SDKs/MacOSX10.4u.sdk
     # This line defines for wich architectures we build.
     CONFIG += x86 ppc
     QMAKE_LFLAGS += -F../XPlaneSDK/Libraries/Mac
     LIBS += -framework XPLM
}

win32 {
    !contains(QMAKE_HOST.arch, x86_64) {
        message("Windows Platform (x86)")
        LIBS += -lXPLM -lXPWidgets
    } else {
        message("Windows Platform (x86_64)")
        LIBS += -lXPLM_64 -lXPWidgets_64
    }
    DEFINES += APL=0 IBM=1 LIN=0
    LIBS += -L$${PWD}/XPSDK201/SDK/Libraries/Win
    DEFINES += NOMINMAX #Qt5 bug
}

QMAKE_POST_LINK += $(COPY_FILE) $(TARGET) extplane.xpl
QMAKE_CLEAN += extplane.xpl

SOURCES += main.cpp \
    xplaneplugin.cpp \
    tcpserver.cpp \
    tcpclient.cpp \
    datarefprovider.cpp \
    datarefs/dataref.cpp \
    datarefs/floatdataref.cpp \
    datarefs/floatarraydataref.cpp \
    datarefs/intdataref.cpp \
    datarefs/doubledataref.cpp \
    datarefs/intarraydataref.cpp \
    datarefs/datadataref.cpp \
    customdata/navcustomdata.cpp \
    customdata/atccustomdata.cpp

HEADERS += \
    xplaneplugin.h \
    tcpserver.h \
    tcpclient.h \
    datarefprovider.h \
    datarefs/dataref.h \
    datarefs/floatdataref.h \
    datarefs/floatarraydataref.h \
    datarefs/intdataref.h \
    datarefs/doubledataref.h \
    datarefs/intarraydataref.h \
    datarefs/datadataref.h \
    util/console.h \
    customdata/navcustomdata.h \
    customdata/atccustomdata.h

OTHER_FILES += README.md client/extplane-client-qt/README
