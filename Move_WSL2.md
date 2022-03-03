##  How to move WSL2 safely to another drive

It is real pain when you have small SSD and Windows Subsystem for Linux (WSL) is growing exponentially in size. There no easy way to move the WSL installation to another drive. Here in this blog I will discuss how to tackle this problem with bite size steps.

1. Open a PowerShell ![powershell](https://avinal.space/images/powershell.png) or Command Prompt ![command-line](https://avinal.space/images/command-line.png) with *Admin* access. For this you can use ![WinKey](https://avinal.space/images/windows10.png) + X shortcut and select **Windows PowerShell(Admin)**.
2. Check if the WSL 2 installation you are planning to move is is currently running/stopped.

```powershell
PS C:\Users\59717> wsl -l -v
PS C:\Users\59717>
  NAME            STATE           VERSION
* Ubuntu-20.04    Running         2
```

3. If its running then you must stop the particular WSL distribution. (*Ubuntu* used as example)

```powershell
PS C:\Users\59717> wsl -t Ubuntu-20.04
```

4. Export to some folder. (Here exporting *Ubuntu* as *ubuntu-ex.tar* to *E:wsl2*)

```powershell
PS C:\Users\59717> New-Item -Path "E:\wsl2" -ItemType Directory

    Directory: E:\

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----        31-12-2020     21:03                wsl2
PS C:\Users\59717> wsl --export Ubuntu-20.04 "E:\wsl2\ubuntu-ex.tar"
```

5. Unregister previous WSL installation

```powershell
PS C:\Users\59717> wsl --unregister Ubuntu-20.04
```

6. Create a new folder and import your WSL installation to that folder.

```powershell
PS C:\Users\59717> wsl --import Ubuntu-20.04 "E:\wsl2" "E:\wsl2\ubuntu-ex.tar"
```

7. Check after import is complete

```powershell
PS C:\Users\59717> wsl -l -v
PS C:\Users\59717>
  NAME            STATE           VERSION
* Ubuntu-20.04    Running         2
```

8. Mark one of your WSL distribution as *(default)*.

```powershell
PS C:\Users\59717> wsl -s Ubuntu-20.04
```

9. After exporting your default user will be set as *root* , to change it to your desired username or find your previous username, run following command

```
PS C:\Users\59717> cd E:\wsl2
PS E:\wsl2> ubuntu2004.exe config --default-user j
```

10. Finally run `wsl` and you have successfully moved your WSL 2 installation to another drive.