# The HPCC environment

## EDTA

- local env

```bash
echo "# local env" >> ~/.bashrc
echo 'export PATH="/share/home/zhuqingshao/.local/bin:$PATH"' >> ~/.bashrc
echo 'export C_INCLUDE_PATH="/share/home/zhuqingshao/.local/include:$C_INCLUDE_PATH"' >> ~/.bashrc
echo 'export CPLUS_INCLUDE_PATH="/share/home/zhuqingshao/.local/include:$CPLUS_INCLUDE_PATH"' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH="/share/home/zhuqingshao/.local/lib:/share/home/zhuqingshao/.local/lib64:$LD_LIBRARY_PATH"' >> ~/.bashrc
echo 'export MANPATH="/share/home/zhuqingshao/.local/man:/share/home/zhuqingshao/.local/man/man1:$MANPATH"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc
```

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

- zstd (v1.5.7)

```bash
cd ~/share
tar xzvf zstd-1.5.7.tar.gz
cd zstd-1.5.7
make clean
make -j4
make install PREFIX=/share/home/zhuqingshao/.local
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


- minimap2 (v2.31.1)

```bash
cd ~/share
tar jxvf minimap2-2.31.tar.bz2
cd minimap2-2.31
make
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

