file(GLOB_RECURSE SRC_FILES_MAIN *.cpp *.c)

idf_component_register(SRCS ${SRC_FILES_MAIN}
                    INCLUDE_DIRS "." )