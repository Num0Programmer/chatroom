# What to do
This assignment has two distinct parts. In the first part, you will write a simple TCP Daytime client, which allows you to connect to a Daytime server and receive timing information. In the second part you will write two parallel/multithreaded Daytime servers.

## Part 1: Daytime clients
Write a simple Daytime client that connects to the Daytime server, provided by the NIST (time.nist.gov:13), to receive time information. This client will comply to RFC 867, as described [here](https://datatracker.ietf.org/doc/html/rfc867). There is one important assumption, however, that I want you to honor and design your code accordingly: we want to assume that you have no prior knowledge about the length of the time message. The only fact you know about the time message is that the last character in it is the OTM (i.e. "on-time-marker"), represented by the star (*) character.

Otherwise, the protocol for the communication between your client and the server is simple, i.e. the client connects to the server, the server sends back the time information to the client and shuts down the connection. Then the client displays the full time message to the user and terminates.

Important: for the C implementation of the client you need to use the C echo client from the last assignment and adapt its semantics to the specs of this assignment. However, you will need to write the Java client from scratch, using class Socket.

Also note that there is no interaction with the user, i.e. there is no prompting for a server address and/or port number. Instead, you will provide the information of the server address/port to your program by using SYMBOLIC_CONSTANTS. Convince yourself that in a C environment you put those in a header file, while in a Java environment you put them in an interface file.

Furthermore, I want you to use the human readable server address above and do a DNS lookup. In C, this can be done with the system call gethostbyname()

## Part 2: Two Multithreaded Daytime Servers
In this second part I want you to write a Daytime server in our two environments, C and Java. Both servers need to be parallel servers that return the information that your clients experienced in the first project part.

Please note that you already have an example of a parallel server in C, it is contained in the Echo Server code that I provided to you in the first project. The Java Echo Server provides a nice base to start from as well, but it is not parallel. You will need to work with Java Threads to make this happen.
