# Builds all the projects in the solution...
.PHONY: all_projects
all_projects: NetDebugLog 

# Builds project 'NetDebugLog'...
.PHONY: NetDebugLog
NetDebugLog: 
	make --directory="." --file=NetDebugLog.makefile

# Cleans all projects...
.PHONY: clean
clean:
	make --directory="." --file=NetDebugLog.makefile clean

