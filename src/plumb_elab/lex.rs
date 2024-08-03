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
    fn next_token(&mut self) -> Option<LexResult> {
        self.skip_whitespace();
        match self.chars.next() {
            Some((pos, c)) => {
                self.start = pos;
                self.current = pos;
                if let Some(tok) = self.match_single_char_token(c) {
                    return Some(Ok(tok))
                }
                return Some(Err(LexError::UnexpectedCharacter(c)));
            }
            None => None,
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
            '=' => Some(self.switch('=', TokenType::EqualEqual, TokenType::Equal)),
            _ => None,
        }
    }

    
    fn switch(&mut self, next_char: char, if_next_char: TokenType<'src>, if_not_next: TokenType<'src>) -> Token<'src> {
        match self.chars.peek() {
            Some((pos, next_char)) => {
                let tok = Token {
                    token_type: if_next_char,
                    line: self.line,
                    col: self.col,
                };
                self.current = *pos;
                self.col += 2;
                _ = self.chars.next();
                return tok;
            }
            _ => {
                let tok = Token {
                    token_type: if_not_next,
                    line: self.line,
                    col: self.col,
                };
                self.col += 1;
                return tok;
            }
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
