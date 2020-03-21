cmake_minimum_required(VERSION 3.5)

project(LimeEvo1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
########################################################################
# Find boost
########################################################################
if (UNIX AND EXISTS "/usr/lib64")
    list(APPEND BOOST_LIBRARYDIR "/usr/lib64") #fedora 64-bit fix
endif (UNIX AND EXISTS "/usr/lib64")
set(Boost_ADDITIONAL_VERSIONS
        "1.35.0" "1.35" "1.36.0" "1.36" "1.37.0" "1.37" "1.38.0" "1.38" "1.39.0" "1.39"
        "1.40.0" "1.40" "1.41.0" "1.41" "1.42.0" "1.42" "1.43.0" "1.43" "1.44.0" "1.44"
        "1.45.0" "1.45" "1.46.0" "1.46" "1.47.0" "1.47" "1.48.0" "1.48" "1.49.0" "1.49"
        "1.50.0" "1.50" "1.51.0" "1.51" "1.52.0" "1.52" "1.53.0" "1.53" "1.54.0" "1.54"
        "1.55.0" "1.55" "1.56.0" "1.56" "1.57.0" "1.57" "1.58.0" "1.58" "1.59.0" "1.59"
        "1.60.0" "1.60" "1.61.0" "1.61" "1.62.0" "1.62" "1.63.0" "1.63" "1.64.0" "1.64"
        "1.65.0" "1.65" "1.66.0" "1.66" "1.67.0" "1.67" "1.68.0" "1.68" "1.69.0" "1.69"
        )
find_package(Boost "1.35" COMPONENTS filesystem system thread)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost required")
endif ()

find_package(SWIG)
SET(GCC_COVERAGE_COMPILE_FLAGS "-Wno-c++11-extensions")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

if (SWIG_FOUND)
    # Minimum SWIG version required is 1.3.31
    set(SWIG_VERSION_CHECK FALSE)
    if ("${SWIG_VERSION}" VERSION_GREATER "1.3.30")
        set(SWIG_VERSION_CHECK TRUE)
    endif ()
else ()
    message(FATAL_ERROR "SWIG required to compile")
endif (SWIG_FOUND)

########################################################################
# Find gnuradio build dependencies
########################################################################
set(GR_REQUIRED_COMPONENTS RUNTIME FILTER PMT)
find_package(Gnuradio)
find_package(Volk)
#find_package(CppUnit)
#find_package(fftw)
#find_package(Doxygen)

option(LOCAL_OSMOCOM "Build with local osmocom libraries" OFF)
#find_package(Libosmocore)
#find_package(Libosmocodec)
#find_package(Libosmocoding)
#find_package(Libosmogsm)

#if(NOT PKG_CONFIG_FOUND)
#    message(FATAL_ERROR "pkg-config is required")
#endif()
#if(NOT GNURADIO_RUNTIME_FOUND)
#    message(FATAL_ERROR "GnuRadio Runtime required")
#endif()
#if(NOT VOLK_FOUND)
#    message(FATAL_ERROR "Volk Not Found")
#endif()
#if(NOT CPPUNIT_FOUND)
#    message(FATAL_ERROR "CppUnit required to compile stuff")
#endif()

#if(NOT LIBOSMOCORE_FOUND OR NOT LIBOSMOCODEC_FOUND OR NOT LIBOSMOGSM_FOUND)
#    set(LOCAL_OSMOCOM ON)
#endif()
#
#if(LOCAL_OSMOCOM)
#    message(STATUS "Compiling with local osmocom libraries")
#elseif(NOT LIBOSMOCODING_FOUND)
#    message(STATUS "Compiling local version of libosmocoding")
#endif()

find_package(Qt5Core REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)

set(BLANK_BOX_LINE "|                                             |")
link_directories(${LINK_DIRS})
add_definitions(-DLIBBLADERF_SEARCH_PREFIX="${CMAKE_INSTALL_PREFIX}")
add_definitions(-DLOGGING_ENABLED=1)
include_directories(${TEST_CONFIG_FILE_INCLUDES} ${INCLUDES}
        "../include"
        "/opt/local/include/boost"
        "/opt/local/include"
        )
link_directories(/opt/local/lib)

find_package(LimeSuite)
#find_package(qwt)
find_package(Qt5 COMPONENTS Widgets Concurrent LinguistTools REQUIRED)
#find_package(qwt)

set(TS_FILES qt_widgets_template_en_US.ts RxThread.cpp ../include/RxThread.hpp LimeStreamRx.cpp LimeStreamRx.hpp ../include/helpers.hpp ../include/ui.h StreamTimer.cpp StreamTimer.hpp TxThread.cpp ../include/TxThread.hpp RxTx.cpp ../include/RxTx.hpp ../include/Base.cpp ../include/Base.hpp ../include/Derived.cpp ../include/Derived.hpp Radios.cpp ../include/Radios.h RadioBladeRf.cpp ../include/RadioBladeRf.hpp RadioRtlSdr.cpp ../include/RadioRtlSdr.hpp RxThreadConcurrent.cpp ../include/RxThreadConcurrent.hpp)

if (ANDROID)
    add_library(LimeEvo1 SHARED
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            ${TS_FILES}
            StreamTimer.cpp StreamTimer.hpp TxThread.cpp ../include/TxThread.hpp RxTx.cpp ../include/RxTx.hpp Radios.cpp ../include/Radios.h RadioBladeRf.cpp ../include/RadioBladeRf.hpp RadioRtlSdr.cpp ../include/RadioRtlSdr.hpp RxThreadConcurrent.cpp ../include/RxThreadConcurrent.hpp)
else ()
    add_executable(LimeEvo1
            main.cpp
            mainwindow.cpp ../include/mainwindow.h
            LimeRadio.cpp ../include/LimeRadio.hpp
            LimeDevice.cpp ../include/LimeDevice.h
            mainwindow.ui

            ../src/resources.qrc
            RxThread.cpp
            ../include/RxThread.hpp

            #            ${TS_FILES}
            LimeStreamRx.cpp LimeStreamRx.hpp ../include/ui.h StreamTimer.cpp StreamTimer.hpp ../src/TxThread.cpp ../include/TxThread.hpp RxTx.cpp ../include/RxTx.hpp Radios.cpp ../include/Radios.h RadioBladeRf.cpp ../include/RadioBladeRf.hpp RadioRtlSdr.cpp ../include/RadioRtlSdr.hpp RxThreadConcurrent.cpp ../include/RxThreadConcurrent.hpp)
endif ()

include_directories(/opt/local/libexec/qt5/lib/qwt.framework/headers)
target_link_libraries(LimeEvo1 PRIVATE LimeSuite bladerf Qt5::Widgets Qt5::Concurrent /opt/local/libexec/qt5/lib/qwt.framework)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
