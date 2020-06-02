import sys
import os

# Replace custom project name alias in CMakeLists.txt and .vcxproj files with user given value.
# Call cmake build command.
def build(projName):
    
	# Define aliases key
    aliasNameProj = "#{VG_BUILD_PROJNAME}"

    # Replace aliases in CMakeLists file
    with open("CMakeLists.txt", "r+") as f:    	
    	buff = f.read()
    	buff = buff.replace(alisNameProj, projName) # Replace proj name alias
    	f.seek(0) # Set pointer to the start fo the file before write op
    	f.write(buff) # Overwrite file with replaced values

    # Replace aliases in .vcxproj file
	with open("Game/projs/win.desktop/game.vcxproj", "r+") as f:    	
    	buff = f.read()
    	buff = buff.replace(alisNameProj, projName) # Replace proj name alias
    	f.seek(0) # Set pointer to the start fo the file before write op
    	f.write(buff) # Overwrite file with replaced values

    # Rename .vcxproj in order to match proj name picked by user
    oldFilename = os.path.join("Game/projs/win.desktop", "game.vcxproj");
    newFilename = os.path.join("Game/projs/win.desktop", projName + ".vcxproj");
    os.rename(oldFilename, newFilename)

    # Replace aliases in .vcxproj.filters file
	with open("Game/projs/win.desktop/game.vcxproj.filters", "r+") as f:    	
    	buff = f.read()
    	buff = buff.replace(alisNameProj, projName) # Replace proj name alias
    	f.seek(0) # Set pointer to the start fo the file before write op
    	f.write(buff) # Overwrite file with replaced values

    # Rename .vcxproj.filters in order to match proj name picked by user
    oldFilename = os.path.join("Game/projs/win.desktop", "game.vcxproj.filters");
    newFilename = os.path.join("Game/projs/win.desktop", projName + ".vcxproj.filters");
    os.rename(oldFilename, newFilename)

if __name__ == "__main__":
	# Parse command args
    projName = str(sys.argv[1]) # arg[1] -> project name
    build(projName)