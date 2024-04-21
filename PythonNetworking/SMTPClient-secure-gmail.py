# Contributor: Timothy Tong
#
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server
# the program runs the ping command, and emails the result using smtp.gmail.com

# NOTE: Do not forget to allow login from less secure apps in your gmail account. Otherwise gmail will complain about username and password.

import smtplib, ssl
import subprocess

port = 465  # For SSL
email_address = raw_input("Please enter your email address: ") #send login + receiver info
password = raw_input("Please enter your password: ")
receiver_email = raw_input("Please enter receiver's email address: ")
subject = 'Server Ping Result!' #subject line

# ping google.com and save the result
proc=subprocess.Popen('ping -c 2 google.com', shell=True, stdout=subprocess.PIPE, ) #copy output
out = proc.communicate()[0] #put in variable
body = 'From: ' + email_address + '\nTo: ' + receiver_email + '\nSubject: ' + subject + '\n' + out #create body

print '\nNow contacting the mail server...'
server = smtplib.SMTP_SSL('smtp.gmail.com', port) #establish connection to server
server.login(email_address, password) #login
server.sendmail(email_address, receiver_email, body) #send message
server.quit() #close connection

print '\nSending email...'
