file(GLOB_RECURSE SRC_FILES_MAIN *.cpp *.c)

idf_component_register(
    SRCS 
        "main.cpp"
        ${SRC_FILES_MAIN}

    INCLUDE_DIRS 
        "."
        "./AutoGenHeaders" 
        "./paLibSubs"
)

