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

- Rust and cargo

```bash
cd ~

# rust using curl
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# press enter or 1 when it asks the input

# anchr (wang-q)
cargo install --git https://github.com/wang-q/anchr --branch main
```

- Cell ranger

```bash


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

## Reference:

- [Unrooted users install Python and related libs](https://blog.csdn.net/JohinieLi/article/details/103710021)
- [Rust and cargo install](https://linux.cn/article-13938-1.html)
