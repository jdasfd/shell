# The HPCC environment

## How to solve the problem when build all dependencies from the source

The major path of all related files:

- local env

```bash
echo "# local env" >> ~/.bashrc
echo 'export PATH="/share/home/zhuqingshao/.local/bin:$PATH"' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH="/share/home/zhuqingshao/.local/lib:/share/home/zhuqingshao/.local/libexec:$LD_LIBRARY_PATH"' >> ~/.bashrc
echo 'export MANPATH="/share/home/zhuqingshao/.local/man:/share/home/zhuqingshao/.local/man/man1:$MANPATH"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc
```

### Scripts

- single file:

`${PATH}` or `cp [file] ${HOME}/.local/bin`

- multiple files (with Perl or Python modules):

`ln -s [file] ${HOME}/.local/bin` (allow files to find their modules in the relative path)

- with related setup or configuration files:

`./configure`

`python3 setup.py install`

### Build from the source

- Only with makefile

`grep "^install:" Makefile`: whether there is an install rule in the Makefile

if could be installed: `make` -> `make install PREFIX=[path]|BINDIR=[path]|prefix=[path]` (check the variable if make file could be read)

if not: `make` -> `${PATH}`

- autoconf

`./configure --prefix=${HOME}/.local`
`make`
`make install`

There are many variables could be related to `./configure`, check the help message:

`./configure --help`

### Solve the gcc library

For the code compatibility, the HPCC use the old version of the gcc and gcc library.

- Load new version of the gcc

`module avail`: check the available modules.

`module load gcc/gcc-11.5.0` to use the new version of the gcc and gcc library.

- Check the link of the library

`ldd $(which [package])`: give out the related library.

`ldconfig`: update the library cache.

## EDTA

`error while loading shared libraries: libbz2.so.1.0: cannot open shared object file: No such file or directory`

- bzip2 (v1.0.8)

```bash
cd ~/share
tar xzvf bzip2-latest.tar.gz
cd bzip2-1.0.8
make clean
make -f Makefile-libbz2_so -j4
make -j4
make install PREFIX=/share/home/zhuqingshao/.local

cp libbz2.so.1.0.8 /share/home/zhuqingshao/.local/lib/
cd $HOME/.local/lib
ln -sf libbz2.so.1.0.8 libbz2.so.1.0
ln -sf libbz2.so.1.0.8 libbz2.so.1
ln -sf libbz2.so.1.0 libbz2.so
```

`error while loading shared libraries: libzstd.so.1: cannot open shared object file: No such file or directory`

- xz (v5.8.3)

```bash
cd ~/share
tar xzvf xz-5.8.3.tar.gz
cd xz-5.8.3
./configure --prefix=${HOME}/.local
make
make install
```

- zstd (v1.5.7)

```bash
cd ~/share
tar xzvf zstd-1.5.7.tar.gz
cd zstd-1.5.7
make clean
make -j4
make install PREFIX=/share/home/zhuqingshao/.local
```

- Python rebuilt (with libbz2 from bzip2 and liblzma from xz)

```bash
cd ~/share/Python-3.9.19

./configure \
    --prefix=${HOME}/.local \
    BZIP2_CFLAGS="-I${HOME}/.local/include" \
    BZIP2_LIBS="-L${HOME}/.local/lib -lbz2" \
    LZMA_CFLAGS="-I${HOME}/.local/include" \
    LZMA_LIBS="-L${HOME}/.local/lib -llzma" \
    --enable-shared
make
make install

- Perl local env (v5.34.3)

```bash
wget https://www.cpan.org/src/5.0/perl-5.34.3.tar.gz
# rsync -avP perl-5.34.3.tar.gz zhuqingshao@xxx:share/

cd ~/share
tar xzvf perl-5.34.3.tar.gz
cd perl-5.34.3
./Configure -des \
    -Dprefix=${HOME}/.local/perl-5.34.3 \
    -Duseshrplib \
    -Dlibpth=${HOME}/.local/lib
make
make test
make install

echo "# local Perl 5.34" >> ~/.bashrc
echo 'export PERL_HOME="${HOME}/.local/perl-5.34.3"' >> ~/.bashrc
echo 'export PATH="${PERL_HOME}/bin:$PATH"' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH="${PERL_HOME}/lib:${LD_LIBRARY_PATH}"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

cd ~/share
# cpanm
wget https://mirror.nju.edu.cn/CPAN/authors/id/M/MI/MIYAGAWA/App-cpanminus-1.7049.tar.gz
tar xzvf App-cpanminus-1.7049.tar.gz
cd App-cpanminus-1.7049
perl Makefile.PL
make
make install

echo "# cpanm" >> ~/.bashrc
echo 'export PERL_CPANM_OPT="--notest --mirror-only --mirror https://mirror.nju.edu.cn/CPAN/"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

cpanm JSON
```

- RMblast/Blast+ (v2.17.1)

```bash
cd ~/share
module load gcc/gcc-11.5.0
tar xzvf ncbi-blast-2.17.0+-src.tar.gz
cd ncbi-blast-2.17.0+-src
gunzip ../isb-2.17.1+-rmblast.patch.gz
patch -p1 < ../isb-2.17.1+-rmblast.patch
cd c++
export CC=gcc
export CXX=g++

./configure --prefix=${HOME}/.local --without-debug --with-mt --with-projects=scripts/projects/rmblastn/project.lst
make
make install

rmblastn -version
#rmblastn: 2.17.1+
# Package: blast 2.17.0, build Aug 27 2026 17:57:53

# cp dynamic library to the local env
# ldd $(which rmblastn)
# libstdc++.so.6, libgomp.so.1, libgcc_s.so.1
cp -v /share/apps/gcc/gcc11.5.0/lib64/libstdc++.so* ~/.local/lib/
cp -v /share/apps/gcc/gcc11.5.0/lib64/libgomp.so* ~/.local/lib/
cp -v /share/apps/gcc/gcc11.5.0/lib64/libgcc_s.so* ~/.local/lib/

cd ~/.local/lib
rm -f libstdc++.so.6 libgomp.so.1 libgcc_s.so.1
ln -sf libstdc++.so.6.0.29 libstdc++.so.6
ln -sf libgomp.so.1.0.0 libgomp.so.1

# ldd $(which rmblastn)
```

- TRF, tandem repeats finder (v4.09.1)

```bash
cd ~/share
tar xzvf v4.09.1.tar.gz
cd TRF-4.09.1
./configure --prefix=${HOME}/.local
make
make install
trf
```

- HMMER (v3.4)

```bash
cd ~/share
tar xzvf hmmer.tar.gz
cd hmmer-3.4
./configure --prefix=${HOME}/.local
make
make install
hmmsearch -h
```

- cd-hit (v4.8.1)

```bash
cd ~/share
tar xzvf cd-hit-v4.8.1-2019-0228.tar.gz
cd cd-hit-v4.8.1-2019-0228
make
make install PREFIX=${HOME}/.local/bin
cd-hit -h

# the same lib as the rmblastn
# ldd $(which cd-hit)
```


- GenomeTools (v1.6.6)

```bash
cd ~/share
tar xzvf v1.6.6.tar.gz
cd genometools-1.6.6
make prefix=${HOME}/.local
make install prefix=${HOME}/.local
gt --version
#gt (GenomeTools) 1.6.6

# ldd $(which gt)
```

- samtools/bcftools/htslib (v1.24)

```bash
cd ~/share
tar -jxvf htslib-1.24.tar.bz2
cd htslib-1.24
./configure --prefix=${HOME}/.local
make
make install
htslib version

cd ~/share
tar -jxvf samtools-1.24.tar.bz2
cd samtools-1.24
./configure --prefix=${HOME}/.local
make
make install
samtools version

cd ~/share
tar jxvf bcftools-1.24.tar.bz2
cd bcftools-1.24
./configure --prefix=${HOME}/.local
make
make install
bcftools version
```

- bedtools (v2.31.1)

```bash
cd ~/share
tar xzvf bedtools-2.31.1.tar.gz
cd bedtools2

make clean
make
make install prefix=${HOME}/.local

bedtools --version
#bedtools v2.31.1
```

- minimap2 (v2.31.1)

```bash
cd ~/share
tar jxvf minimap2-2.31.tar.bz2
cd minimap2-2.31
make
# cp to local bin
cp minimap2 ${HOME}/.local/bin/

minimap2 --version
#2.31-r1302
```

- LTR Finder (v1.07)

```bash
cd ~/share/LTR_Finder/source
make

echo "# LTR Finder" >> ~/.bashrc
echo 'export PATH="$PATH:/share/home/zhuqingshao/share/LTR_Finder/source"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

ltr_finder -h
```

- LTR Finder parallel (v1.4)

```bash
cd ~/share
tar xzvf v1.4.tar.gz
cd LTR_FINDER_parallel-1.4
# prebuilt, ln to local bin
ln -s ~/share/LTR_FINDER_parallel-1.4/LTR_FINDER_parallel ${HOME}/.local/bin/LTR_FINDER_parallel

LTR_FINDER_parallel -h
```

- LTR Retriever (v3.0.5)

```bash
cd ~/share
tar xzvf v3.0.5.tar.gz
ln -s ~/share/LTR_retriever-3.0.5/LTR_retriever ${HOME}/.local/bin/LTR_retriever

LTR_retriever -h
```

- IRF, Inverted Repeats Finder (v3.09)

```bash
cd ~/share
tar xzvf IRFv3.09.tar.gz
cd IRF-IRFv3.09/src
make
cp ../bin/irf.exe ${HOME}/.local/bin/

irf.exe
```

- TIR learner (v4.07)

```bash
cd ~/share
tar xzvf v4.07.tar.gz
cd TIR-Learner-4.07/TIR-Learner4
python3 TIR-Learner.py -h
```

- seqtk (v1.5)

```bash
cd ~/share
tar xzvf v1.5.tar.gz
cd seqtk-1.5
make
make BINDIR=${HOME}/.local/bin install

seqtk
#Version: 1.5-r133
```

- TE sorter (v1.5.1)

```bash
cd ~/share
tar xzvf v1.5.1.tar.gz
cd TEsorter-1.5.1
python3 setup.py install

TEsorter -v
#TEsorter 1.5.1
```

- HelitronScanner (v1.1)

```bash
cd ~/share
unzip HelitronScanner_V1.0.zip
cd HelitronScanner
# prebuild java pack
java -jar ./HelitronScanner.jar
```

- mafft (v7.525)

```bash
cd ~/share
tar xzvf mafft-7.525-with-extensions-src.tgz
cd mafft-7.525-with-extensions/core
# vim Makefile
# change: PREFIX=/share/home/zhuqingshao/.local
make
make install

cd ~/share/mafft-7.525-with-extensions/extensions
# vim Makefile
# change: PREFIX=/share/home/zhuqingshao/.local
make
make install

mafft --version
#v7.525 (2024/Mar/13)
```

- FamDB (v3.0.0)

```bash
cd ~/share
tar xzvf 3.0.0.tar.gz
cd FamDB-3.0.0
make
python3 famdb.py --help

# download the database on a web-connected machine
python3 famdb.py -i Libraries/famdb/ check Viridiplantae
python3 famdb.py -i Libraries/famdb/ check --component cc Viridiplantae
python3 famdb.py -i Libraries/famdb/ check --component uc Viridiplantae
python3 utils/download_dfam.py
# type 1,2,4 to download all consensus sequences

# rsync -avP Libraries/ zhuqingshao@xxx:share/FamDB-3.0.0/Libraries/
```

- RepeatMasker (v4.2.4)

```bash
cd ~/share
tar xzvf RepeatMasker-4.2.4.tar.gz
cd RepeatMasker
./configure

echo "# RepeatMasker" >> ~/.bashrc
echo 'export PATH="$PATH:/share/home/zhuqingshao/share/RepeatMasker"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

RepeatMasker -h
```

