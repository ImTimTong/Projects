# C Networking 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/CProgramNetworking)

## Overview
This repository showcases a simple implementation of the client and server sides of a stop & wait protocol using C programming language as part of Networking Lab. The program allows the client to transfer a file to the server reliably, considering packet corruption and loss scenarios.

## Files
### client.c
This file contains the implementation of the client side of the stop & wait protocol. It includes functions to establish a connection with the server, send file contents, and handle acknowledgments.

### server.c
This file contains the implementation of the server side of the stop & wait protocol. It includes functions to receive file contents from the client, verify packet integrity, and send acknowledgments.

### tfv1.h
This header file contains necessary definitions and structures used in both client.c and server.c files.

## How to Use
1. Compile the client.c and server.c files:
```bash
gcc -o client client.c
gcc -o server server.c
```

2. Run the server specifying the port number:
`./server port_number`

3. Run the client specifying the server's IP address, port number, source file, and destination file:
`./client port_number server_ip source_file dest_file`

## Assumptions
The stop and wait protocol assumes packet corruption and packet loss scenarios.
The program simulates an erroneous channel where packets can get corrupted with an 80% probability and lost with an 80% probability.
