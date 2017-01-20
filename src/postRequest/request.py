#!/usr/bin/python
#coding:gbk
import json
import urllib2
import requests
import sys
import base64

#url = 'http://10.134.28.27:20166?mspider'
url = 'http://10.134.28.27:20166?haha'
#payload = {'logtitude':100, 'latitude':200, 'distance':1000}
#headers = {'Content-type':'application/json'}
#q = 0
#while(q < 100):
#	r = requests.post(url, data = json.dumps(payload), headers = headers)
#	q += 1



###### FILE
#ff = {'file':open('amr.amr', 'rb')}
#ff = {'file':open('test.txt', 'rb')}
#r = requests.post(url, files = ff)
#r.text


fin = open("amr.amr", 'rb')
speech = base64.b64encode(fin.read())
print speech
#fin = open("test.txt", 'rb')
#fin = open("aaa.txt", 'rb')
#headers = {'Content-type':'multipart/form-data'}
headers = {'Content-type':'application/json'}
content = ""
for line in fin.readlines():
	line = line.strip()
	#sys.stdout.write("%s" % line)
	content += line
fin.close()
exit()
#print content
#unicode(content, errors='ignore')
#payload = {'logtitude':100, 'latitude':200, 'distance':1000 , 'ffff':content}
payload = {'amrVoice':content}
r = requests.post(url, data = json.dumps(payload,encoding='latin1'), headers = headers)


