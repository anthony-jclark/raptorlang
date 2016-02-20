
/*
 *  Testing basic lexer functionality.
 */



#include <catch.hpp>
#include "rex/rex.h"
using namespace raptor::lexer;

#include <vector>



SCENARIO ( "The lexer \"rex\" can tokenize strings", "[rex]" ) {


    GIVEN ( "An empty string" ) {
        std::istringstream iss("");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "An \"END\" token is returned" ) {
                REQUIRE ( tok.name == TOK::END );
                REQUIRE ( tok.value == "" );
            }
        }
    }


    GIVEN ( "A string with a \"name\" (identifier)" ) {
        std::istringstream iss("test_name");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "A \"NAME\" token is returned" ) {
                REQUIRE ( tok.name == TOK::NAME );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A string with a single integer" ) {
        std::istringstream iss("123456789");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "An \"INTEGER\" token is returned" ) {
                REQUIRE ( tok.name == TOK::INTEGER );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A string with a single floating-point number" ) {
        std::istringstream iss("1234.56789");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "A \"FLOAT\" token is returned" ) {
                REQUIRE ( tok.name == TOK::FLOAT );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A string with an invalid single floating-point number" ) {
        std::istringstream iss("1.234.56789");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "An \"UNDEFINED\" token is returned" ) {
                REQUIRE ( tok.name == TOK::UNDEFINED );
                REQUIRE ( tok.value == "" );
            }
        }
    }


    GIVEN ( "A string with a string literal" ) {
        std::istringstream iss("\"this is a string literal\"");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "A \"STRING\" token is returned" ) {
                REQUIRE ( tok.name == TOK::STRING );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A string with a character literal" ) {
        std::istringstream iss("'c'");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "A \"CHARACTER\" token is returned" ) {
                REQUIRE ( tok.name == TOK::CHARACTER );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A string with an invalid character literal" ) {
        std::istringstream iss("'cc'");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "An \"UNDEFINED\" token is returned" ) {
                REQUIRE ( tok.name == TOK::UNDEFINED );
                REQUIRE ( tok.value == "" );
            }
        }
    }


    GIVEN ( "A string containing each of the reserved keywords" ) {
        std::stringstream ss;
        auto reserved_token_map = getReservedList();

        std::vector<TOK> tok_names;
        std::vector<std::string> tok_values;
        for (const auto &pair : reserved_token_map) {
            ss << pair.first << " ";
            tok_values.push_back(pair.first);
            tok_names.push_back(pair.second);
        }
        tok_values.push_back("");
        tok_names.push_back(TOK::END);

        WHEN ( "The string is repeatedly passed to the lexer" ) {
            auto lexer = rex(ss);

            std::vector<Token> toks;
            toks.push_back(lexer.get_token());
            while (toks.back().name != TOK::END)
                toks.push_back(lexer.get_token());

            THEN ( "The correct reserved keyword tokens are returned" ) {
                for (auto i = 0u; i < toks.size(); ++i) {
                    REQUIRE (toks[i].name == tok_names[i]);
                    REQUIRE (toks[i].value == tok_values[i]);
                }
            }
        }
    }


    GIVEN ( "A string containing each of the punctuators" ) {
        std::stringstream ss;
        auto punctuator_token_map = getPunctuatorList();

        std::vector<TOK> tok_names;
        std::vector<std::string> tok_values;
        for (const auto &pair : punctuator_token_map) {
            ss << pair.first << " ";
            tok_values.push_back(pair.first);
            tok_names.push_back(pair.second);
        }
        tok_values.push_back("");
        tok_names.push_back(TOK::END);

        WHEN ( "The string is repeatedly passed to the lexer" ) {
            auto lexer = rex(ss);

            std::vector<Token> toks;
            toks.push_back(lexer.get_token());
            while (toks.back().name != TOK::END)
                toks.push_back(lexer.get_token());

            THEN ( "The correct punctuator tokens are returned" ) {
                for (auto i = 0u; i < toks.size(); ++i) {
                    REQUIRE (toks[i].name == tok_names[i]);
                    REQUIRE (toks[i].value == tok_values[i]);
                }
            }
        }
    }


    GIVEN ( "A string with a single-line comment" ) {
        std::istringstream iss("//this is a single-line comment");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "A \"COMMENT\" token is returned" ) {
                REQUIRE ( tok.name == TOK::COMMENT );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A string with a multi-line comment" ) {
        std::istringstream iss("/*\nmulti-\nline\ncomment\n*/");

        WHEN ( "The string is passed to the lexer" ) {
            auto lexer = rex(iss);
            auto tok = lexer.get_token();

            THEN ( "A \"COMMENT\" token is returned" ) {
                REQUIRE ( tok.name == TOK::COMMENT );
                REQUIRE ( tok.value == iss.str() );
            }
        }
    }


    GIVEN ( "A token" ) {
        Token t{TOK::END, ""};

        WHEN ( "The token is passed to an output stream" ) {
            std::ostringstream oss;
            oss << t;

            THEN ( "The token is handled and formatted for output" ) {
                REQUIRE ( oss.str() == "{END:\"\"}" );
            }
        }
    }


    GIVEN ( "A TOK" ) {
        auto t = TOK::END;

        WHEN ( "The TOK is passed to an output stream" ) {
            std::ostringstream oss;
            oss << t;

            THEN ( "The TOK is handled and formatted for output" ) {
                REQUIRE ( oss.str() == "END" );
            }
        }
    }


    GIVEN ( "A string with several lines of valid tokens" ) {
        std::istringstream iss(
            "// This is a test program\n"
            "int main() {\n"
            "    double i = 0.0;\n"
            "    cout << \"Hello World\" << '!' << std::endl;\n"
            "    return 0;\n"
            "}\n"
            "\n"
        );

        WHEN ( "The string is continually passed to the lexer" ) {
            auto lexer = rex(iss);

            std::vector<Token> toks;
            do {toks.push_back(lexer.get_token());}
            while (toks.back().name != TOK::END);

            THEN ( "No errors are reports, and none of the tokens are \"UNDEFINED\"" ) {
                for (const auto& tok : toks)
                    REQUIRE ( tok.name != TOK::UNDEFINED );
            }
        }
    }
}
