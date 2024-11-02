# Loop through each file and get only the filename
file(GLOB FILES_IN_CURRENT_FOLDER "*")
set(TEST_RUNNERS_NAMES)
# Loop through each file and get the filename without extension
foreach(FILE_PATH ${FILES_IN_CURRENT_FOLDER})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
		get_filename_component(FILE_NAME_WE ${FILE_PATH} NAME_WE)
		if(NOT FILE_NAME STREQUAL "CMakeLists.txt")
			set(RUNNER_NAME "${FILE_NAME_WE}-trunner")
			add_executable(${RUNNER_NAME} ${FILE_NAME})
			target_link_libraries(${RUNNER_NAME} PUBLIC tig_lib crypto Unity)
			target_include_directories(${RUNNER_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")
			target_include_directories(${RUNNER_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/external/Unity/src")
			add_test(${FILE_NAME} ${RUNNER_NAME})
		endif()
endforeach()


foreach(TR_NAME ${TEST_RUNNER_NAMES})
endforeach()

