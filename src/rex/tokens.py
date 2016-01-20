#!/usr/bin/env python

"""
Create an enum for tokens, and a function for printing them.

TODO:

"""

import sys
import os

TAB = "    "
TOK_ENUM = "TOK"
TOK_STRUCT = "Token"

TOSTRING_FCN = "TOK_toString"
RESERVED_FCN = "TOK_getReserved"
PUNCT_FCN = "TOK_getPunctuator"

GETRESERVED_FCN = "TOK_getListReserved"
GETPUNCTS_FCN = "TOK_getListPuncts"
GETOTHER_FCN = "TOK_get"

MAX_COL = 80
COMMENT_BANNER = "// --------------------------------------------------------"


def read_tokens(lines):
    """Read tokens from standard input."""

    tokens = []
    keywords = []
    punctuators = []
    other = []
    lnumber = 0

    for line in lines:
        lnumber += 1

        # Strip extraneous white space and check for EOF
        lstrip = line.strip()
        if not lstrip:
            break

        # Remove whitespace from the middle of string and check for comments
        lsplit = lstrip.split()
        if (lsplit[0] == "//"):
            continue

        # Ensure that the ':' and ';' characters are present
        try:
            if (lsplit[1] != ':' or lsplit[3] != ';'):
                msg = "Error parsing the token file on line " + str(lnumber)
                print(msg + ' : "' + " ".join(lsplit) + '".')
                exit(1)
        except Exception, e:
            msg = "Invalid token string on line " + str(lnumber)
            print(msg + ' ("' + " ".join(lsplit) + '""): ' + str(e) + '.')
            exit(1)

        # Add tokens to the dictionary
        tname = lsplit[0]
        tvalue = lsplit[2].replace("'", "")
        token = (tname, tvalue)
        tokens.append(token)

        # Add keywords to list
        if (len(tvalue) != 0 and (tvalue[0].isalpha() or tvalue[0] == '_')):
            keywords.append(token)

        elif (len(tvalue) != 0):
            punctuators.append(token)

        else:
            other.append(token)

    # Add extra tokens
    tokens.sort(key=lambda tup: tup[1])
    return tokens, keywords, punctuators


def header_guard_top():
    guard_name = "_TOKENS_HEADER_"
    guard_string = "\n"
    guard_string += "#ifndef " + guard_name + "\n"
    guard_string += "#define " + guard_name
    return guard_string + "\n\n"


def header_guard_bottom():
    return "#endif\n"


def includes(fnames):
    """Add included files."""
    include_string = ""
    for fname in fnames:
        include_string += "#include " + fname + "\n"
    return include_string + "\n\n"


def token_enum(tokens):
    """Add a definition for the TOK enum."""
    enum_string = "enum class " + TOK_ENUM + "\n{\n"
    for tok in tokens:
        enum_string += TAB + tok[0] + ",//" + tok[1] + "\n"
    return enum_string + "};\n\n"


def token_struct():
    """Add a definition for the Token struct."""
    struct_string = "struct " + TOK_STRUCT + "{\n"
    struct_string += TAB + TOK_ENUM + " name;\n"
    struct_string += TAB + "std::string value;\n};"
    return struct_string + "\n\n"


def token_string_proto():
    proto_string = COMMENT_BANNER
    proto_string += "\n// Function for printing tokens\n"
    proto_string += COMMENT_BANNER
    proto_string += "std::string " + TOSTRING_FCN + "(" + TOK_STRUCT + " t);"
    return proto_string + "\n\n"


def token_string_fcn(tokens):
    """Add a definition for the token toString function."""

    # Function definition
    fcn_string = token_string_proto()[:-3] + "\n{\n"

    # An array of TOKs in string form
    array_name = "TOK_STRINGS"
    fcn_string += TAB + "static const std::array<std::string,"
    fcn_string += str(len(tokens))
    fcn_string += "> " + array_name + " = {{"

    line_start = "\n" + TAB + TAB
    col = len(line_start)
    fcn_string += line_start
    for tok in tokens:
        # Make sure that lines do not go over MAX_COL characters
        line = "\"" + tok[0] + "\", "
        if (col + len(line)) > MAX_COL:
            fcn_string += "\n" + TAB + TAB
            col = len(line_start)
        fcn_string += line
        col += len(line)
    fcn_string += "\n" + TAB + "}};\n"

    # Return the correct string
    fcn_string += TAB + "return \"{\" + " + array_name
    fcn_string += "[static_cast<unsigned>(t.name)]"
    fcn_string += " + \":\" + t.value + \"}\";\n"
    return fcn_string + "}\n\n"


def reserved_keyword_proto():
    proto_string = COMMENT_BANNER
    proto_string += "\n// Utility function used to check for reserved words\n"
    proto_string += COMMENT_BANNER
    proto_string += TOK_ENUM + " " + RESERVED_FCN + "(std::string word);"
    return proto_string + "\n\n"


def reserved_keyword_fcn(keywords):
    """Add a definition for the reserved keyword function."""

    # Function definition
    fcn_string = reserved_keyword_proto()[:-3] + "\n{\n"

    # A map from strings to TOKs
    map_name = "TOK_KEYWORDS"
    fcn_string += TAB + "static const std::unordered_map<std::string, "
    fcn_string += TOK_ENUM + "> " + map_name + " = {\n"
    for kword in keywords:
        fcn_string += TAB + TAB + "{\"" + kword[1]
        fcn_string += "\", TOK::" + kword[0] + "},\n"
    fcn_string += TAB + "};\n"

    # Search for the reserved keywrod in the map (UNDEFINED if not found)
    fcn_string += TAB + "auto search = " + map_name + ".find(word);\n"
    fcn_string += TAB + "if (search != " + map_name + ".end()) {\n"
    fcn_string += TAB + TAB + "return search->second;\n"
    fcn_string += TAB + "}\n" + TAB + "else {\n" + TAB + TAB + "return "
    fcn_string += "TOK::UNDEFINED;\n}"
    return fcn_string + "}\n\n"


def punctuator_proto():
    proto_string = COMMENT_BANNER
    proto_string += "\n// Utility function used to check for punctuators\n"
    proto_string += COMMENT_BANNER
    proto_string += TOK_ENUM + " " + PUNCT_FCN + "(std::istream& ts, char c);"
    return proto_string + "\n\n"


def punctuator_fcn(punctuators):
    """Add a definition for a punctuator function."""

    # Add the function definition
    fcn_string = punctuator_proto()[:-3] + "\n{\n"

    # Add a variable for the maximum number of characters in a punctuator
    max_punc_len = max([len(p[1]) for p in punctuators])
    fcn_string += TAB + "static const unsigned MAX_PUNC_CHARS = "
    fcn_string += str(max_punc_len) + ";\n"
    fcn_string += TAB + "static_assert(MAX_PUNC_CHARS == 2);\n"

    # Create the map of strings to punctuator tokens
    map_name = "TOK_KEYWORDS"
    fcn_string += TAB + "static const std::unordered_map<std::string, "
    fcn_string += TOK_ENUM + "> " + map_name + " = {\n"
    for punct in punctuators:
        fcn_string += TAB + TAB + "{\"" + punct[1]
        fcn_string += "\", TOK::" + punct[0] + "},\n"
    fcn_string += TAB + "};\n"

    # Search for the function based on how many characters we should search
    fcn_string += """
    std::string word{c};
    TOK return_token = TOK::UNDEFINED;

    auto search = TOK_KEYWORDS.find(word);
    if (search != TOK_KEYWORDS.end()) {
        return_token = search->second;
    }

    if (ts.get(c)) {
        word += c;
        search = TOK_KEYWORDS.find(word);
        if (search != TOK_KEYWORDS.end())
            return_token = search->second;
        else
            ts.unget();
    }
    return return_token;"""
    return fcn_string + "\n}\n\n"


def main(ifilename, ofilename):
    """Create the tokens header file."""

    # Read tokens and check for empty file
    token_lines = []
    with open(ifilename, 'r') as tokens_file:
        token_lines = tokens_file.readlines()
    tokens, keywords, punctuators = read_tokens(token_lines)
    if len(tokens) == 0:
        print("Error: no tokens found in the input stream.")
        exit(1)

    # Create and write to the header file
    header_fname = ofilename + ".h"
    with open(header_fname, 'w') as header_file:
        header_file.write(header_guard_top())
        header_file.write(includes(["<string>"]))
        header_file.write(token_enum(tokens))
        header_file.write(token_struct())
        header_file.write(token_string_proto())
        header_file.write(reserved_keyword_proto())
        header_file.write(punctuator_proto())
        header_file.write(header_guard_bottom())

    # Create and write to the implementation file
    cpp_fname = ofilename + ".cpp"
    header_base = "\"" + os.path.basename(header_fname) + "\""
    with open(cpp_fname, 'w') as cpp_file:
        cpp_file.write(includes([header_base, "<string>", "<array>",
                                "<unordered_map>", "<iostream>"]))
        cpp_file.write(token_string_fcn(tokens))
        cpp_file.write(reserved_keyword_fcn(keywords))
        cpp_file.write(punctuator_fcn(punctuators))

if __name__ == '__main__':

    if (len(sys.argv) != 3):
        print("Error creating 'token' header. Inalid number of CL arguments.")
        exit(1)

    ifilename = sys.argv[1]
    ofilename = sys.argv[2]

    if (ifilename[-3:] != ".in"):
        print("Invalid input filename: \"" + ifilename + "\".")
        exit(1)

    else:
        main(ifilename, ofilename)
