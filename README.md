# GRAPPA
Vim-like paint application for mac(OS X), Linux(CentOS) using GLUT.         
Extract the zip file and change directory to "GRAPPA-master", then make "GRAPPA".     

## installation (for mac)
    $ cd [Path to "GRAPPA-master"]/GRAPPA-master/build
    $ cmake .. && make
    $ ./GRAPPA

```bash:bash
$ cd [Path to "GRAPPA-master"]/GRAPPA-master/build
$ cmake .. && make
$ ./GRAPPA
```

## installation (for Linux)
```bash:bash
$ cd [Path to "GRAPPA-master"]/GRAPPA-master
$ make
$ ./build/GRAPPA
```

## demo
Go to direcotry where "GRAPPA" executable exists.     
Then, execute GRAPPA with "GRAPPA.gra" as an argument.
```bash:bash
$ ./GRAPPA ../GRAPPA.gra
```
As another way, after starting GRAPPA,
```vim:grappa consol
:edit ../GRAPPA.gra
```
The command "edit" can be omitted in "e".
```vim:grappa consol
:e ../GRAPPA.gra
```

## screenshots
![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/movie4.gif)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/movie2.gif)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/GRAPPA_screenshot2.png)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/GRAPPA_screenshot.png)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/OctoCat.png)
