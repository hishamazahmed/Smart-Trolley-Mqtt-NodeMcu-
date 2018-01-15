from flask import Flask
from flask import request
from pymongo import MongoClient
app = Flask(__name__)

client = MongoClient('localhost:27017')
db=client.rfid

 
@app.route('/')
def hello_world():
    return 'Hello, World!'

@app.route('/sensor',methods = ['POST', 'GET'])
def sensor():
    if request.method == 'POST':
        #print (request.is_json)
        content = request.json 
        db.table2.insert_one(content)
        x = db.table2.find()
        #for i in x:
         #   print(i)
        return "done"
    else:
    #   user = request.args.get('nm')
        return "error"

if __name__ == '__main__':
    app.run(host='192.168.0.103', port=5000)