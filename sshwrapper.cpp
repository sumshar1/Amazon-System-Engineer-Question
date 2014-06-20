#include "sshwrapper.h"
#include<iostream>
#include<string.h>
#include<sys/syscall.h>
#include<unistd.h>
using namespace std;
//constructor initialization list
sshwrapper::sshwrapper( const std::string Rhost, const std::string Rcmd,/* const std::string Inputfile*/, const std::string Outputfile) :
               Remote_Host(Rhost), Remote_Command(Rcmd)/*, Input_File(Inputfile)*/, Output_File(Outputfile) { }
			   

void sshwrapper::Execute_Command()
{
			std::string sshpath="/usr/bin/ssh";
			char *User=argv[1];
			std::string userID(User);
			userID=USERID + "@";
			std::string Firing_Command=sshpath + " " + userID + Remote_Host + " ./" +Remote_command + /*" <" + Input_file + " >" + */ Output_File;
			
			if(system(Firing_Command.c_str()) < 0)
			    {
				 throw runtime_error("SSH Command Execution Failed!!");
				}
			counter--;
}
