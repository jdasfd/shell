# My settings

## How to modified R 4.3.0

After my test, I realized that my linux R could only accept http for softwares downloading, which means all https web would return a mistake.

Do the following to create a ~/.Rprofile to change the default setting of R. The following codes were written by `R`, which means in linux you should type `R` in the terminal.

```R
file.edit('~/.Rprofile')
# my R only allow http proxy
options("repos" = c(CRAN="http://mirrors.tuna.tsinghua.edu.cn/CRAN/"))
options(BioC_mirror="http://mirrors.ustc.edu.cn/bioc/")

#:wq to save and exit vim
```
