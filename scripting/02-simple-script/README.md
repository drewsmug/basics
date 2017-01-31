Write a one line shell script that for each file or directory in the 
current directory prints:
"foo is a file" for files
and "bar is a directory" for directories.

```
cd /tmp
mkdir tmp
cd tmp
touch foo
touch bar
mkdir foodir
mkdir bardir
```
Your one-liner goes here that produces following output
```
bar is a file
bardir is a directory
foo is a file
foodir is a directory
```
