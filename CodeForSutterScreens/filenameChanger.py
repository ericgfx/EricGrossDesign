import os
# Global Variables for testing only.
Directory = '.'
OldFilename = 'Slide1.png'
NewFilename = 'Filler01.png'


def join(Directory,Filename):
	joint = os.path.join(Directory,Filename)
	return joint

def changeName(OldFilename,NewFilename,Directory):
	OldFilename = join(Directory,OldFilename)
	NewFilename = join(Directory,NewFilename)
	print'Current Files are: ',repr(os.listdir(Directory))
	print'The current file name is: ',repr(OldFilename)
	print'The new file name will be: ',repr(NewFilename)
	for filename in os.listdir(Directory):
		os.rename(OldFilename, NewFilename)

# def runTest():
# 	print('Write Test Here')
	
changeName(OldFilename,NewFilename,Directory)


#// Successfully changes the name of the file.
#// OSError: [Errno 2] No such file or directory
