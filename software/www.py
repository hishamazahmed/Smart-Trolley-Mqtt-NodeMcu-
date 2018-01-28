from flask import Flask
from flask import request
import pymongo
import pprint
from pymongo import MongoClient
import time
ppp=0
app = Flask(__name__) 
client = MongoClient()
@app.route('/temp',methods = ['POST', 'GET'])
def sensor():
    if request.method == 'POST':

        print (request.is_json)
        content = request.json
        content["timestamp"] = time.ctime()      
        nnn=content["value"]
        print (nnn)
       
        
        db = client.PROJECT                
        data = db.test_collection.find_one({'rid' : str(nnn)})
        lll= (data["price"])
         


        return lll
    else:
    #   user = request.args.get('nm')
        return "error"

if __name__ == '__main__':
    
    app.run(host='0.0.0.0',port='8081')







