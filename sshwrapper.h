//ssh wrapper class

#ifndef SSHWRAPPER_H
#define SSHWRAPPER_H
#include<string.h>
using namespace std;
class sshwrapper
{
private:
	std::string Remote_Host;     //Place holder for the remote host name(IP)
	std::string Remote_Command;  //Place holder for the remote command that needs to fired
	//std::string Input_File;      //Place holder for the name of the file that tells the location of the log file on the remote host
	std::string Output_File;     //Place holder for the output that is generated locally on the server after running the remote command on the remote host
    
public:
    static int counter(0);
	sshwrapper();
	void Execute_Command();
};
#endif
