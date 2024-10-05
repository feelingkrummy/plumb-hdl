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
    PTT_EOF, 
    
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

const char* plumbtokentype_strings[] = {
    [PTT_Invalid]           = "Invalid",
    [PTT_EOF]               = "EOF",

    [PTT_LeftParen]         = "(", 
    [PTT_RightParen]        = ")", 
    [PTT_LeftBrace]         = "{", 
    [PTT_RightBrace]        = "}", 
    [PTT_LeftBracket]       = "[", 
    [PTT_RightBracket]      = "]", 
    [PTT_Plus]              = "+", 
    [PTT_Minus]             = "-", 
    [PTT_Star]              = "*", 
    [PTT_Slash]             = "/", 
    [PTT_Colon]             = ":", 
    [PTT_SemiColon]         = ";", 
    [PTT_Equal]             = "=", 
    [PTT_EqualEqual]        = "==",
    [PTT_Bang]              = "!",
    [PTT_BangEqual]         = "!=",
    [PTT_LeftArrow]         = ">",
    [PTT_LeftArrowEqual]    = ">=",
    [PTT_RightArrow]        = "<",
    [PTT_RightArrowEqual]   = "<=",
    
    [PTT_Ident]             = "ident",

    // Begin Keywords
    // These must be in alphabetical order
    // so the is_keyword binary search works
    // correctly
    [PTT_And]               = "and",
    [PTT_Begin]             = "begin",
    [PTT_End]               = "end",
    [PTT_Input]             = "input",
    [PTT_Logic]             = "logic",
    [PTT_Module]            = "module",
    [PTT_Nand]              = "nand",
    [PTT_Nor]               = "nor",
    [PTT_Not]               = "not",
    [PTT_Or]                = "or",
    [PTT_Output]            = "output",
    [PTT_Xnor]              = "xnor",
    [PTT_Xor]               = "xor"
    // End Keywords

};

typedef struct {
    uint32_t pos;
    PlumbTokenType type;
} PlumbToken;

typedef struct {
    uint64_t cap;
    uint64_t len;
    PlumbToken* tokens;
} TokenList;

#endif
