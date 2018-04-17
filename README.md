![alt text](https://github.com/brokebloke/BreachPass/blob/master/logo/BreachPass-logo.png)

## What is BreachPass?
Breach Pass works with existing password managers to identify breached usernames and emails, based upon existing passwords within LastPass password manager and corrects them by changing them both from the website and LastPass with little to no user input.

![alt text](https://github.com/brokebloke/BreachPass/blob/master/logo/demonstration.gif)

## What problem does BreachPass solve?
BreachPass solves the issue regarding self management of passwords. The average user becomes informed that their password has been breached after 154 days, usually from an email notification indicating that someone has attempted to log into their account. BreachPass checks for these breached accounts automatically and changes them for the user.

## Current To-Do list
- Work with Lastpass's existing JSON formatting
- Create BreachPass as a Daemon
- Extend support to other systems
- Extend support to other CLI password managers (ie: Dashline)
- Create a makefile
- Create more accurate path detection
- Add comments
- Fix/Improve memory management issues (read memory access)

## Build & Installation
Simply build the files with GCC with -lcurl tag 

Python3 and RoboBrowser is required for website.py

## Credits
- Various people and sources on the internet for snippets of code
- haveibeenpwned for use of their API and their database
