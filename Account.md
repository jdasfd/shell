# Add user and build an env

## Create an account

```bash
# change default shell from /bin/sh to /bin/bash
sudo useradd -D -s /bin/bash

# create new account
sudo useradd -m -s /bin/bash wzy01
# -m: create /home/wzy01
# -s: use /bin/bash as the default shell

# set new passwd
sudo passwd wzy01
# type 2 times
```

## Software management

### Python

- OpenSSL (leading to pip wrong)

```bash
cd ~/biosoft
wget https://www.openssl.org/source/openssl-1.1.1t.tar.gz

tar -zvxf openssl-1.1.1t.tar.gz
cd openssl-1.1.1t
./config --prefix=/home/wzy01/.openssl.1.1.1t --openssldir=/home/wzy01/.openssl.1.1.1t/openssl no-zlib
make
make install

# add path
echo "# local openssl.1.1.1" >> ~/.bashrc
echo 'export PATH=/home/wzy01/.openssl.1.1.1t/bin:$PATH' >> ~/.bashrc
echo "export LD_LIBRARY_PATH=/home/wzy01/.openssl.1.1.1t/lib:$LD_LIBRARY_PATH" >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc
```

- Python-3.7.16 (local python)

```bash
cd ~/biosoft
wget https://www.python.org/ftp/python/3.7.16/Python-3.7.16.tgz
tar -xvzf Python-3.7.16.tgz

cd Python-3.7.16
# make a dir under home
mkdir -p /home/wzy01/.python3.7.16/
./configure --prefix="/home/wzy01/.python3.7.16/"
# change SSL setup
vim Modules/Setup
# uncomment the code below and change SSL to local openssl
#SSL=/home/wzy01/.openssl.1.1.1t
#_ssl _ssl.c \
#        -DUSE_SSL -I$(SSL)/include -I$(SSL)/include/openssl \
#        -L$(SSL)/lib -lssl -lcrypto
export LD_LIBRARY_PATH=/home/wzy01/.openssl-1.1.1t/lib:$LD_LIBRARY_PATH
make
make install

# add path
echo "# local python" >> ~/.bashrc
echo 'export PATH=/home/wzy01/.python3.7.16/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc
```

### Resolve /usr/bin/env: ‘python’

In some cases, a problem may show up like `/usr/bin/env: ‘python’: No such file or directory` under a rooted account or `/usr/bin/env: ‘python’: Permision denied` under an unrooted account. The reason now I guess is the python2 and python3 problem. In Ubuntu, `python` is referred to python2 and `python3` is referred to python3 as far as I know. There are usually some software supporting python2 and python3. It is the goal that you let the software know that `python` is python3 but not python2. A simple way to solve this problem is `sudo apt install python-is-python3`. In the case of building env for an unrooted account, I decide to use `sudo ln -s` to use the user's python3.

```bash
# root your account
sudo ln -s /home/wzy01/.python3.7.16/bin/python3 /usr/bin/python
```

### Other useful tools download globally

- Minimap2

```bash
cd ~/biosoft

# install and make
git clone https://github.com/lh3/minimap2
cd minimap2 && make

# add path
echo "# minimap2" >> ~/.bashrc
echo 'export PATH=~/biosoft/minimap2:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

minimap2 -h
```

- Hifiasm

```bash
cd ~/biosoft

# install and make
git clone https://github.com/chhylp123/hifiasm.git
cd hifiasm && make

# add path
echo "# hifiasm" >> ~/.bashrc
echo 'export PATH=~/biosoft/hifiasm:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

hifiasm -h
```

- Purge_Dups (v.1.2.5)

```bash
cd ~/biosoft

git clone https://github.com/dfguan/purge_dups.git
cd purge_dups/src && make

# add path
echo "# purge_dups" >> ~/.bashrc
echo 'export PATH=~/biosoft/purge_dups/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

purge_dups -h
```

- NextDenovo

May influenced by the problem [Resolve /usr/bin/env: ‘python’](#resolve-usrbinenv--python).

```bash
cd ~/biosoft
pip3 install paralleltask

# install and make
git clone https://github.com/Nextomics/NextDenovo.git
cd NextDenovo && make

# add path
echo "# nextDenovo" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/NextDenovo:$PATH' >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/NextDenovo/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

nextDenovo -h
minimap2-nd -h
```

- MEGAHIT (v.1.2.9)

May influenced by the problem [Resolve /usr/bin/env: ‘python’](#resolve-usrbinenv--python).

```bash
cd ~/biosoft

wget https://github.com/voutcn/megahit/releases/download/v1.2.9/MEGAHIT-1.2.9-Linux-x86_64-static.tar.gz
tar zvxf MEGAHIT-1.2.9-Linux-x86_64-static.tar.gz
mv MEGAHIT-1.2.9-Linux-x86_64-static megahit

# add path
echo "# megahit" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/megahit/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

megahit -h
```

- SNAP

```bash
cd ~/biosoft
git clone https://github.com/KorfLab/SNAP.git

cd SNAP && make

# add path
echo "# SNAP" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/SNAP:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

snap -help
```

- ParaAT (v.2.0)

```bash
cd ~/biosoft
git clone https://github.com/wonaya/ParaAT.git

# add path
echo "# ParaAT" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/ParaAT:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

ParaAT.pl -help
```

- RepeatMasker (v.4.1.5)

```bash
cd ~/biosoft
# RMBlast dep
wget https://www.repeatmasker.org/rmblast/rmblast-2.13.0+-x64-linux.tar.gz
tar -xzvf rmblast-2.13.0+-x64-linux.tar.gz

# add path
echo "# rmblast" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/rmblast-2.13.0/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

# trf dep
git clone https://github.com/Benson-Genomics-Lab/TRF.git
cd TRF
mkdir build
cd build
../configure
make

echo "# trf" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/TRF/build/src:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

wget http://www.repeatmasker.org/RepeatMasker/RepeatMasker-4.1.5.tar.gz
tar -xzvf RepeatMasker-4.1.5.tar.gz
cd RepeatMasker
perl ./configure
# input following codes:
#/home/wzy01/biosoft/TRF/build/src/trf
#/home/wzy01/biosoft/rmblast-2.13.0/bin

echo "# RepeatMasker" >> ~/.bashrc
echo 'export PATH=/home/wzy01/biosoft/RepeatMasker:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

# default search engine is rmblast
# please modified to your own search engine
RepeatMasker -h
```

```


### Conda env

- Anaconda

Conda could be installed via unrooted settings.

```bash
cd ~/biosoft
wget https://repo.anaconda.com/archive/Anaconda3-2023.03-Linux-x86_64.sh

bash Anaconda3-2023.03-Linux-x86_64.sh
conda config --set auto_activate_base false
```

- EDTA

```bash
cd ~/biosoft
git clone https://github.com/oushujun/EDTA.git

conda env create -f EDTA/EDTA.yml -n tools

conda activate tools
EDTA.pl --help
```

- OrthoFinder

```bash
conda config --add channels defaults
conda config --add channels bioconda
conda config --add channels conda-forge

conda install -n tools orthofinder
```

```

## References

- [useradd](https://blog.csdn.net/yeahpeople/article/details/116454475)
- [unrooted_account_ssl_solution_1](https://blog.csdn.net/qq_54029683/article/details/113774724)
- [unrooted_account_ssl_solution_2](https://www.jianshu.com/p/c454631f8f82)
- [/usr/bin/env:python_solution](https://askubuntu.com/questions/942930/usr-bin-env-python-no-such-file-or-directory)
