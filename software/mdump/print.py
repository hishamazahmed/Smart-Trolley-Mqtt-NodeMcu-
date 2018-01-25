import pymongo

from pymongo import MongoClient
client = MongoClient()

#Dumping in mongodb
db = client.test_database
collection = db.test_collection
posts=db.table1


import pprint
x=2361989187160
for post in posts.find({"uid": x }):
    pprint.pprint(post)
    
for post in posts.find({"uid": x }):
    if posts.find({"uid": x }).count > 0:
        pprint.pprint("uid found: True")
    else:
        pprint.pprint("uid found: False")

#pprint.pprint("Counting is: " + str(posts.count()))

#Printing all data
#for post in posts.find():
#    pprint.pprint(post)    