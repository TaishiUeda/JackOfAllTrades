set nu
set rnu
set shiftwidth=4
set autoindent
set smartindent
set backspace=indent,eol,start
set encoding=utf-8

" Don't write backup file if vim is being called by "crontab -e"
au BufWrite /private/tmp/crontab.* set nowritebackup nobackup
" Don't write backup file if vim is being called by "chpass"
au BufWrite /private/etc/pw.* set nowritebackup nobackup

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

"-------- add pulgins from here ------
Plugin 'VundleVim/Vundle.vim'
"tag jump
Plugin 'lyuts/vim-rtags'
"novel c-completer
Plugin 'Valloric/YouCompleteMe'
"python syntax checker
Plugin 'dense-analysis/ale'
"simple template
Plugin 'aperezdc/vim-template'
"terminal in buffer
Plugin 'wkentaro/conque.vim'
"SKK for vim
Plugin 'tyru/eskk.vim'
"tag jump extention for xml files
Plugin 'tmhedberg/matchit'
"molokai color scheme
Plugin 'tomasr/molokai'
"--------- end -----------------------

call vundle#end()            " required
filetype plugin indent on    " required

"----- key map for conuqe term -----
noremap mx :ConqueTerm zsh
noremap vmx :ConqueTermVSplit zsh
noremap nmx :ConqueTermSplit zsh

"----- set xml syntax as ros config syntax ----
autocmd! BufRead,BufNewFile *.launch setfiletype xml
autocmd! BufRead,BufNewFile *.urdf setfiletype xml

"----- setting for eskk -----
" language mes en_US.utf8
let g:eskk#directory = "~/.eskk"
let g:eskk#large_dictionary = { 'path': "~/.eskk/SKK-JISYO.L", 'sorted':1, 'encoding': 'euc-jp', }
let g:eskk#dictionary = { 'path': "~/.eskk/.skk-jisyo", 'sorted':0, 'encoding': 'utf-8', }

"----- setting for color scheme -----
syntax enable
colorscheme molokai
set t_Co=256
hi Normal ctermbg=none

