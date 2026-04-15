This project has been created as part of the 42 curriculum by miwehbe.

# get_next_line

`get_next_line` is a 42 project that does one thing: read a line from a file descriptor each time you call it.
Call it once -> you get a line. Call it again -> next line. Keep going -> until it returns `NULL`.

Sounds easy. It's not.

The tricky part is not just reading from the file, but keeping what's left for the next call without using global variables. That's where static variables come in, and that's basically the whole point of the project.
The function works with any file descriptor (files, stdin, etc.), and it has to behave correctly no matter the buffer size ,even if it's very small or very big.

## How it works

The idea is to keep a "leftover" between calls.

- There's a static variable that stores what was already read but not returned yet
- Each time you call the function, it reads more from the file
- It keeps reading until it finds a `\n` or reaches the end
- It returns the line (including the newline if there is one)
- And saves the rest for the next call

If there's no newline at the end of the file, it just returns whatever is left.

The important part is that the static variable keeps its value between calls, so the function doesn't start from zero every time.

## Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

You can change the buffer size to test different cases. It should also compile without defining it:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -o gnl
```

## Example

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```
> **Note:** you need to create `file.txt` manually before testing with a main

## What was hard

- Understanding how static variables actually behave
- Handling memory without leaks
- Managing the leftover correctly
- Edge cases (empty file, no newline, small buffer, etc.)

## Resources

- [man2 - read()](https://man7.org/linux/man-pages/man2/read.2.html) : understanding how read() works at a low level
- [man2 - open()](https://man7.org/linux/man-pages/man2/open.2.html) : file descriptors and how to open files
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/) : good intro to static variables if you're new to the concept
- [cppreference - C memory](https://en.cppreference.com/w/c/memory) : malloc, free and memory management

# Notes
I used AI just to confirm how static variables behave between function calls, nothing more.

---

"Static variable. One line at a time. How hard can it be?" : me, before starting this project.