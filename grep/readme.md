# grep

## Requirements
grep is a tool to search strings from files. And there are "ack" or "ag" that provide the same functionalties but with better performance. Here I am going to build the same tool utilizing multi-threading. 
<br>
Input format
 - mgrep {keyword} {relative path}
<br>
 Output format
 - If the keyword is found in the file, output the correspoding file name and line numbers. 
 - 파일의 각 line에 keyword가 있는 경우, 해당 파일과 줄 번호를 출력한다.
<br>

1. If relative path is a directory, search all files in the directory.
2. If there are other directories in the given relative path, also search all files in that directory.
3. Utilize multi-threading to search as fast as possible
4. The search result for the same file should be output at once
5. Assume that there are no symlinks in the directory
