
#include <catch.hpp>
#include "rex/rex.h"

#include <vector>

/*
 *  Testing basic lexer functionality.
 */

SCENARIO( "The lexer \"rex\" can tokenize strings", "[rex]" ) {


    GIVEN( "A an empty string" ) {
        std::istringstream iss("");

        WHEN( "The string is passed to the lexer" ) {
            auto tok = get_token(iss);

            THEN( "An \"END\" token is returned" ) {
                REQUIRE( tok.name == TOK::END );
                REQUIRE( tok.value == "" );
            }
        }
    }


    GIVEN( "A string with a \"name\" (identifier)" ) {
        std::istringstream iss("name");

        WHEN( "The string is passed to the lexer" ) {
            auto tok = get_token(iss);

            THEN( "A \"NAME\" token is returned" ) {
                REQUIRE( tok.name == TOK::NAME );
                REQUIRE( tok.value == iss.str() );
            }
        }
    }


    // GIVEN( "A string with a left and right parentheses" ) {
    //     std::istringstream iss("()");

    //     WHEN( "The string is passed twice to the lexer" ) {
    //         auto tok1 = get_token(iss);
    //         auto tok2 = get_token(iss);

    //         THEN( "A \"LPAREN\" and \"RPAREN\" tokens are returned" ) {
    //             REQUIRE( tok1.name == TOK::LPAREN );
    //             REQUIRE( tok1.value == iss.str().substr(0,1) );
    //             REQUIRE( tok2.name == TOK::RPAREN );
    //             REQUIRE( tok2.value == iss.str().substr(1,1) );
    //         }
    //     }
    // }

    // GIVEN( "A string with a single semicolon" ) {
    //     std::istringstream iss(";");

    //     WHEN( "The string is passed to the lexer" ) {
    //         auto tok = get_token(iss);

    //         THEN( "A \"SEMICOL\" token is returned" ) {
    //             REQUIRE( tok.name == TOK::SEMICOL );
    //             REQUIRE( tok.value == iss.str() );
    //         }
    //     }
    // }


    // GIVEN( "A string with a single integer" ) {
    //     std::istringstream iss("1234567");

    //     WHEN( "The string is passed to the lexer" ) {
    //         auto tok = get_token(iss);

    //         THEN( "An \"INT\" token is returned" ) {
    //             REQUIRE( tok.name == TOK::INT );
    //             REQUIRE( tok.value == iss.str() );
    //         }
    //     }
    // }


    // GIVEN( "A string with a single floating-point number" ) {
    //     std::istringstream iss("123.456");

    //     WHEN( "The string is passed to the lexer" ) {
    //         auto tok = get_token(iss);

    //         THEN( "A \"FLOAT\" token is returned" ) {
    //             REQUIRE( tok.name == TOK::FLOAT );
    //             REQUIRE( tok.value == iss.str() );
    //         }
    //     }
    // }


    // GIVEN( "A string with an initializer symbol and binary operators" ) {
    //     std::istringstream iss("=+-*/");

    //     WHEN( "The string is passed to the lexer onces for each character" ) {
    //         std::vector<Token> toks;
    //         for (const auto& c : iss.str())
    //             toks.push_back(get_token(iss));

    //         THEN( "The correct tokens are returned" ) {
    //             std::vector<Token> correct_toks = {
    //                 {TOK::INIT, "="},
    //                 {TOK::BINOP, "+"},
    //                 {TOK::BINOP, "-"},
    //                 {TOK::BINOP, "*"},
    //                 {TOK::BINOP, "/"}
    //             };
    //             for (auto i = 0u; i < toks.size(); ++i) {
    //                 REQUIRE( toks[i].name == correct_toks[i].name );
    //                 REQUIRE( toks[i].value == correct_toks[i].value );
    //             }
    //         }
    //     }
    // }


    // GIVEN( "A string with a single-line and multi-line comments" ) {
    //     std::istringstream iss("#this is ignored\n#[\nso\nis\nthis\n#]");

    //     WHEN( "The string is passed to the lexer" ) {
    //         auto tok = get_token(iss);

    //         THEN( "An \"END\" token is returned" ) {
    //             REQUIRE( tok.name == TOK::END );
    //             REQUIRE( tok.value == "" );
    //         }
    //     }
    // }


    // GIVEN( "A string with an ill-formed floating-point number" ) {
    //     std::istringstream iss("1.1.1");

    //     WHEN( "The string is passed to the lexer" ) {
    //         auto tok = get_token(iss);

    //         THEN( "An \"UNDEF\" token is returned" ) {
    //             REQUIRE( tok.name == TOK::UNDEF );
    //             REQUIRE( tok.value == "" );
    //         }
    //     }
    // }


    // GIVEN( "A string with several lines of valid tokens" ) {
    //     std::istringstream iss(
    //         "a = 10\n"
    //         "  # 1.1.1   \n"
    //         "a = (1.1234) #[blah\n"
    //         "this is still commented]#but this is not\n"
    //         ";\n"
    //         "a = a + a * b / c - j\n"
    //         "- - - - + =\n"
    //     );

    //     WHEN( "The string is continually passed to the lexer" ) {
    //         std::vector<Token> toks;
    //         do {toks.push_back(get_token(iss));}
    //         while (toks.back().name != TOK::END);

    //         THEN( "No errors are reports, and none of the tokens are \"UNDEF\"" ) {
    //             for (const auto& tok : toks)
    //                 REQUIRE( tok.name != TOK::UNDEF );
    //         }
    //     }
    // }
}