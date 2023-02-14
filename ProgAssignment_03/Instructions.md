# What to do
Download the sample code, if you have not already done so.

Make a deliberate effort to understand the code, especially the parts that we highlighted in class, when I explained how threads from the threadpool are blocked and then activated when needed by way of an interplay of wait() and notify().

Change the programming logic such that the server serves "3A+1" requests, see [here](https://en.wikipedia.org/wiki/Collatz_conjecture).

Specifically, the server receives an integer in binary format from a client over the network and applies the 3A+1 algorithm. It keeps track of how many steps it takes to reduce the original number to 1 and then sends that number of steps (again in binary format as an Integer) back to the client.

On the client side we want to assume that the user puts in an integer through the standard input (i.e. keyboard), upon which the client sends this number to the server, receives the result, i.e. the number of steps, and prints it out on the standard output. Then the client shuts down the connection.

While I provide you with the Java sample code for the server that serves as a framework - only the semantics need to be changed - you will need to provide TWO clients of your own, which are implemented in C as well as in Java.
