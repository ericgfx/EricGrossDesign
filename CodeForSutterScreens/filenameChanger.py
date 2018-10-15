
import os
xDirectory = '//Users/erimacbookpro/EricGrossDesign/CodeForSutterScreens/'
Directory = '.'
OldFilename = 'Slide1.png'
NewFilename = 'Filler01.png'


def join(Directory,Filename):
	joint = os.path.join(Directory,Filename)
	return joint

def changeName(OldFilename,NewFilename,Directory):
	OldFilename = join(Directory,OldFilename)
	NewFilename = join(Directory,NewFilename)
	print os.listdir(Directory)
	print OldFilename
	print NewFilename
	for filename in os.listdir(Directory):
		os.rename(OldFilename, NewFilename)


changeName(OldFilename,NewFilename,Directory)


#// Successfully changes the name of the file.
#// OSError: [Errno 2] No such file or directory
