# MP3 Tag Reader 
MP3 tag reader is a software which will read and display MP3 (ID3) tag information from MP3 files. The software will be desktop based and not web based. All operations will be performed using command line interface

# Usage 
### Help Command 
``` 
./a.out -h
```
it will print all the available commands that can be used with this binary file



### Print MP3 tag details 
```
./a.out <mp3.file>
./a.out sample.mp3
```


### Modify tag data

To modify title imformation  and view those information 
```
./a.out -t "newname" sample.mp3 
./a.out sample.mp3
```


similarly we can use others commands to modify tag information
