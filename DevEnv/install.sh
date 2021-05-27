#!/bin/bash

git submodule init
git submodule update

bundledir=$HOME/.vim/bundle
if [ -e $bundledir ]; then
    echo "$bundledir already exists.\n"
else
    echo "$bundledir is made.\n"
    mkdir -p $bundledir
fi
echo "Vundle.vim is copied to $bundledir\n"
cp -r Vundle.vim $bundledir

molokaidir=$HOME/.vim/bundle/molokai
if [ -e $molokaidir ]; then
    echo "$molokaidir already exists.\n"
else
    echo "$molokaidir is made.\n"
    mkdir -p $molokaidir
fi
echo "molokai is copied to $bundledir\n"
cp -r molokai $bundledir
cp -r molokai/colors $HOME/.vim/colors

vimrc=$HOME/.vimrc
if [ -e $vimrc ]; then
    read -p $vimrc" already exists. Do you overwrite it? (y/N): " yn
    case "$yn" in [yY]*) ;; *) echo "abort." ; exit ;; esac
else
    echo ".vimrc is copied to $HOME"
fi

cp .vimrc $HOME

echo "Installing bundle plugins..."
vim -c "BundleUpdate" -c qa

echo "Installing YouCompleteMe..."
cd $bundledir/YouCompleteMe
sudo apt install build-essential cmake vim-nox python3-dev
sudo apt install mono-complete golang nodejs default-jdk npm
python3 install.py --all

echo "Install python syntax checker..."
sudo apt install -y python3-pip pylint flake8
python3 -m pip install pylint flake8

echo "Downloading SKK dictionary..."
curl -O http://openlab.jp/skk/dic/SKK-JISYO.L.gz

eskk=$HOME/.eskk
if [ -e $eskk ]; then
    echo "$eskk already exists.\n"
else
    mkdir -p $eskk
    echo "$eskk is made.\n"
fi
gzip -d SKK-JISYO.L.gz
mv SKK-JISYO.L $eskk

echo "copying templates..."
cp ./templates/* ~/.vim/bundle/vim-template/templates

echo "Complete."
