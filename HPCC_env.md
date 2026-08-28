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

