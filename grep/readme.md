# grep
grep is a tool to search files for a keyword. And there are "ack" or "ag" that provide the same functionalties but with better performance. Here I am going to build the same tool utilizing multi-threading. 

#### Input format
 - mgrep {keyword} {relative path}

#### Output format
 - If the keyword is found in the file, output the correspoding file name and line numbers. 

#### Requirements
1. If relative path is a directory, search all files in the directory.
2. If there are other directories in the given relative path, also search all files in that directory.
3. Utilize multi-threading to search as fast as possible
4. The search result for the same file should be output at once
5. Assume that there are no symlinks in the directory
