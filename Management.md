# Biosoftware management

This section describes how to install and manage software using an unrooted linux account. Although the vast majority of common software could be installed directly under root account using `sudo apt install`, some rare software with complexed dependencies packages or env (_e.g._: Unrooted users install Python and related libraries) is neccesary to install under own account without affecting other env. Here are some codes for displaying softwares management.

- Perl

```bash
# RLK related
sudo cpan -i Getopt::Long Path::Tiny \
    Bio::Seq Bio::SeqIO AlignDB::IntSpan \
    Bio::SearchIO Bio::SearchIO::hmmer

# anchr dep
sudo cpan -i YAML::Syck Number::Format
```

- Rust and cargo

```bash
# rust using curl
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# press enter or 1 when it asks the input

# anchr (wang-q)
cargo install --git https://github.com/wang-q/anchr --branch main
```

- Ubuntu packages

```bash
sudo apt install aria2
```

## Reference:

- [Unrooted users install Python and related libs](https://blog.csdn.net/JohinieLi/article/details/103710021)
- [Rust and cargo install](https://linux.cn/article-13938-1.html)
