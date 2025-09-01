<h1 align=center>🐇Bunarr</h1> 
<p align=center>A simple c99 static array implementation</p>
<div align=center>
  
  ![GitHub last commit](https://img.shields.io/github/last-commit/vivivivianne/bunarr?style=for-the-badge&labelColor=101418&color=9ccbfb)
  ![GitHub Repo stars](https://img.shields.io/github/stars/vivivivianne/bunarr?style=for-the-badge&labelColor=101418&color=b9c8da)
  ![GitHub repo size](https://img.shields.io/github/repo-size/vivivivianne/bunarr?style=for-the-badge&labelColor=101418&color=d3bfe6)

</div>

## ✅ Features:
- Static size
- Insert, Append, Remove, Get and more.
- The header file is overly commented with the usage explained in it.
- `bunarr_exe(arr, func)` runs a function on all items of the list.
- `bunarr_free(arr)` destroys the list and calls callback function in each item if one is defined.
- +list cloning functions that allow copying an list or creating an list of pointers to another list.

## 💾 Usage 

- To add to your project simply copy the headers and bunarr.c
- For examples see [tests.c](tests.c)

## ⚠️  Caveats:

- Not made with double pointers in mind, might not work.
- it also requires buntypes.h which is what i personally use for types.
- The current insert implementation does not allow inserting things that are outside of the list length.
This means you should use insert only to insert between things that are already in the list.

## 🗒️ Todo:

- Implement insert
- Implement sub arrays
- Consider improving inserting functionality
- Proper error handling
- Generate docs with doxygen???
