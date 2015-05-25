" Bebop syntax file for vim.
" Install to ~/.vim/syntax
" Chris Laverdiere 2015
"
" Credit to http://learnvimscriptthehardway.stevelosh.com/chapters/45.html

if exists("b:current_syntax")
  finish
endif

" Keywords
syntax keyword bebopKeyword if while fin
syntax keyword bebopKeyword break continue return
syntax keyword bebopKeyword not and or
syntax keyword bebopKeyword true false
syntax keyword bebopType bool int float none string type
syntax keyword bebopKeyword say write

" Matched constructs
syntax match bebopComment "<>.*"
syntax match bebopOperator "[\+\-\*\/\%\=]"
syntax region bebopString start=/"/ end=/"/

" Highlighting links
highlight link bebopComment Comment
highlight link bebopKeyword Keyword
highlight link bebopOperator Operator
highlight link bebopType Type
highlight link bebopString String

let b:current_syntax = "bebop"
