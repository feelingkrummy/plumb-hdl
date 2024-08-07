use crate::plumb_elab::tokens::{TokenType, Token};
use std::iter::Peekable;
use std::str::CharIndices;

#[derive(Debug)]
pub enum LexError {
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
            line: 1,
            // col: 0,
            col: 1,
        }
    }

    // fn scan_token(&mut self) -> Result<Token, String> {
    fn next_token(&mut self) -> LexResult<'src> {
        self.skip_whitespace();
        match self.chars.next() {
            Some((pos, c)) => {
                //self.col += 1;
                self.start = pos;
                self.current = pos;
                eprintln!("Starting Token, Col : {}, Line : {}", self.col, self.line);
                if let Some(tok) = self.match_single_char_token(c) {
                    eprintln!("Ending Single Char Token, Col : {}, Line : {}", self.col, self.line);
                    return Ok(tok);
                }
                if let Some(tok) = self.match_double_char_token(c) {
                    eprintln!("Ending Double Char Token, Col : {}, Line : {}", self.col, self.line);
                    return Ok(tok);
                }
                let start_line = self.line;
                let start_col = self.col;
                if let Some(lit) = self.parse_identifier(c) {
                    if let Some(tok) = self.match_keyword(lit, start_line, start_col) {
                        eprintln!("Ending Keyword Token, Col : {}, Line : {}", self.col, self.line);
                        return Ok(tok);
                    }
                    let tok = Token{
                        token_type: TokenType::Identifier{literal: lit},
                        line: start_line,
                        col: start_col
                    };
                    eprintln!("Ending Ident Token, Col : {}, Line : {}", self.col, self.line);
                    return Ok(tok);
                }
                return Err(LexError::UnexpectedCharacter(c));
            }
            None => Ok(Token{token_type: TokenType::Eof, line: self.line, col: self.col}),
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
            let mut last_char : char = c;
            // Increase column count at least one for current character
            self.col += 1;
            while let Some((pos, next_char)) = self.chars.peek() {
                if next_char.is_alphanumeric() {
                    last_char = *next_char;
                    self.current = *pos;
                    // Increase column for each additional character
                    self.col += 1;
                    _ = self.chars.next();
                } else {
                    break;
                }
            }
            return Some(&self.source[self.start..(self.current+last_char.len_utf8())]);
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

            "lsl" => Some(Token{token_type: TokenType::Lsl, line: line, col: col}),
            "lsr" => Some(Token{token_type: TokenType::Lsr, line: line, col: col}),
            "asl" => Some(Token{token_type: TokenType::Asl, line: line, col: col}),
            "asr" => Some(Token{token_type: TokenType::Asr, line: line, col: col}),
            "rol" => Some(Token{token_type: TokenType::Rol, line: line, col: col}),
            "ror" => Some(Token{token_type: TokenType::Ror, line: line, col: col}),

            "logic" => Some(Token{token_type: TokenType::Logic, line: line, col: col}),
            &_ => None,
        }
    }

    fn skip_whitespace(&mut self) {
        while let Some((i, c)) = self.chars.peek() {
            if c.is_whitespace() {
                if *c == '\n' {
                    self.line += 1;
                    self.col = 1;
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

impl<'src> Iterator for Lexer<'src> {
    type Item = LexResult<'src>;

    fn next(&mut self) -> Option<Self::Item> {
        let result = self.next_token();
        // match self.next_token() {
        match result {
            Ok(t) => {
                if t.token_type == TokenType::Eof {
                    return None;
                } else {
                    return Some(Ok(t));
                }
            },
            Err(e) => return Some(Err(e)),
        }
    }
}

#[allow(dead_code)]
mod test {
    use super::*;

    const LOGICAL_KEYWORDS : &str = "and nand or nor xor xnor";
    const RELATIONAL_KEYWORDS : &str = "== != < <= > >=";
    const SHIFT_KEYWORDS : &str = "lsl lsr asl asr rol ror";
    const MATH_OP_KEYWORDS : &str = "+ - * / =";
    const AND_GATE_INPUT : &str =
"module AndGate (
    a   : input logic;
    b   : input logic;
    q   : output logic;
) begin

q = a and b;

end module";

    fn scan_tokens(string: &str) -> Vec<Token> {
        let mut toks = Vec::<Token>::with_capacity(7);
        for result in Lexer::new(string) {
            match result {
                Ok(t) => toks.push(t),
                Err(e) => panic!("Error encountered while lexing logical keywords : {:?}", e),
            }
        }
        return toks;
    }

    #[test]
    fn logical_keywords() {
        let toks = scan_tokens(test::LOGICAL_KEYWORDS);
        let expected_toks = vec!(
            Token{ token_type: TokenType::And, line: 1, col: 1 },
            Token{ token_type: TokenType::Nand, line: 1, col: 5 },
            Token{ token_type: TokenType::Or, line: 1, col: 10 },
            Token{ token_type: TokenType::Nor, line: 1, col: 13 },
            Token{ token_type: TokenType::Xor, line: 1, col: 17 },
            Token{ token_type: TokenType::Xnor, line: 1, col: 21 },
        );
        assert_eq!(toks, expected_toks);
    }

    #[test]
    fn relational_keywords() {
        let toks = scan_tokens(test::RELATIONAL_KEYWORDS);
        let expected_toks = vec!(
            Token{ token_type: TokenType::EqualEqual, line: 1, col: 1 },
            Token{ token_type: TokenType::BangEqual, line: 1, col: 4 },
            Token{ token_type: TokenType::LeftArrow, line: 1, col: 7 },
            Token{ token_type: TokenType::LeftArrowEqual, line: 1, col: 9 },
            Token{ token_type: TokenType::RightArrow, line: 1, col: 12 },
            Token{ token_type: TokenType::RightArrowEqual, line: 1, col: 14 },
        );
        assert_eq!(toks, expected_toks);
    }

    #[test]
    fn shift_kewords() {
        let toks = scan_tokens(test::SHIFT_KEYWORDS);
        let expected_toks = vec!(
            Token{ token_type: TokenType::Lsl, line: 1, col: 1 },
            Token{ token_type: TokenType::Lsr, line: 1, col: 5 },
            Token{ token_type: TokenType::Asl, line: 1, col: 9 },
            Token{ token_type: TokenType::Asr, line: 1, col: 13 },
            Token{ token_type: TokenType::Rol, line: 1, col: 17 },
            Token{ token_type: TokenType::Ror, line: 1, col: 21 },
        );
        assert_eq!(toks, expected_toks);
    }

    #[test]
    fn math_op_keywords() {
        let toks = scan_tokens(test::MATH_OP_KEYWORDS);
        let expected_toks = vec!(
            Token{ token_type: TokenType::Plus, line: 1, col: 1 },
            Token{ token_type: TokenType::Minus, line: 1, col: 3 },
            Token{ token_type: TokenType::Star, line: 1, col: 5 },
            Token{ token_type: TokenType::Slash, line: 1, col: 7 },
            Token{ token_type: TokenType::Equal, line: 1, col: 9 },
        );
        assert_eq!(toks, expected_toks);
    }

    #[test]
    fn basic_module() {
        let toks = scan_tokens(test::AND_GATE_INPUT);
        let expected_toks = vec!(
            Token{ token_type: TokenType::Module, line: 1, col: 1 },
            Token{ token_type: TokenType::Identifier{ literal: "AndGate" }, line: 1, col: 8 },
            Token{ token_type: TokenType::LeftParen, line: 1, col: 16 },
            Token{ token_type: TokenType::Identifier{ literal: "a" }, line: 2, col: 5 },
            Token{ token_type: TokenType::Colon, line: 2, col: 9 },
            Token{ token_type: TokenType::Input, line: 2, col: 11 },
            Token{ token_type: TokenType::Logic, line: 2, col: 17 },
            Token{ token_type: TokenType::SemiColon, line: 2, col: 22 },
            Token{ token_type: TokenType::Identifier{ literal: "b" }, line: 3, col: 5 },
            Token{ token_type: TokenType::Colon, line: 3, col: 9 },
            Token{ token_type: TokenType::Input, line: 3, col: 11 },
            Token{ token_type: TokenType::Logic, line: 3, col: 17 },
            Token{ token_type: TokenType::SemiColon, line: 3, col: 22 },
            Token{ token_type: TokenType::Identifier{ literal: "q" }, line: 4, col: 5 },
            Token{ token_type: TokenType::Colon, line: 4, col: 9 },
            Token{ token_type: TokenType::Output, line: 4, col: 11 },
            Token{ token_type: TokenType::Logic, line: 4, col: 18 },
            Token{ token_type: TokenType::SemiColon, line: 4, col: 23 },
            Token{ token_type: TokenType::RightParen, line: 5, col: 1 },
            Token{ token_type: TokenType::Begin, line: 5, col: 3 },
            Token{ token_type: TokenType::Identifier{ literal: "q" }, line: 7, col: 1 },
            Token{ token_type: TokenType::Equal, line: 7, col: 3 },
            Token{ token_type: TokenType::Identifier{ literal: "a" }, line: 7, col: 5 },
            Token{ token_type: TokenType::And, line: 7, col: 7 },
            Token{ token_type: TokenType::Identifier{ literal: "b" }, line: 7, col: 11 },
            Token{ token_type: TokenType::SemiColon, line: 7, col: 12 },
            Token{ token_type: TokenType::End, line: 9, col: 1 },
            Token{ token_type: TokenType::Module, line: 9, col: 5 },
        );
        assert_eq!(toks, expected_toks);
    }
}
