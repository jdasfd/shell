# Biosoftware management

This section describes how to install and manage software using an unrooted linux account. Although the vast majority of common software could be installed directly under root account using `sudo apt install`, some rare software with complexed dependencies packages or env (_e.g._: Unrooted users install Python and related libraries) is neccesary to install under own account without affecting other env. Here are some codes for displaying softwares management.

## Some softwares needed to be installed via root account

- Perl

```bash
# RLK related
sudo cpan -i Getopt::Long Path::Tiny \
    Bio::Seq Bio::SeqIO AlignDB::IntSpan \
    Bio::SearchIO Bio::SearchIO::hmmer

# anchr dep
sudo cpan -i YAML::Syck Number::Format
```

- Ubuntu packages

```bash
# download
sudo apt install aria2
# RLK related
sudo apt install mafft
sudo apt install fasttree
sudo apt install cd-hit
sudo apt install iqtree
```

## Manage packages under unrooted linux account

### Anaconda

Anaconda could be installed directly under unrooted linux account

```bash
cd ~
wget https://repo.anaconda.com/archive/Anaconda3-2023.09-0-Linux-x86_64.sh
bash Anaconda3-2023.03-Linux-x86_64.sh
# installed via 
# restart

# auto activate canceled
conda config --set auto_activate_base false
```

### Basic installation (compile)

- tsv-utils

```bash
cd ~/share
git clone https://github.com/eBay/tsv-utils.git
cd tsv-utils
make

echo "# tsv utils" >> ~/.bashrc
echo 'export PATH=/home/jyq/share/tsv-utils/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

tsv-select -h
```

- faops

```bash
cd ~/share
git clone https://github.com/wang-q/faops
cd faops
make

echo "# faops" >> ~/.bashrc
echo 'export PATH=/home/jyq/share/faops:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

faops
```

- Rust and cargo

```bash
cd ~

# rust using curl
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# press enter or 1 when it asks the input

# anchr (wang-q)
cargo install --git https://github.com/wang-q/anchr --branch main
```

### Phylogeny and RLKs related

- trimAL (v1.4.rev22)

```bash
cd ~/share
git clone https://github.com/inab/trimal.git

cd trimal/source
make

#add path
echo "# trimal" >> ~/.bashrc
echo 'export PATH=$PATH:~/share/trimal/source' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc
```

- tmbed

```bash
cd ~/share
git clone https://github.com/BernhoferM/TMbed.git tmbed
cd tmbed/
pip install .
tmbed --help

# tmbed env settings
echo "# cuda env" >> ~/.bashrc
echo 'export CUBLAS_WORKSPACE_CONFIG=":4096:8"' >> ~/.bashrc
echo 'export PYTORCH_CUDA_ALLOC_CONF=max_split_size_mb:32' >> ~/.bashrc
source ~/.bashrc

tmbed --help
```

- HMMER

```bash
cd ~/share
wget http://eddylab.org/software/hmmer/hmmer-3.3.2.tar.gz
tar -xzvf hmmer-3.3.2.tar.gz
cd hmmer-3.3.2/
./configure --prefix ~/.hmmer
make
make check
make install

# hmmer setting
echo "# HMMER_332" >> ~/.bashrc
echo 'export PATH=~/.hmmer/bin:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

hmmscan -h
```

### Single-cell related

- Cellranger

Download cellranger via `wget` or `curl` to my software dir `~/share`. The download link could be found on the website [10xgenomics](https://support.10xgenomics.com/single-cell-gene-expression/software/overview/welcome).

```bash
cd ~/share/
# cellranger
wget -O cellranger-7.1.0.tar.gz "https://cf.10xgenomics.com/releases/cell-exp/cellranger-7.1.0.tar.gz?Expires=1680805080&Policy=eyJTdGF0ZW1lbnQiOlt7IlJlc291cmNlIjoiaHR0cHM6Ly9jZi4xMHhnZW5vbWljcy5jb20vcmVsZWFzZXMvY2VsbC1leHAvY2VsbHJhbmdlci03LjEuMC50YXIuZ3oiLCJDb25kaXRpb24iOnsiRGF0ZUxlc3NUaGFuIjp7IkFXUzpFcG9jaFRpbWUiOjE2ODA4MDUwODB9fX1dfQ__&Signature=i6cFr79khQt8vYd-lOuN6YiHDMt5~qvtN0DGaSlzZ7lf676CYdL-~msHdxFp1sNQESSGY1GvRF5hBNUzt7OcmNDqz4mDTiPDRrHj3-nkcDmS1YnWqaxXTS7M95pjdRjqt8udJjALr3YKHeZN8uJU6TNf1IIsm7Jgqr5eSM7dJGlFnwPLAz9rzFADKOaeDTG5a-CuEq8-7GL4cbjyNzshvFOThmAUnYFbKQfjennorucsdYD1B2AlJEiEtEykaKUeQ4DhVZZose51R6qMkFj4iCFgMjdB4EgcRyvNkmIQ6j4kZZsEJl6CF8hROOYckalVk1EKlod9LQTHf3fCD3Zlkg__&Key-Pair-Id=APKAI7S6A5RYOXBWRPDA"
# cellranger-atac
wget -O cellranger-atac-2.1.0.tar.gz "https://cf.10xgenomics.com/releases/cell-atac/cellranger-atac-2.1.0.tar.gz?Expires=1680813186&Policy=eyJTdGF0ZW1lbnQiOlt7IlJlc291cmNlIjoiaHR0cHM6Ly9jZi4xMHhnZW5vbWljcy5jb20vcmVsZWFzZXMvY2VsbC1hdGFjL2NlbGxyYW5nZXItYXRhYy0yLjEuMC50YXIuZ3oiLCJDb25kaXRpb24iOnsiRGF0ZUxlc3NUaGFuIjp7IkFXUzpFcG9jaFRpbWUiOjE2ODA4MTMxODZ9fX1dfQ__&Signature=dHBrc-5MMWr-6hTLwDIgorZIupXByEcbI6jjA8hQTsd1aWOfgHGUKXGKsukjmw2zp8ehD2yxduUmpuMyIymctkIEuavk6jYSHS6mekyi8S0hKfE9qk8Zya-VP8gIyqVy5LaFgtFdt164-yVBKjA9kLVdBJ5qghs2WNOhJqQ2es~iH8rdb5L2OSjdv0hHTIuypMQobOKSt27kKfOPtbV-f~~g1d1MxrgBJJXu7JDS-QwLwqbU3eDUPz2IE5XqmsFYEkxAlOlYszdv-kIGxc37AvwBavMJfMzJqIlcVvi53N4szZGqqQ4V4f-p8q0oh2RYJA-fe3sOFK6fBYI0gFeeeQ__&Key-Pair-Id=APKAI7S6A5RYOXBWRPDA"

# tar them
tar -xzvf cellranger-7.1.0.tar.gz
tar -xzvf cellranger-atac-2.1.0.tar.gz

# add path to .bashrc
echo "# Single cell" >> ~/.bashrc
echo 'export PATH=~/share/cellranger-7.1.0:$PATH' >> ~/.bashrc
echo 'export PATH=~/share/cellranger-atac-2.1.0:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

# test
cellranger -h
cellranger-atac -h
```

- STAR

```bash
cd ~/share

git clone https://github.com/alexdobin/STAR.git
cd STAR/source
make STAR

echo "# STAR" >> ~/.bashrc
echo 'export PATH=~/share/STAR/source:$PATH' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

STAR -h
```

### Protein structure related

- AlphaFold2 (v2.3.1)

```bash
cd ~/share

conda create -n alphafold python==3.8
conda update -n base conda
conda activate alphafold

# install deps
conda install -y -c conda-forge openmm==7.5.1 cudatoolkit==11.2.2 pdbfixer
conda install -y -c bioconda hmmer hhsuite==3.3.0 kalign2

# pip install via python3.8
pip install absl-py==1.0.0 biopython==1.79 chex==0.0.7 dm-haiku==0.0.9 dm-tree==0.1.6 immutabledict==2.0.0 jax==0.3.25 ml-collections==0.1.0 numpy==1.21.6 pandas==1.3.4 protobuf==3.20.1 scipy==1.7.0 tensorflow-cpu==2.9.0
# pip install --upgrade --no-cache-dir jax==0.3.25 jaxlib==0.3.25+cuda11.cudnn805 -f https://storage.googleapis.com/jax-releases/jax_cuda_releases.html
pip install -U --no-cache-dir "jax[cuda12_pip]" -f https://storage.googleapis.com/jax-releases/jax_cuda_releases.html

wget https://github.com/deepmind/alphafold/archive/refs/tags/v2.3.1.tar.gz && tar -xzf v2.3.1.tar.gz && export alphafold_path="$(pwd)/alphafold-2.3.1"
wget -q -P $alphafold_path/alphafold/common/ https://git.scicore.unibas.ch/schwede/openstructure/-/raw/7102c63615b64735c4941278d92b554ec94415f8/modules/mol/alg/src/stereo_chemical_props.txt

# $alphafold_path variable is set to the alphafold git repo directory (absolute path)
cd ~/anaconda3/envs/alphafold/lib/python3.8/site-packages/ && patch -p0 < $alphafold_path/docker/openmm.patch
```

- mmseqs2 (version 7e2840992948ee89dcc336522dc98a74fe0adf00)

```bash
cd ~/share
wget https://github.com/soedinglab/MMseqs2/releases/download/14-7e284/mmseqs-linux-avx2.tar.gz
tar -xzvf mmseqs-linux-avx2.tar.gz

echo "# mmseqs2" >> ~/.bashrc
echo 'export PATH="$PATH:~/share/mmseqs/bin"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc
```

- ColabFold

Using [localcolabfold](https://github.com/YoshitakaMo/localcolabfold) for rapid deployment.

```bash
# touch install_colabbatch_linux.sh
# chmod +x install_colabbatch_linux.sh
bash install_colabbatch_linux.sh

echo "# colabfold" >> ~/.bashrc
echo 'export PATH="/home/jyq/share/localcolabfold/colabfold-conda/bin:$PATH"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

conda activate /home/jyq/share/localcolabfold/colabfold-conda
# this command could be used to solve the error of ptxas (version issue)
conda install cuda -c nvidia
# no gpu detected (cudnn issue)
conda install cudnn
colabfold_batch --help

# if something wrong
cd ~/share/localcolabfold
bash update_linux.sh

# for convenience
# conda rename -p /home/jyq/share/localcolabfold/colabfold-conda colabfold
# --dry-run: test whether running
# unroot users would not be able to do this

# try to clone env from the path
conda create -n colab --clone /home/jyq/share/localcolabfold/colabfold-conda

# no gpu detected
# if cuda12 detected (under activate env)
# pip install --upgrade "jax[cuda12_pip]==0.4.23" -f https://storage.googleapis.com/jax-releases/jax_cuda_releases.html

# use the following code in python to check
# >>> print(jax.local_devices()[0].platform)
```

- ColabDB

Run the following command for building colab local database (bash not very good)

```bash
mkdir -p ~/share/localcolabfold/colabDB
cd ~/share/localcolabfold/colabDB

cat << EOF > db.tmp.lst
UNIREF30_READY
COLABDB_READY
PDB_READY
PDB100_READY
PDB_MMCIF_READY
EOF

# uniref30_2302
aria2c --max-connection-per-server=8 https://wwwuser.gwdg.de/~compbiol/colabfold/uniref30_2302.tar.gz
tar xzvf uniref30_2302.tar.gz
# mmseqs tsv2exprofiledb uniref30_2302 uniref30_2302_db
# no ${OUT}_h.dbtype
mmseqs tsv2db uniref30_2302_h.tsv uniref30_2302_db_h --output-dbtype 12
# no ${OUT}.dbtype
mmseqs tsv2db uniref30_2302.tsv uniref30_2302_db_tmp --output-dbtype 0
mmseqs compress uniref30_2302_db_tmp uniref30_2302_db
mmseqs rmdb uniref30_2302_db_tmp
# no ${OUT}_seq.dbtype
mmseqs tsv2db uniref30_2302_seq.tsv uniref30_2302_db_seq_tmp --output-dbtype 0
mmseqs compress uniref30_2302_db_seq_tmp uniref30_2302_db_seq
mmseqs rmdb uniref30_2302_db_seq_tmp
# no ${OUT}_aln.dbtype
mmseqs tsv2db uniref30_2302_aln.tsv uniref30_2302_db_aln_tmp --output-dbtype 5
mmseqs compress uniref30_2302_db_aln_tmp uniref30_2302_db_aln
mmseqs rmdb uniref30_2302_db_aln_tmp
# no ${OUT}_seq_h.dbtype
mmseqs aliasdb uniref30_2302_db_h uniref30_2302_db_seq_h
# empty .sh
rm -f -- uniref30_2302_db.sh
touch UNIREF30_READY

# colabfold envdb
aria2c --max-connection-per-server=8 https://wwwuser.gwdg.de/~compbiol/colabfold/colabfold_envdb_202108.tar.gz
tar xzvf colabfold_envdb_202108.tar.gz
# mmseqs tsv2exprofiledb "colabfold_envdb_202108" "colabfold_envdb_202108_db"
# no ${OUT}_h.dbtype
mmseqs tsv2db colabfold_envdb_202108_h.tsv colabfold_envdb_202108_db_h --output-dbtype 12
# no ${OUT}.dbtype
mmseqs tsv2db colabfold_envdb_202108.tsv colabfold_envdb_202108_db_tmp --output-dbtype 0
mmseqs compress colabfold_envdb_202108_db_tmp colabfold_envdb_202108_db
mmseqs rmdb colabfold_envdb_202108_db_tmp
# no ${OUT}_seq.dbtype
mmseqs tsv2db colabfold_envdb_202108_seq.tsv colabfold_envdb_202108_db_seq_tmp --output-dbtype 0
mmseqs compress colabfold_envdb_202108_db_seq_tmp colabfold_envdb_202108_db_seq
mmseqs rmdb colabfold_envdb_202108_db_seq_tmp
# no ${OUT}_aln.dbtype
mmseqs tsv2db colabfold_envdb_202108_aln.tsv colabfold_envdb_202108_db_aln_tmp --output-dbtype 5
mmseqs compress colabfold_envdb_202108_db_aln_tmp colabfold_envdb_202108_db_aln
mmseqs rmdb colabfold_envdb_202108_db_aln_tmp
# no ${OUT}_seq_h.dbtype
mmseqs aliasdb colabfold_envdb_202108_db_h colabfold_envdb_202108_db_seq_h
# empty .sh
rm -f -- colabfold_envdb_202108_db.sh
touch COLABDB_READY

# pdb
aria2c --max-connection-per-server=8 https://wwwuser.gwdg.de/~compbiol/colabfold/pdb100_230517.fasta.gz
mmseqs createdb pdb100_230517.fasta.gz pdb100_230517
touch PDB_READY

# pdb100
aria2c --max-connection-per-server=8 https://wwwuser.gwdg.de/~compbiol/data/hhsuite/databases/hhsuite_dbs/pdb100_foldseek_230517.tar.gz
tar xzvf pdb100_foldseek_230517.tar.gz pdb100_a3m.ffdata pdb100_a3m.ffindex
touch PDB100_READY

mkdir -p pdb/divided
mkdir -p pdb/obsolete
rsync -rlpt -v -z --delete --port=33444 rsync.wwpdb.org::ftp/data/structures/divided/mmCIF/ pdb/divided
rsync -rlpt -v -z --delete --port=33444 rsync.wwpdb.org::ftp/data/structures/obsolete/mmCIF/ pdb/obsolete
touch PDB_MMCIF_READY

# show all ready files
ls *_READY
cat db.tmp.lst | tsv-join -f <(ls *_READY) -k 1 -e

# if showing nothing
rm db.tmp.lst
```

- GPU background moniter

```bash
# pip install gpustat
# without dynamic changing

# nvitop is a better one
pip install nvitop
nvitop
```

- US-align (version 20230609)

```bash
cd ~/share

git clone https://github.com/pylelab/USalign.git
cd USalign/
make

echo "# USalign" >> ~/.bashrc
echo 'export PATH="$PATH:~/share/USalign"' >> ~/.bashrc
echo >> ~/.bashrc
source ~/.bashrc

USalign -h
```

## Reference:

- [Unrooted users install Python and related libs](https://blog.csdn.net/JohinieLi/article/details/103710021)
- [Rust and cargo install](https://linux.cn/article-13938-1.html)
