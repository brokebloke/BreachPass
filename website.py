# Password Changer - A simple password changing POC script to be further improved upon

import re
import sys
import json

from robobrowser import RoboBrowser
from urllib.parse import urlparse

# Treats each argument as a variable
username = sys.argv[1]
password = sys.argv[2]
newpassword = sys.argv[3]
domain = sys.argv[4]

# Uses a test JSON file that could work with breached websites in the future
data = {"websites" : {"MySpace" : { "login": {"https://myspace.com/signin": {"username" : "username", "password": "password"}}, "change": {"https://myspace.com/settings/profile": {"newpassword" : "password" , "verifynewpassword": "verifypassword"}}}}}
json_data = json.loads(json.load(data)) # Loads JSON data as Python Library data

website = urlparse(domain) # Parses the domain given
parsedsite = website.netloc # Parses the URL and grab the root domain

if json_data['websites']['MySpace'] in parsedsite: # String checks for the JSON data MySpace against the URL link
	br = RoboBrowser(user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36') # Runs a RoboBrowser session with a popular user agent

	br.open(json_data['websites']['MySpace']['login']) # Opens the Sign In link determined by the JSON data
	signup_form = br.get_form(class_='signup') # Extracts the sign up form
	signup_form[(json_data['websites']['MySpace']['username']['username'])] = username # Defines the input (username) as username
	signup_form[(json_data['websites']['MySpace']['password']['password'])] = password # Defines the input (password) as password
	br.submit_form(form) # Submits the form
	if br.status_code == 200: # Checks if the status code 200 (successful) is met
		br1 = RoboBrowser(user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36') # Runs a RoboBrowser session with a popular user agent

		br.open(json_data['websites']['MySpace']['change']) # Opens the Change Password link determined by the JSON data
		passwordform = br1.get_form() # Extracts the first form (in this instance, the account info form)
		passwordform[(json_data['websites']['MySpace']['change']['newpassword'])] = newpassword # Defines the input (newpassword) as newpassword
		passwordform[(json_data['websites']['MySpace']['change']['verifypassword'])] = newpassword # Defines the input (verifypassword) as newpassword

		br1.submit_form(passwordform) # Submits the form
		if br1.status_code == 200: # Checks if the status code 200 (Successful) is met
			return 200 # Returns 200
		else:
			return 0
	else:
		return 0
else:
	return 0