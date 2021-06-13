# 获取所有源文件

file(GLOB_RECURSE SRC_FILES *.cpp)
message("sssssssssssssss")
idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS ".")
