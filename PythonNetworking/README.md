# Python Networking

## [View Code](https://github.com/ImTimTong/Projects/tree/main/PythonNetworking)

## Description
These are Python scripts developed as part of a networking lab exercise. The scripts demonstrate basic SMTP (Simple Mail Transfer Protocol) client functionalities for sending emails through both a local SMTP server and a Gmail SMTP server.

## Scripts Overview
### SMTPClient-local.py
This script implements a simple SMTP mail client to send an email to a local SMTP server. It utilizes sockets to establish a TCP connection with the mail server running on localhost. The script sends a basic email message with subject and body to a specified recipient.

### SMTPClient-secure-gmail.py
This script also implements an SMTP mail client but sends an email using Gmail's SMTP server (smtp.gmail.com). It prompts the user for their email address, password, and the recipient's email address. The script then pings Google's servers, captures the result, and emails it to the recipient using SSL encryption over port 465.

## Instructions
### Running SMTPClient-local.py
1. Before running local.py, ensure you have a local SMTP server running. You can start one using the following command:
`python -m smtpd -c DebuggingServer -n localhost:6000`

2. Run local.py using Python: `python local.py`
   
### Running SMTPClient-secure-gmail.py
1. Ensure you have allowed login from less secure apps in your Gmail account settings. Otherwise, Gmail might block the login attempt.
2. Run secure-gmail.py using Python:
`python secure-gmail.py`
3. Enter your email address, password, and the recipient's email address as prompted.
