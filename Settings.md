# My settings

## How to modified R 4.3.0

After my test, I realized that my linux R could only accept http for softwares downloading, which means all https web would return a mistake.

Do the following to create a ~/.Rprofile to change the default setting of R. The following codes were written by `R`, which means in linux you should type `R` in the terminal.

```R
file.edit('~/.Rprofile')
# my R only allow http proxy
options("repos" = c(CRAN="http://mirrors.tuna.tsinghua.edu.cn/CRAN/"))
options(BioC_mirror="http://mirrors.ustc.edu.cn/bioc/")

#:wq to save and exit vim
```

## Linuxbrew

```bash
echo "==> Tuna mirrors of Homebrew/Linuxbrew"
export HOMEBREW_BREW_GIT_REMOTE="https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/brew.git"
export HOMEBREW_CORE_GIT_REMOTE="https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/homebrew-core.git"
export HOMEBREW_BOTTLE_DOMAIN="https://mirrors.tuna.tsinghua.edu.cn/homebrew-bottles"

git clone --depth=1 https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/install.git brew-install
/bin/bash brew-install/install.sh

rm -rf brew-install

test -d ~/.linuxbrew && PATH="$HOME/.linuxbrew/bin:$HOME/.linuxbrew/sbin:$PATH"
test -d /home/linuxbrew/.linuxbrew && PATH="/home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:$PATH"

if grep -q -i Homebrew $HOME/.bashrc; then
    echo "==> .bashrc already contains Homebrew"
else
    echo "==> Update .bashrc"

    echo >> $HOME/.bashrc
    echo '# Homebrew' >> $HOME/.bashrc
    echo "export PATH='$(brew --prefix)/bin:$(brew --prefix)/sbin'":'"$PATH"' >> $HOME/.bashrc
    echo "export MANPATH='$(brew --prefix)/share/man'":'"$MANPATH"' >> $HOME/.bashrc
    echo "export INFOPATH='$(brew --prefix)/share/info'":'"$INFOPATH"' >> $HOME/.bashrc
    echo "export HOMEBREW_NO_ANALYTICS=1" >> $HOME/.bashrc
    echo "export HOMEBREW_NO_AUTO_UPDATE=1" >> $HOME/.bashrc
    echo 'export HOMEBREW_BREW_GIT_REMOTE="https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/brew.git"' >> $HOME/.bashrc
    echo 'export HOMEBREW_CORE_GIT_REMOTE="https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/homebrew-core.git"' >> $HOME/.bashrc
    echo 'export HOMEBREW_BOTTLE_DOMAIN="https://mirrors.tuna.tsinghua.edu.cn/homebrew-bottles"' >> $HOME/.bashrc
    echo >> $HOME/.bashrc
fi

source $HOME/.bashrc
```

## Install packages managed by Linuxbrew

```bash
bash $HOME/Scripts/shell/brew.sh
source $HOME/.bashrc
```

## Packages of each language

```bash
bash ~/Scripts/shell/perl/install.sh
bash ~/Scripts/dotfiles/python/install.sh
bash ~/Scripts/shell/r/install.sh
```
