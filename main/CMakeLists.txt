set(Main_SRCS
        main.cpp
)

add_executable(lexical-analyzer
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(lexical-analyzer
    grammar-parser
    automata
    #code-parser
    dfa-minimizer
    #error-handler
    pattern-matcher
    utils-lib
    #file-writer
)

install(TARGETS lexical-analyzer DESTINATION bin)
