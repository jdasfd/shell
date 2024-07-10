# How to manage all packages on the linux platform

## Packages

### nwr

```bash
cd ~/share

brew install rust
git clone https://github.com/wang-q/nwr.git

cd nwr
export CARGO_TARGET_DIR=/tmp
cargo build
cargo install --path . --force --offline

# echo .cargo to path
echo "# cargo" >> ~/.bashrc
echo 'export PATH=$PATH:~/.cargo/bin' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

# install all info
nwr download
nwr txdb
nwr ardb
nwr ardb --genbank
```

## Packages on HPC

### Python3

```bash
pip3 config set global.index-url https://mirror.nju.edu.cn/pypi/web/simple/
pip3 install --upgrade pip
```

### OrthoFinder

- mcl

```bash
mkdir -p ~/software/local
cd ~/software/packages
wget http://micans.org/mcl/src/mcl-22-282.tar.gz
wget http://micans.org/mcl/src/cimfomfa-22-273.tar.gz
# upload to the HPC

cd ~/software
tar xzf packages/cimfomfa-22-273.tar.gz
cd cimfomfa-22-273
./configure --prefix=/share/home/zhuqingshao/software/local --disable-shared
make
make install

cd ~/software
tar xzf packages/mcl-22-282.tar.gz
cd mcl-22-282.tar.gz
./configure CFLAGS=-I/share/home/zhuqingshao/software/local/include LDFLAGS=-L/share/home/zhuqingshao/software/local/lib --prefix=/share/home/zhuqingshao/software/local --enable-rcl
make
make install

# export path to .bashrc
# source ~/.bashrc
```

- diamond

```bash
cd ~/software/local/bin
tar xzvf ~/software/packages/diamond-linux64.tar.gz

diamond help
```

- fastme

```bash
cd ~/software/packages
wget http://www.atgc-montpellier.fr/download/sources/fastme/fastme-2.1.6.4.tar.gz

cd ~/software
tar xzvf packages/fastme-2.1.6.4.tar.gz
cp ~/software/fastme-2.1.6.4/binaries/fastme-2.1.6.2-linux64 ~/software/local/bin/fastme

fastme -h
```

- mafft

```bash
cd ~/software/packages
wget https://mafft.cbrc.jp/alignment/software/mafft-7.526-with-extensions-src.tgz

tar xfvz packages/mafft-7.526-with-extensions-src.tgz
cd mafft-7.526-with-extensions-src/core/
vim Makefile
# PREFIX = /share/home/zhuqingshao/software/local
make clean
make
make install

mafft -h
```

- fasttree

```bash
cd ~/software/local/bin
wget http://meta.microbesonline.org/fasttree/FastTree
chmod ugo+x FastTree

FastTree -h
```

- iqtree

```bash
cd ~/software/packages
wget https://github.com/Cibiv/IQ-TREE/releases/download/v1.6.12/iqtree-1.6.12-Linux.tar.gz

cd ~/software
tar xzvf packages/iqtree-1.6.12-Linux.tar.gz

cp iqtree-1.6.12-Linux/bin/iqtree ~/software/local/bin
iqtree -h
```

- Orthofinder

```bash
cd ~/software/packages
wget https://github.com/davidemms/OrthoFinder/releases/download/2.5.5/OrthoFinder_source.tar.gz

tar xzvf packages/OrthoFinder_source.tar.gz
pip3 install numpy
pip3 install scipy
cp OrthoFinder_source/orthofinder.py ~/software/local/bin/orthofinder
cp -r OrthoFinder_source/scripts_of ~/software/local/bin/

orthofinder -h
```

## References

- [apt,apt-get,aptitude](https://linuxgenie.net/difference-between-apt-apt-get-and-aptitude/#:~:text=In%20summary%2C%20apt%2C%20apt-get%2C%20and%20aptitude%20are%20all,it%20can%20also%20be%20more%20complex%20to%20use.)
