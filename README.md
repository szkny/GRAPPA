# GRAPPA
Vim-like paint application powered by GLUT (for Mac or Linux).         

## download
Execute "git clone" command.
```bash
$ git clone https://github.com/szkny/GRAPPA.git
```
Or extract the zip file.   
```bash:bash
$ cd [Path to "GRAPPA-master.zip"]
$ unzip GRAPPA-master.zip
```

## install (Mac)
Change directory to "GRAPPA" or "GRAPPA-master", then
```bash:bash
$ cd ./build
$ cmake ..
$ make
```

## install (Linux)
Change directory to "GRAPPA" or "GRAPPA-master", then
```bash:bash
$ make
```

## demo
Go to directory where "GRAPPA" executable exists ("build" directory).     
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
GRAPPA's command list can be confirmed by "help" command.
```vim:grappa consol
:help
```
The command list is described in "./src/Command.cpp".

## screenshots
![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/movie4.gif)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/movie2.gif)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/GRAPPA_screenshot2.png)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/GRAPPA_screenshot.png)

![GRAPPA images](https://github.com/szkny/GRAPPA/wiki/images/OctoCat.png)
