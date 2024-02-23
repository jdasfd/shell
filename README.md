# Ubuntu env settings

This is a markdown which recorded all setting of my own env (rooted). There is also a markdown [here](https://github.com/jdasfd/shell/blob/main/Management.md) written all env building process of an unrooted account.

## Install packages needed by Linuxbrew and some others

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/jdasfd/shell/master/basic.sh)"
```

## Install linuxbrew

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

## Clone different repos

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/jdasfd/shell/master/download.sh)"
source $HOME/.bashrc
```


```bash
bash $HOME/Scripts/shell/brew.sh
source $HOME/.bashrc
```

## Env built

```bash
bash ~/Scripts/shell/perl/install.sh
bash ~/Scripts/dotfiles/python/install.sh
bash ~/Scripts/shell/r/install.sh
bash ~/Scripts/dotfiles/rust/install.sh
source ~/.bashrc
```

### R

- Manually install the package in R

Some packages failed in installing from the Internet. Manually install them is another solution.

```bash
cd /tmp

# stringi
wget https://github.com/gagolews/stringi/archive/master.zip -O stringi.zip
unzip stringi.zip
sed -i '/\/icu..\/data/d' stringi-master/.Rbuildignore
R CMD build stringi-master
```

- How to modified R 4.3.0

R version once always disturbing me. Now all my own R packages available under the R 4.3.0.

After my test, I realized that my linux R could only accept http for softwares downloading, which means all https web would return a mistake. So using http proxy instead of https to reduce mistakes.

```R
# file.edit('~/.Rprofile')
options("repos" = c(CRAN="http://mirrors.tuna.tsinghua.edu.cn/CRAN/"))
options(BioC_mirror="http://mirrors.ustc.edu.cn/bioc/")
```

## Symlink

```bash
ln -s /mnt/d/data/ ~/data
```
