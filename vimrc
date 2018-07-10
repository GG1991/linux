set enc=utf-8
set fenc=utf-8
set termencoding=utf-8

" move among buffers with CTRL
map <C-J> :bnext<CR>
map <C-K> :bprev<CR>

if &term =~ "xterm\\|rxvt"
  " use an orange cursor in insert mode
  let &t_SI = "\<Esc>]12;orange\x7"
  " use a red cursor otherwise
  let &t_EI = "\<Esc>]12;red\x7"
  silent !echo -ne "\033]12;red\007"
  " reset cursor when vim exits
  autocmd VimLeave * silent !echo -ne "\033]112\007"
  " use \003]12;gray\007 for gnome-terminal
endif

" disable vi compatibility (emulation of old bugs)
set nocompatible
set noet ci pi sts=0 sw=4 ts=4
set textwidth=80

" turn syntax highlighting on
set t_Co=256
syntax on
colorscheme torte
set number

" highlight matching braces
" set showmatch
" intelligent comments
set comments=sl:/*,mb:\ *,elx:\ */
map <C-c> :s/^/\/\//<Enter>
map <C-p> :s/^\/\///<Enter>
map <C-e> :setlocal spell spelllang=en_us<Enter>
map <C-t> :set nospell<Enter>

" Enhanced keyboard mappings
" in normal mode F2 will save the file
nmap <F2> :w<CR>
" in insert mode F2 will exit insert, save, enters insert again
imap <F2> <ESC>:w<CR>i
" switch between header/source with F4
map <F4> :e %:p:s,.h$,.X123X,:s,.cpp$,.h,:s,.X123X$,.cpp,<CR>
" recreate tags file with F5
map <F5> :!ctags -R –c++-kinds=+p –fields=+iaS –extra=+q .<CR>
" goto definition with F12
map <F12> <C-]>
" in diff mode we use the spell check keys for merging
if &diff
" diff settings
  map <M-Down> ]c
  map <M-Up> [c
  map <M-Left> do
  map <M-Right> dp
  map <F9> :new<CR>:read !svn diff<CR>:set syntax=diff buftype=nofile<CR>gg
else
  " spell settings
  ":setlocal spell spelllang=en
  " set the spellfile - folders must exist
  set spellfile=~/.vim/spellfile.add
  map <M-Down> ]s
  map <M-Up> [s
endif

" colors
highlight Comment ctermfg=LightCyan
