add_library(
    theIncludes
    board.h
    chessPiece.h
    queen.h
    king.h
    bishop.h
    knight.h
    rook.h
    pawn.h
)

target_include_directories(theIncludes PUBLIC ../"{CMAKE-CURRENT_SOURCE_DIR}"/src)