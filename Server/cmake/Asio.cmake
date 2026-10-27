# Standalone (non-Boost) asio, header only, as the target asio::asio.
#
# By default a pinned release is downloaded with FetchContent. Point CQYH_ASIO_SOURCE_DIR at an existing checkout
# (the directory that contains include/asio.hpp or asio/include/asio.hpp) to build without network access.

set(CQYH_ASIO_SOURCE_DIR "" CACHE PATH "Existing asio checkout to use instead of downloading one")

if(CQYH_ASIO_SOURCE_DIR)
    set(_asio_root "${CQYH_ASIO_SOURCE_DIR}")
else()
    # A release tarball rather than a git clone: needs no git/shell, and the hash pins the exact contents.
    include(FetchContent)
    FetchContent_Declare(asio
        URL      https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-38-2.tar.gz
        URL_HASH SHA256=9f2648fa483e58a6bf848d970ee0ea650ca19ed7769dfa520ed4f7b8d27af1db
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(asio)     # asio has no CMakeLists.txt: this only downloads and unpacks it
    set(_asio_root "${asio_SOURCE_DIR}")
endif()

# Older releases keep the headers in <root>/asio/include, newer ones (1.38+) in <root>/include.
if(EXISTS "${_asio_root}/include/asio.hpp")
    set(_asio_include "${_asio_root}/include")
elseif(EXISTS "${_asio_root}/asio/include/asio.hpp")
    set(_asio_include "${_asio_root}/asio/include")
else()
    message(FATAL_ERROR "asio.hpp not found under ${_asio_root}")
endif()

find_package(Threads REQUIRED)

add_library(asio INTERFACE)
add_library(asio::asio ALIAS asio)
target_include_directories(asio SYSTEM INTERFACE "${_asio_include}")
target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)
target_link_libraries(asio INTERFACE Threads::Threads)
if(WIN32)
    target_compile_definitions(asio INTERFACE _WIN32_WINNT=0x0A00)     # Windows 10 / Server 2016 and newer
endif()
