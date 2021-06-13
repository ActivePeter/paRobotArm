# 获取所有源文件

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.cc)
idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS ".")
