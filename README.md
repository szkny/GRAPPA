# GRAPPA
Vim-like paint application for mac(OS X), Linux(CentOS) using GLUT.         

## download
Extract the zip file and change directory to "GRAPPA-master".     
```bash:bash
$ cd [Path to "GRAPPA-master.zip"]
$ unzip GRAPPA-master.zip
```
Or execute "git clone" command.
```bash
$ git clone https://github.com/szkny/GRAPPA.git
```

## installation (for mac)
Change directory to "GRAPPA-master" or "GRAPPA", then
```bash:bash
$ cd ./build
$ cmake .. && make
```

## installation (for Linux)
Change directory to "GRAPPA-master" or "GRAPPA", then
```bash:bash
$ make
```

## demo
Go to direcotry where "GRAPPA" executable exists ("build" directory).     
Then, execute GRAPPA with "GRAPPA.gra" as an argument.
```bash:bash
$ ./GRAPPA ../GRAPPA.gra
```
As another way, after starting GRAPPA, type ":" to start the console mode, and enter the following command,
```vim:grappa consol
:edit ../GRAPPA.gra
```
The command "edit" can simply written as "e".
```vim:grappa consol
:e ../GRAPPA.gra
```

## screenshots
![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/movie4.gif)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/movie2.gif)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/GRAPPA_screenshot2.png)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/GRAPPA_screenshot.png)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/OctoCat.png)
