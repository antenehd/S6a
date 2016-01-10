
 S6a INTERFACE IMPLEMENTATION LIBRARY


 1. INTRODUCTION
	
	This implementation of the S6a interface is meant to be used as a shared library. It contains a lot of 
	APIs that are useful to implement the s6a interface. It is bases on the freediameter(www.freediameter.net)   
    software libraries  'linfdproto' and 'libfdcore' which contains the implementation for the diameter basic 
    protocol and other basic functionalities need for this implementation to work. And it also requires the 
    extensions 'dict_dcca', 'dict_dcca_3gpp' and 'dict_nasreq' found in freediameter to be loaded for this   
    implementation to work.
	
	The details of the APIs of this library can be found in the documentaion. The documentaion is generated using
   	doxygen, to generate the documentation on your terminal navigate to the main directory and run this: 
	
	   # doxygen doc_gen 

	This will create an html documentation in 'doc' directory.
		
 2. ISTALLATION
	

	2.1. INSTALL FREEDIAMETER
	
		 Since this library totally relies on freediameter libraries, freediameter software must be installed.
		 To install freediameter follow the install instruction stated in the files found in the 
		 freediameter directory. The freediameter software in this directory should be used since it contains 
       	 some modified codes.
	
	2.2. BUILD THE S6a INTERFACE IMPLEMENTATION LIBRARY

		 Assuming it has been downloaded to you PC already. To build the S6a library, on your terminal goto the 
	  	 directory where this implementation is downloaded to, and excute the 'Makefile', run the following on 
       	 terminal:
		 
		 # make
	 
      	 This will create two new directories 'OBJECTS' and 'bin'. And the library is placed in the new directory 
	     'bin' under the name 'libssixa.so'. Use 'make debug' to build a library  which gives some information    	
	     where the error occurs. 
	
 3. TESTING

	Testing for all functionalities provided by the library are not yet done. The testing approached used is end to 
	end functionality test(i.e. message transfer from local peer node to remote peer node). While doing the end to  
    end testing each function will also be tested since all the functions will be used when all the end to end 
    testing is completed. 
	The end to end testing that has be done so far is for Update-Location-Request message and 
    Update-Location-Answer messages.

	Running the test: 

	  	mysql client and server should be installed on system where this test will be done.

	    To run the test, first the procedures mentioned in section 2.1. and section 2.2. must be completed 
	 	successfuly. Then on your command terminal navigate to 'test' directory which is found in the main directory 
	 	and	excute 'Makefile' and then excute 'copy.sh' as follows:
		
		# cd test
		# make
		# sh copy.sh

	    Then configure the password and username of the mysql server on your system in 'mysql.conf' file found in  			this directory('test' directory). Read the instruction in the file configure accordingly.

	 	After this create the test HSS database by navigating to 'hss_db' directory which is found in the current
	  	directory('test' directory) and excuting 'my.sh' as follows:

		# sh my.sh

	  Test Update-Location-Request/Answer : 

	 	Navigate to the 'test' directory and then navigate to 'testnode1' directory and run the following 
	    command to simulate an HSS server which is waiting for S6a interface messages:

		# ./testapp hss

	 	Then open another terminal and navigate to 'testnode2' directory which is found in the same directory as
	    'testhss'. From there run the following to simulate an MME client sending Update-Location-Request and 
       	waiting for Upadate-Location-Answer:

		# ./testapp ulr peer1.localdomain

	 	Now you should see the test running on both terminals.

	  Test Cancel-Location-Request/Answer : 

	 	Navigate to the 'test' directory and then navigate to 'testnode1' directory and run the following 
	    command to simulate an MME server which is waiting for S6a interface messages:

		# ./testapp mme

	 	Then open another terminal and navigate to 'testnode2' directory which is found in the same directory as
	    'testhss'. From there run the following to simulate an HSS client sending Update-Location-Request and 
       	waiting for Upadate-Location-Answer:

		# ./testapp clr peer1.localdomain

	 	Now you should see the test running on both terminals.

	  Test Authentication-Information-Request/Answer : 

	 	Navigate to the 'test' directory and then navigate to 'testnode1' directory and run the following 
	    command to simulate an HSS server which is waiting for S6a interface messages:

		# ./testapp mme

	 	Then open another terminal and navigate to 'testnode2' directory which is found in the same directory as
	    'testhss'. From there run the following to simulate an MME client sending Update-Location-Request and 
       	waiting for Upadate-Location-Answer:

		# ./testapp air peer1.localdomain

	 	Now you should see the test running on both terminals. 

	    Note : 'Warnings' messages in the terminal are just notifications that an optional AVP is not present which 
	    is could be normal. The 'ERROR' messages immediatly following or preceding the 'warning' messages is caused 
	    by the same situation as the 'warning'	message and it is generated by the freediameter application not the 
	    test application.




