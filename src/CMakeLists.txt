cmake_minimum_required(VERSION 3.2)
set($TARGET simple_map_reduce)

add_executable(${TARGET}
    main.cpp
    args_parser.h args_parser.cpp
    base_executor.h base_executor.cpp
    defines.h
    map.h map.cpp
    shuffle.h shuffle.cpp
    reduce.h reduce.cpp
    yamr.h yamr.cpp
    utils.h utils.cpp
    functors.h functors.cpp)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${TARGET}
    PRIVATE ${Boost_INCLUDE_DIR}
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(${TARGET} PRIVATE
        /W4
    )
else ()
    target_compile_options(${TARGET} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(${TARGET}
    ${Boost_LIBRARIES}
    Threads::Threads
)

# бинарник кладем в каталог bin
install(TARGETS ${TARGET} RUNTIME DESTINATION bin)

# генерить будем deb пакет
set(CPACK_GENERATOR DEB)

# конфигурируем deb пакет
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT oshuev.valery@yandex.ru)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-program-options,libboost-system,libboost-thread")

# подключем генератор пакетов
include(CPack)
