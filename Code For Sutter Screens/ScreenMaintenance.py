import json

filename = 'slideList.txt'

def readFile():
	file = open(filename, mode='r')
	text = file.read()
	file.close()
	return text

testList = [
    {"filename": "Test1.png",
    "content": 'TestContent1',
    "startDate":'01/01/2018',
    "endDate": '03/03/2019',
    "Filler Status": False 
    },
    {
    "filename": "Test2.png",
    "content": 'TestContent2',
	"startDate":'01/01/2018',
    "endDate": '01/01/2018',
    "Filler Status": False }
]


slideList = readFile()
print(slideList[0]['content'])

