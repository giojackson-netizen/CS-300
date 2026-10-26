# CS 300 – Data Structures and Algorithms
**Giovanni Jackson**

## Portfolio Overview

This repository includes my Project One runtime and memory analysis and my Project Two C++ advising assistance program. Project One compares vectors, hash tables, and binary search trees. Project Two uses the vector design I recommended to load course information, print courses in alphanumeric order, and display individual courses with their prerequisites.

## What was the problem you were solving in the projects for this course?

The problem was creating an advising program that could organize course information and help users see which courses they needed to take. The program needed to read course data from a file, print an ordered course list, and display a selected course with its prerequisites. For Project One, I compared different data structures to decide which would work best. For Project Two, I used that analysis to build the program in C++.

## How did you approach the problem? Consider why data structures are important to understand.

I approached the problem by comparing the runtime, memory usage, and maintenance needs of a vector, hash table, and binary search tree. I chose a vector because the course list was small, and it provided a straightforward way to store and manage the information. My program uses linear searches to find courses and merge sort to print them in alphanumeric order.

Understanding data structures is important because the way information is stored affects how efficiently a program can search, organize, and process it. A structure that works well for a small list may not be the best choice for a larger system. This connects to my experience working in a hospital, where keeping equipment information organized makes it easier to find what is needed and complete work efficiently.

## How did you overcome any roadblocks you encountered while going through the activities or project?

One challenge in the implementation was handling course files correctly while checking for invalid information. The program needed to account for missing course numbers or titles, duplicate courses, and prerequisites that did not exist in the catalog. It also needed to allow blank prerequisite columns when a course did not have any prerequisites.

I addressed these issues by separating file loading, validation, searching, and sorting into different functions. The program reads courses into a temporary vector and checks prerequisites after all records have been loaded. This allows a prerequisite to appear later in the file. It also keeps previously loaded data available if a new file fails validation.

## How has your work on this project expanded your approach to designing software and developing programs?

This project helped me understand the value of planning how information will move through a program before writing the full implementation. Comparing the data structures and writing pseudocode gave me a clearer direction for building the final program. It also showed me that choosing a design involves considering the size of the data, the operations users need, and how easily the program can be maintained.

I can apply this approach to the biomedical equipment tracker I have been exploring. Organizing equipment records, searching for devices, and connecting related information all require decisions about how data should be stored and accessed. This project gave me a better foundation for making those decisions.

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project reinforced the importance of using clear names, focused functions, and comments that explain the purpose of the code. Instead of placing every operation inside the main function, I separated responsibilities into functions such as LoadCourses, FindCourse, MergeSort, and PrintCourse. This makes the program easier to follow and makes it easier to locate the part that needs to change.

I also paid attention to input validation and clear error messages. The program checks whether data has been loaded before allowing users to print or search courses, and it handles invalid menu choices. These practices help make the program easier to use, troubleshoot, and expand.
