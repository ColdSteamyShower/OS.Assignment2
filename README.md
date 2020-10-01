# OS_Assignement2

Michael Kulinich
kulinich@chapman.edu

Ayden Best
bbest@chapman.edu

CPSC 380-01
Assignment 2

[mk@amk OS.Assignment2]$ gcc sshell.c -o sshell
[mk@amk OS.Assignment2]$ ./sshell 
osh> cat bar.txt
executing argument: cat bar.txt
Hello World
Hello World!!


Child Complete
osh> ls
executing argument: ls
bar.txt  README.md  sshell  sshell.c


Child Complete
osh> ls -ltr
executing argument: ls -ltr
total 40
-rw-rw-r--. 1 mk mk   123 Sep 30 09:51 README.md
-rw-rw-r--. 1 mk mk    26 Sep 30 17:42 bar.txt
-rw-rw-r--. 1 mk mk  4383 Sep 30 17:45 sshell.c
-rwxrwxr-x. 1 mk mk 22592 Sep 30 17:46 sshell


Child Complete
osh> emacs bar.txt &
executing argument: emacs bar.txt &
osh> exit
executing argument: exit
[mk@amk OS.Assignment2]$ 

