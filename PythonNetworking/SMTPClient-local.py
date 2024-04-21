# Contributor: Timothy Tong
#
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server

# Note:
# Run a local smtp mail server using the following command before running this code:
# python -m smtpd -c DebuggingServer -n localhost:6000


from socket import *
import ssl


# Choose a mail server
mailserver = 'localhost'

# Create socket called clientSocket and establish a TCP connection with mailserver
serverPort = 6000
clientSocket = socket(AF_INET, SOCK_STREAM) #create socket
clientSocket.connect((mailserver,serverPort)) #connect

# Port number may change according to the mail server
recv = clientSocket.recv(1024).decode() #receive server response and check if good
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')
rcpt_domain = recv.split()[1] #server domain

# Send HELO command along with the server address
clientSocket.send('HELO ' + mailserver + '\r\n') #send HELO for handshake
recv = clientSocket.recv(1024).decode() #receive server response and check it
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send MAIL FROM command and print server response
clientSocket.send('MAIL FROM: sender@random.edu\r\n') #send MAIL FROM
recv = clientSocket.recv(1024).decode() #read response and check
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send RCPT TO command and print server response
clientSocket.send('RCPT TO: receiver@' + rcpt_domain + '\r\n') #send RCPT TO
recv = clientSocket.recv(1024).decode() #read response and check
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send DATA command and print server response
clientSocket.send('DATA\r\n') #send DATA command
recv = clientSocket.recv(1024).decode() #read response and check
print(recv)
if recv[:3] != '354':
    print('354 reply not received from server.')

# Send message data.
clientSocket.send('SUBJECT: Greeting To you!\nThis is line 1\nThis is line 2.') # Message to send
clientSocket.send('\r\n.\r\n') # Message ends with a single period

recv = clientSocket.recv(1024).decode() #Read response and check
print(recv)
if recv[:3] != '250':
    print('250 reply not received from server.')

# Send QUIT command and get server response
clientSocket.send('QUIT\r\n') #Send QUIT
recv = clientSocket.recv(1024).decode() #Read response and check
print(recv)
if recv[:3] != '221':
    print('221 reply not received from server.')
