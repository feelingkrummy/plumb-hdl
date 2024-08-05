use crate::plumb_elab::tokens::{TokenType, Token};
use std::iter::Peekable;
use std::str::CharIndices;

enum LexError {
    UnexpectedCharacter(char),
}

pub struct Lexer<'src> {
    source : &'src str,
    chars : Peekable<CharIndices<'src>>,

    start : usize,
    current : usize,

    line: u64,
    col: u64,
}

type LexResult<'src> = Result<Token<'src>, LexError>;

impl<'src> Lexer<'src> {
    pub fn new(source: &'src str) -> Lexer {
        Lexer {
            source: source,
            chars: source.char_indices().peekable(),
            start: 0,
            current: 0,
            line: 0,
            col: 0,
        }
    }

    // fn scan_token(&mut self) -> Result<Token, String> {
    fn next_token(&mut self) -> LexResult {
        self.skip_whitespace();
        match self.chars.next() {
            Some((pos, c)) => {
                self.start = pos;
                self.current = pos;
                if let Some(tok) = self.match_single_char_token(c) {
                    return Ok(tok);
                }
                if let Some(tok) = self.match_double_char_token(c) {
                    return Ok(tok);
                }
                let start_line = self.line;
                let start_col = self.col;
                if let Some(lit) = self.parse_identifier(c) {
                    if let Some(tok) = self.match_keyword(lit, start_line, start_col) {
                        return Ok(tok);
                    }
                    let tok = Token{
                        token_type: TokenType::Identifier{literal: lit},
                        line: start_line,
                        col: start_col
                    };
                    return Ok(tok);
                }
                return Err(LexError::UnexpectedCharacter(c));
            }
            None => Ok(Token{token_type: TokenType::Eof, line: line, col: col}),
        }
    }

    fn match_single_char_token(&mut self, c: char) -> Option<Token<'src>> {
        let token_type : TokenType<'src>;
        match c {
            '(' => token_type = TokenType::LeftParen,
            ')' => token_type = TokenType::RightParen,
            '{' => token_type = TokenType::LeftBrace,
            '}' => token_type = TokenType::RightBrace,
            '[' => token_type = TokenType::LeftBracket,
            ']' => token_type = TokenType::RightBracket,
            '+' => token_type = TokenType::Plus,
            '-' => token_type = TokenType::Minus,
            '*' => token_type = TokenType::Star,
            '/' => token_type = TokenType::Slash,
            ':' => token_type = TokenType::Colon,
            ';' => token_type = TokenType::SemiColon,
            _ => return None,
        }
        let tok = Token{
            token_type: token_type,
            line: self.line,
            col: self.col,
        };
        self.col += 1;
        return Some(tok);
    }

    fn match_double_char_token(&mut self, c: char) -> Option<Token<'src>> {
        match c {
            '=' => Some(self.match_if_or('=', TokenType::EqualEqual,        TokenType::Equal)),
            '!' => Some(self.match_if_or('=', TokenType::BangEqual,         TokenType::Bang)),
            '<' => Some(self.match_if_or('=', TokenType::LeftArrowEqual,    TokenType::LeftArrow)),
            '>' => Some(self.match_if_or('=', TokenType::RightArrowEqual,   TokenType::RightArrow)),
            _ => None,
        }
    }

    fn match_if_or(&mut self, next_char: char, if_next_char: TokenType<'src>, if_not_next: TokenType<'src>) -> Token<'src> {
        if let Some((pos, c)) = self.chars.peek() {
            if *c == next_char {
                let tok = Token {
                    token_type: if_next_char,
                    line: self.line,
                    col: self.col,
                };
                self.current = *pos;
                self.col += 2;
                _ = self.chars.next();
                return tok;
            } else {
                let tok = Token {
                    token_type: if_not_next,
                    line: self.line,
                    col: self.col,
                };
                self.col += 1;
                return tok;
            }
        } else {
            let tok = Token {
                token_type: if_not_next,
                line: self.line,
                col: self.col,
            };
            self.col += 1;
            return tok;
        }
    }

    fn parse_identifier(&mut self, c: char) -> Option<&'src str> {
        if c.is_alphabetic() {
            while let Some((pos, _next_char)) = self.chars.peek() {
                if _next_char.is_alphanumeric() {
                    self.current = *pos;
                    self.col += 1;
                    _ = self.chars.next();
                } else {
                    break;
                }
            }
            return Some(&self.source[self.start..self.current]);
        } else {
            return None;
        }
    }

    fn match_keyword(&mut self, lit: &str, line: u64, col: u64) -> Option<Token<'src>> {
        match lit {
            "begin" => Some(Token{token_type: TokenType::Begin, line: line, col: col}),
            "end" => Some(Token{token_type: TokenType::End, line: line, col: col}),
            "module" => Some(Token{token_type: TokenType::Module, line: line, col: col}),
            "input" => Some(Token{token_type: TokenType::Input, line: line, col: col}),
            "output" => Some(Token{token_type: TokenType::Output, line: line, col: col}),
            "not" => Some(Token{token_type: TokenType::Not, line: line, col: col}),
            "and" => Some(Token{token_type: TokenType::And, line: line, col: col}),
            "nand" => Some(Token{token_type: TokenType::Nand, line: line, col: col}),
            "or" => Some(Token{token_type: TokenType::Or, line: line, col: col}),
            "nor" => Some(Token{token_type: TokenType::Nor, line: line, col: col}),
            "xor" => Some(Token{token_type: TokenType::Xor, line: line, col: col}),
            "xnor" => Some(Token{token_type: TokenType::Xnor, line: line, col: col}),
            &_ => None,
        }
    }

    fn skip_whitespace(&mut self) {
        while let Some((i, c)) = self.chars.peek() {
            if c.is_whitespace() {
                if *c == '\n' {
                    self.line += 1;
                    self.col = 0;
                } else {
                    self.col += 1;
                }
                self.current = *i;
                _ = self.chars.next();
            } else {
                break;
            }
        }
    }
}
