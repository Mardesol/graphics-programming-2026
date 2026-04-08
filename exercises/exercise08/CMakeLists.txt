set(libraries itugl glad glfw assimp imgui ${APPLE_LIBRARIES})

file(GLOB target_inc "*.h")
file(GLOB target_src "*.cpp")

file(GLOB_RECURSE shaders "*.vert" "*.frag" "*.geom" "*.glsl")
source_group("Shaders" FILES ${shaders})

add_executable(${TARGETNAME} ${target_inc} ${target_src} ${shaders})
target_link_libraries(${TARGETNAME} ${libraries})