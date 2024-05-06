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

### OrthoFinder

## References

- [apt,apt-get,aptitude](https://linuxgenie.net/difference-between-apt-apt-get-and-aptitude/#:~:text=In%20summary%2C%20apt%2C%20apt-get%2C%20and%20aptitude%20are%20all,it%20can%20also%20be%20more%20complex%20to%20use.)
