file(GLOB_RECURSE SRC_FILES_MAIN *.cpp *.c)
# add_executable (${PROJECT_NAME} ${SRC_FILES_MAIN})
idf_component_register(SRCS "blink.c"
 ${SRC_FILES_MAIN}
# "*.cpp"
                    INCLUDE_DIRS "." "./AutoGenHeaders" "./paLibSubs")
