import pymongo

from pymongo import MongoClient
client = MongoClient()

#Dumping in mongodb
db = client.test_database
collection = db.test_collection
import datetime
post = {"uid" : 2361989187105,
        "item": "pen",
        "price" : 5,
        "date": datetime.datetime.utcnow()}

posts=db.table1
post_id=posts.insert_one(post).inserted_id

import pprint
pprint.pprint(posts.find_one())
#pprint.pprint(table1.find_one({"uid": 2361989187152}))