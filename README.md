Amazon-System-Engineer-Question
===============================

Determines the top 10 most common source IP addresses, and their hit rates, for a fleet of 1000 web servers within the last hour. The following assumptions may be used... web servers are locally writing access logs in the Apache Combined Log Format (http://httpd.apache.org/docs/current/logs.html#combined). web servers are accessible by ssh.




Problem Summary:

SE1 QE1:::
Determines the top 10 most common source IP addresses, and their hit rates, for a fleet of 1000 web servers within the last hour. 

The following assumptions may be used...
web servers are locally writing access logs in the Apache Combined Log Format (http://httpd.apache.org/docs/current/logs.html#combined).
web servers are accessible by ssh.

Various other assumptions, taken in consideration are:

**Code has been written on notepad++, so alignment may go wrong depending upon your choice of editor to open the files.

1) Pattern matching is done on the following fields of the date command as mentioned below;

   %d -> Date
   %b -> Month
   %Y -> Year
   %H -> Hours
   %M -> Minutes
   %S -> Seconds 
   
   which means distance wrt to time(i.e. at most 1 hour behind current time)  is calculated based on the above mentioned parameters of the date command.
   
2) If some of the webservers are down, then their is no outcome for the query fired on those servers, only in the case, when there is no shared file system (or log file in our case)
   i.e. the log file on which we work is not present locally on the server from where we fire the program.
3) The user who executes the program should have its public key shared with all the other 1000 webservers, so that the user can ssh without entering password.
4) The arguments are passed to program as arguments in the order "1000 server name file" and "log file name on remote servers" 
5) The server from where this program is fired is either one of the 1000 webservers or a separate one.
6) Program is allowed to create files on the server where the program executes.
7) The files created on the run, are cleaned at the end of the execution of the program.



The program is written in c++. And, is written out in 2 ways, one being the sequential way, and the other being concurrent.

A) In order to run the code in sequential mode(i.e. using signal thread) use the following command to compile the program and run the program;
   1) First compile the code using the command:
       on most of the linux machines this works fine, if doesn't then execute command 1.b.
      1.a #     g++ -std=c++0x sshwrapper.h sshwrapper.cpp maxhitRate.cpp -o OutputFile
      1.b #     g++ -std=c++11 sshwrapper.h sshwrapper.cpp maxhitRate.cpp -o OutputFile

   2)  To execute fire the object file in the manner defined below;
   
       #   ./OutputFile  inputServerNameFile   LogFilePathOnRemoteServers 
         
		 here, inputServerNameFile and  LogFilePathOnRemoteServers should be replaced with actual arguments.
		 

B) In order to run the code in multi-thread mode, please fire the following set of commands with actual arguments;
	1) First compile the code using the command:
       1.a #     g++ -std=c++0x -pthread sshwrapper.h sshwrapper.cpp maxhitRateThread.cpp -o OutputFile	
	          this works on most of the machines, if doesn't, please use the command mentioned below;
	   1.b #     g++ -std=c++11 -pthread sshwrapper.h sshwrapper.cpp maxhitRateThread.cpp -o OutputFile		  
	   
	2)  To execute fire the object file in the manner defined below;
   
       #   ./OutputFile  inputServerNameFile   LogFilePathOnRemoteServers 
         
		 here, inputServerNameFile and  LogFilePathOnRemoteServers should be replaced with actual arguments. 
