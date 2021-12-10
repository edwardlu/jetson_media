cmake_minimum_required(VERSION 3.10)
project(camera_applications)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")

set(project_include_dir
	${PROJECT_SOURCE_DIR}/camera_utils
	${PROJECT_SOURCE_DIR}/common
	${PROJECT_SOURCE_DIR}/application
	${PROJECT_SOURCE_DIR}/vendor/camera
	${PROJECT_SOURCE_DIR}/vendor/end_denc
	${PROJECT_SOURCE_DIR}/vendor/layout
	${PROJECT_SOURCE_DIR}/3rd/json/include
)
include_directories(${project_include_dir})

file(GLOB CAMERA_SOURCE
	"${PROJECT_SOURCE_DIR}/camera_utils/*.cpp"
	"${PROJECT_SOURCE_DIR}/common/*.cpp"
	"${PROJECT_SOURCE_DIR}/vendor/camera/*.cpp"
	"${PROJECT_SOURCE_DIR}/vendor/end_denc/*.cpp"
	"${PROJECT_SOURCE_DIR}/vendor/layout/*.cpp"
	"${PROJECT_SOURCE_DIR}/application/*.cpp"
)

add_executable(camera_jetson ${CAMERA_SOURCE})
