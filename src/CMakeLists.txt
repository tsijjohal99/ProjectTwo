set(SRC_FILES board.cpp chessPiece.cpp queen.cpp king.cpp bishop.cpp knight.cpp rook.cpp pawn.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRC-FILES})

target_link_libraries(ProjectTwo PUBLIC src)