
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

	
 3. USING THIS LIBRARY APIs
	
	The first thing that should be done is initailize 'ss_diameter_conffile_name' global variable. This variable 
    should be set to the file name(full path eg "./diam/diam.conf") of the diameter configuration file. If this 
    variable is not set the configuration file will be searched in the directory where the excutable resides and the
    default file name is 'freediameter.conf'. Check the 'freediameter.conf.sample' file found in 'doc' directory 
    for details about how to configuration.

	The next step is to initiate the diameter module using 'ss_init()' API. This will load the diameter 
    configuration, load the dictionary that contains the AVP and command definition. In additions it starts the module
    that will route messages, listen on the configured ports, connects to configured peers, takes care of CEA, CER, 
    DWR and DWA messages.

	The above two steps should always come first before using the following APIs.

	After the above steps the next advisable step is to registere the callback functions that will be called when a 
	S6a message is received. If an S6a message is received before the callbacks are registered it would be discarded. 
    The APIs for registering the callbacks are:
		 'ss_reg_cb_ulr()'  for Update-Location-Request
		 'ss_reg_cb_clr()'	for Cancel-Location-Request
		 'ss_reg_cb_air()' 	for Authentication-Information-Request
		 'ss_reg_cb_idr()'	for Insert-Subscriber-Data-Request
		 'ss_reg_cb_dsr()'	for Delete-Subscriber-Data-Request
		 'ss_reg_cb_pur()'  for Purge-UE-Request 
		 'ss_reg_cb_rsr()'  for Reset-Request
	     'ss_reg_cb_nor()'  for Notify-Request
	Check the documentation for this APIs for details about how the callback works. 

	The other APIs in the documentations can be used according to the need to use them. The other  APIs can be 
    generally described as follows:  

	   'ss_create_msg_<cmd>': To create a specific request message. This will create a new message of the 'cmd' type
        	and it creates a new session id and set Session-Id AVP, sets the Vendor-Sepecific-Application-Id AVP and
        	its child AVPs and sets Auth-Session-State AVP. And it also sets Origin-Host AVP and Origin-Realm AVP 
        	with the values from the configuration file. The Auth-Session-State AVP is set to a value of 'NO-STATE-
		 	MAINTAINED'. And in Vendor-Sepecific-Application-Id AVP, Vendor-Id AVP is set to '10415'(3gpp's vendor 
		    id) and the Auth-Application-Id AVP IS set to '16777251'(S6a interface's application identifiere).
 			

	   'ss_peer_state' : Checks the connection state with a remote peer. To successful send message to a remote peer
	   		the state of the connection should be open state.

	   'ss_set_<AVPname>' : To set the value of an AVP and add it to it's parent which could be a message or an AVP 
	 		of typed grouped. The AVP should be of not type grouped since AVPs of typed group do not have a value 
 			rather they have other AVPs as a child in their data field.	   		

	   'ss_get_<AVPname>' : To fetch the value of an AVP which is found in a message. The AVP should be a direct child
      		of the message. If the AVP is a child AVP of other AVP which is a direct child of the message the parent
           	AVP should be fetched first using 'ss_get_gavp_<AVPname>'('AVPname' is the name of the parent AVP) and
 			then use 'ss_get_<AVPname>_gavp'('AVPname' is the name of the child AVP) to fetch the value. The AVP 
	 		should be of not type grouped since AVPs of typed group do not have a value rather they have other AVPs 
	     	as a child in their data field.
	
	   'ss_get_<AVPname>_gavp' : To fetch the value of an AVP which is found in another AVP of typed grouped. The AVP 
		  	it's value is fetched should be a direct child of the AVP of typed grouped. The AVP should be of not type 
           	grouped since AVPs of typed group do not have a value rather they have other AVPs as a child in their 
		    data field.

	   'ss_get_<AVPname>_array': To fetch an multiple values of an AVP found in a message. This API is used if the AVP
        	is a direct child of the message and if the AVP is one of the AVPs that can appear in the message more 
	 		than once. The AVP should be of not type grouped since AVPs of typed group do not have a value 
 			rather they have other AVPs as a child in their data field.

	   'ss_get_<AVPname>_gavp_array' : To fetch an multiple values of an AVP in an AVP of typed grouped. The AVP 
		  	it's value is fetched should be a direct child of the AVP of typed grouped and if the AVP is one of the 
     		AVPs that can appear in the AVP of type grouped more than once. The AVP should be of not type grouped 
	 		since AVPs of typed group do not have a value rather they have other AVPs as a child in their data field.

	   'ss_create_<AVPname>' : To create an empty AVP structure of a specific AVP of typed grouped.  For AVPs which 
 			are not of typed grouped, 'ss_set_<AVPname>' does the trick for both creating the AVP setting it's value 
	 		and adding it to it's parent.

	   'ss_add_<AVPname>' : To add an AVP of typed grouped into it's parent, which could be a message or an AVP of 
 	 		typed grouped. For AVPs which are not of typed grouped, 'ss_set_<AVPname>' does the trick for both 
	 		creating the AVP setting it's value and adding it to it's parent.

	   'ss_get_gavp_<AVPname>' : To fetch an AVP of typed grouped from it's parent. This API is mainly used	to fetch 
		 	parent AVPs of typed grouped before fetching their children values.

	   'ss_msg_create_answer' : To create an answer message from a received request message. This will extract and add
	 		all the necessary values like the end-to-end identifier from the request message and  set it in the answer
		    message structure. It also sets the Vendor-Sepecific-Application-Id AVP and its child AVPs and sets Auth-
	 		Session-State AVP. Here Auth-Session-State AVP is set to a value of 'NO-STATE-MAINTAINED'. And in Vendor-
	 		Sepecific-Application-Id AVP, Vendor-Id AVP is set to '10415'(3gpp's vendor id) and the 
		 	Auth-Application-Id AVP IS set to '16777251'(S6a interface's application identifiere).

	   'fd_msg_send' : To send message to other peers. It also registers, if provided, a callback function that will 
	 		be called when the corresponding answer is received.
	
	   'fd_msg_send_timeout' : It similar with 'fd_msg_send', the only difference is that if the corresponding answer
	 		is not recieved with in a specified time duration it will be discarded.

	   'fd_core_shutdown' : To shut down the diameter module. This will teerdown all existing connections and free
		 	all resources consumed by the diameter module.

	   'fd_core_wait_shutdown_complete' : Blocks untill the diameter module is shut down.

	    Note:'cmd' is abbreviated name of request command message(eg. rsr for Reset-Request).
		     'AVPname' is name of the AVP all in small letters and the hyphens(-) substituded by underscore
			 eg. for AVP Active-APN, AVPname would be 'active_apn'.

	
 4. TESTING

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




