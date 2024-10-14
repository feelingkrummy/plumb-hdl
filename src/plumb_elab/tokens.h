/*
Copyright 2024 Kameron A. Rummel 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef PLUMB_TOKENS_H_
#define PLUMB_TOKENS_H_

#include <stdint.h>

typedef enum PlumbTokenType {
    PTT_Invalid = 0, 
    PTT_Eof, 
    
    // Single Char Tokens
    PTT_LeftParen, 
    PTT_RightParen, 
    PTT_LeftBrace, 
    PTT_RightBrace, 
    PTT_LeftBracket, 
    PTT_RightBracket, 
    PTT_Plus, 
    PTT_Minus, 
    PTT_Slash, 
    PTT_Colon, 
    PTT_SemiColon, 

    // Double Char Token
    PTT_Star, 
    PTT_StarStar, 
    PTT_Equal, 
    PTT_EqualEqual, 
    PTT_Bang, 
    PTT_BangEqual, 
    PTT_LeftArrow, 
    PTT_LeftArrowEqual, 
    PTT_RightArrow, 
    PTT_RightArrowEqual, 
    
    PTT_Ident,
   
    // Begin Keywords
    // These must be in alphabetical order
    // so the is_keyword binary search works
    // correctly
    PTT_And, 
    PTT_Begin, 
    PTT_End, 
    PTT_Input, 
    PTT_Logic, 
    PTT_Module, 
    PTT_Nand, 
    PTT_Nor, 
    PTT_Not, 
    PTT_Or, 
    PTT_Output, 
    PTT_Xnor,
    PTT_Xor
    // End Keywords
} PlumbTokenType;

str8 plumbtokentype_str8[] = {
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

typedef struct {
    uint32_t line;
    uint32_t col;
} PlumbTokenLoc;

#define INIT_LOCATION {.line=1, .col=1}

typedef struct {
    PlumbTokenLoc loc;
    PlumbTokenType type;
    union {
        str8 ident;
    }
} PlumbToken;

typedef struct {
    uint64_t cap;
    uint64_t len;
    PlumbToken* tokens;
} TokenList;

#endif
