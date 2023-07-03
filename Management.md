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
sudo apt install aria2
```

## Manage packages under unrooted linux account

- tsv-utils

```bash
cd ~/share
git clone https://github.com/eBay/tsv-utils.git
cd tsv-utils
make

echo "# STAR" >> ~/.bashrc
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

- Rust and cargo

```bash
cd ~

# rust using curl
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# press enter or 1 when it asks the input

# anchr (wang-q)
cargo install --git https://github.com/wang-q/anchr --branch main
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
```

## Reference:

- [Unrooted users install Python and related libs](https://blog.csdn.net/JohinieLi/article/details/103710021)
- [Rust and cargo install](https://linux.cn/article-13938-1.html)
