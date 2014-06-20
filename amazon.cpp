/*
Program created by Sumit Sharma

Purpose of the program:::

Determines the top 10 most common source IP addresses, and their hit rates, for a fleet of 1000 web servers within the last hour. 

The following assumptions may be used...

**web servers are locally writing access logs in the Apache Combined Log Format (http://httpd.apache.org/docs/current/logs.html#combined).
**web servers are accessible by ssh.
*/



/*--->>>including the preprocessor 
*/
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/syscall.h> //defines system call
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector
#include <map>			//std::map
#include "sshwrapper.h"
#include<fstream>

using namespace std;

// 1 ) Declaring the map to keep the data on server from where this program is fired.
// 2 ) Format of fields is "IPADDRESS, HITRATE"
std::map< std::string , int > tracker;
std::map< std::string , int >::iterator iter;

// 1) For getting the top 10 fields of the pattern "IPADDRESS, HITRATE", we would be using a HEAP data Structure.
// 2) This CompareByValue is used to sort heap of constant size 10
struct CompareByValue 
{
    bool operator() (const data a, const data b) const 
	{
    return a.hitrate < b.hitrate;
    };
};



/*--->>>function declarations 
*/


/* 1) To check if the program has been supplied with all the required arguments. 
      Arguments to be specified are mentioned below in the correct order as follows;
	  a) User-name: As whom do you run this program from the console (this user should be a valid user, and it should right to ssh on all the 1000 servers
	  b) Configuration file name: This arguments contains the name of the file which lists all the 1000 webservers(specifically IP Addresses).
	  c) Log file name: This arguments mentions the log file under consideration on the remote webservers
*/

bool CheckArguments(int argc, char *argv[]);


/* 2) Now, we connect to 1000 servers and get relevant output from them. This function is passed the file which contains the name of 1000 webservers.
*/

bool  Connect&Getdata( char *ServerListFileName);




/*--->>>Function definitions
*/

bool CheckArguments(int argc, char *argv[])
{
  //Checking the argument count, should be 3
	
	if(argc!=3)
	    { 
			 std::cerr<<"usage ./solution User-Id ServerListFileName LogFileName";
			 return false;
	    } 
		
  //Validating the arguments passed
     
	/*User name */ 
	if( system( "awk 'BEGIN { status =0 ;} $1 ~/`argv[1]`/ {status=1;} END {if(status == 0) print "the User is Valid, can we can move on with execution!!"; }'")  < 0 )
		{
			throw runtime_error("User does not exist!!");
			return false;
		}
		
  
    /* ServerList file name */
	ifstream list(argv[2], std::ios::in);
	if( !list ) 
		{
			std::cerr<<"the serverlist file does not exist, please make sure filename is correct!!";
			return false;
		}
	
	//clears all test
	list.close();
	return true;
	 
}



bool  Connect&Getdata( char *ServerListFileName)
{
    //creating 1000 threads for getting information in pair (IPADDRESS, HITRATE)
    std::thread threads[1000];
    //command to executed on the remote system to filter based on the condition, that the line added is at max 1 hour old from current system time
	std::string command="awk -vDate=`date -d 'now -1 hours' + [%d/%b/%Y:%H:%M:%S` '{ if ($4 > Date) print $1}'" +" " + string(argv[3]) +" | sort | uniq -c | sort -n | tail";
	
	ifstream inputfile("ServerListFileName", std::ios::in);
	
	std::string ServerIP;    //string to hold the address, so the host knows, where to connect 
	int count(0);            //count to hold the number of remote of machines from where we have got the information 
	while(inputfile)
	{
		inputfile>>ServerIP;
		
		sshwarpper sshExecute(ServerIP, command, "Outputs/"ServerIP+".out" );
		sshwarper::counter++; count++;
		threads[count] = std::thread(&sshwrapper::Execute_Command() , &sshExecute);
	}
	
	int threadID; 
	while(sshwarper::counter!=0)
	{/*
		if(threads[threadID].joinable())
	    { 
			threads[threadID].join();
			count--;
	    }
		*/
	}
	
	//start reading the file one by one, and put the data to the heap...
	//first get the files in a new file
		system("ls Outputs/ > maxHits.out");
		
	//Now open all the files which are listed in the file maxHits.out, open them add contents to the data structure to return the top 10 ip's 
	//and their hit rates
	
	ifstream reader("maxHits.out");
	try 
	{
		if( !maxHits.out )
			throw -1;
	}
	catch (int exception)
	{
		std::cerr<<"Program has been unsuccessful to create the file maxHits.out, and hence exiting!!";
		return false;
	}
	
	std::string filenames;  
	while(reader)
	{
		reader >> filenames;
		std::string pathtofile="Outputs/" + filenames;
		ifstream reader1(pathtofile.c_str());
			if(!reader1)
			{
				std::cerr<<"error reading the file" << pathtofile<<std::endl;
			}
		int hitRate;
		std::string IPAddress;
	
		while(reader1)
		{
			filecounter++;
			reader1>>hitRate;
			reader1>>IPAddress;
	
	//add the entries to the hashmap
		tracker[IPAdress]+=hitRate;
	}
	//close the file which has been imported from the remote servers
		reader1.close();
	}
	
	//close the file 
	reader.close();
	
	//delete all the unnecessay files from the system
	
	system("rm -f -R Outputs/");
	system("rm -f maxHits.out");
	
	/*now we have the data in the format
	IPAddress -- >> hit rate
	Converting it to the required form (top 10)
	*/
	
	typedef struct returndata
	{
		int hitrate;
		std::string ipaddress;
	}data;
	
	
	std::vector <data> myVector;
	
	iter=tracker.begin();
	int ipcount(0);
	while( iter!=tracker.end() )
		{
		data Data;
			if(ipcount < 10)
			{
				Data.hitrate=iter->second;
				Data.ipaddress=iter->first;
				ipcount++;
				myVector.push_back(Data);
		
				if(ipcount==9)
				{
				std::sort(myVector.begin(), myVector.end(), CompareByValue());
				}	
			}
			else
			{
				data Data1=myVector.front();
					if(iter->second > Data1.hitrate)
					{
						myVector.pop_front();
						data Data;
						Data.hitrate=iter->second;
						Data.ipaddress=iter->first;
						myVector.push_front(Data);
						std::sort(myVector.begin(), myVector.end(), CompareByValue());
					}
			}
		iter++;	
		}
	
	//display the result on the screen as well as a file
	
	ofstream outputfile("maxHitIPs.out", std::ios::out);
	if(!outputfile)
		{ 
			std::cerr<<"error while creating the final output file"<<std::endl;
		}
	
	std::cout<<"IP ADDRESS            "<<"HIT RATE";
	outputfile<<"IP ADDRESS            "<<"HIT RATE";
	
	int size=myVector.size();
	
	for(int i=0; i < size ; i++)
	{
	std::cout << myVector[i].ipaddress  <<"            "<<myVector[i].hitrate<<std::endl;
	outputfile << myVector[i].ipaddress <<"            "<<myVector[i].hitrate<<std::endl;
	}
	
	return true;
}	
	
int main(int argc, char *argv[])
{
//Checking the usage of the program
if( CheckArguments(argc, argv[]) == false)
{
return 0;
}

//create a directory in the present working directory, to store the output files
if(system("mkdir -p Outputs") <0)
{
std::cerr<<"Exception, wasn't able to create a directory in the PWD, please check current directory permissions"<<std::endl;
exit (0);
}

//Now connect to all the 1000 webservers and get relevant data from there,  we will just fetch 10 rows of data with the ip address and hit rate
char *serverListFile=argv[2];
Connect&Getdata(serverListFile);

//remove the directory created on the system
if(system("rm -f -R Outputs") <0)
{
std::cerr<<"Exception, wasn't able to delete the Outputs Directory in the PWD, please delete it manually after this program completes execution hereafter!!"<<std::endl;
return 0;
}

return 1;
}


