#include "common/str.h"
#include "plumb_elab/tokens.h"

const str8 plumbtokentype_str8[] = {
    [PTT_Invalid]           = STR8("Invalid"),
    [PTT_Eof]               = STR8("EOF"),

    [PTT_LeftParen]         = STR8("("), 
    [PTT_RightParen]        = STR8(")"), 
    [PTT_LeftBrace]         = STR8("{"), 
    [PTT_RightBrace]        = STR8("}"), 
    [PTT_LeftBracket]       = STR8("["), 
    [PTT_RightBracket]      = STR8("]"), 
    [PTT_Plus]              = STR8("+"), 
    [PTT_Minus]             = STR8("-"), 
    [PTT_Slash]             = STR8("/"), 
    [PTT_Colon]             = STR8(":"), 
    [PTT_SemiColon]         = STR8(";"), 

    [PTT_Star]              = STR8("*"), 
    [PTT_StarStar]          = STR8("**"), 
    [PTT_Equal]             = STR8("="), 
    [PTT_EqualEqual]        = STR8("=="),
    [PTT_Bang]              = STR8("!"),
    [PTT_BangEqual]         = STR8("!="),
    [PTT_LeftArrow]         = STR8(">"),
    [PTT_LeftArrowEqual]    = STR8(">="),
    [PTT_RightArrow]        = STR8("<"),
    [PTT_RightArrowEqual]   = STR8("<="),
    
    [PTT_Ident]             = STR8("ident"),

    // Begin Keywords
    // These must be in alphabetical order
    // so the is_keyword binary search works
    // correctly
    [PTT_And]               = STR8("and"),
    [PTT_Begin]             = STR8("begin"),
    [PTT_End]               = STR8("end"),
    [PTT_Input]             = STR8("input"),
    [PTT_Logic]             = STR8("logic"),
    [PTT_Module]            = STR8("module"),
    [PTT_Nand]              = STR8("nand"),
    [PTT_Nor]               = STR8("nor"),
    [PTT_Not]               = STR8("not"),
    [PTT_Or]                = STR8("or"),
    [PTT_Output]            = STR8("output"),
    [PTT_Xnor]              = STR8("xnor"),
    [PTT_Xor]               = STR8("xor")
    // End Keywords

};
